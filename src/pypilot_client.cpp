/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2020 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#include <vector>

#include <wx/wx.h>
#include <wx/socket.h>

#include "pypilot_client.h"


BEGIN_EVENT_TABLE(pypilotClient, wxEvtHandler)
    EVT_SOCKET(-1, pypilotClient::OnSocketEvent)
END_EVENT_TABLE()

/* queue mode queues up data, where map mode replaces incoming data with most recent
   if receive is not called as often as the incoming data, map mode reduces processing
   but for scopes or loggers, we need queue mode */
pypilotClient::pypilotClient(bool queue_mode, bool request_list)
: m_bQueueMode(queue_mode), m_bRequestList(request_list)
{
//    m_sock.Connect(wxEVT_SOCKET, wxSocketEventHandler(pypilotClient::OnSocketEvent), NULL, this);
    
    m_sock.SetEventHandler(*this);
    m_sock.SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    m_sock.Notify(true);
    m_sock.SetTimeout(1);
}

void pypilotClient::connect(wxString host, int port)
{
    if(host.empty())
        host = "pypilot";
            
    if(port == 0)
        port = 23322; /* default port */

    wxIPV4address addr;
    addr.Hostname(host);
    addr.Service(port);
    m_sock.Connect(addr, false);
}

void pypilotClient::disconnect()
{
    m_sock.Close();
    m_sock_buffer.clear();
    OnDisconnected();
}

bool pypilotClient::receive(std::string &name, Json::Value &value)
{
    if(m_bQueueMode) {
        if(m_queue.empty())
            return false;

        std::pair<std::string, Json::Value> &val = m_queue.front();
        m_queue.pop_front();
    
        name = val.first;
        value = val.second;
        return true;
    }

    if(m_map.empty())
        return false;

    std::map<std::string, Json::Value>::iterator it = m_map.begin();
    name = it->first;
    value = it->second;
    m_map.erase(it);
    return true;
}

void pypilotClient::set(std::string name, Json::Value &value)
{
    m_sock.Write(name.c_str(), name.size());
    m_sock.Write("=", 1);
    Json::FastWriter writer;
    std::string str = writer.write(value);
    m_sock.Write(str.c_str(), str.size());
}

void pypilotClient::set(std::string name, double value)
{
    Json::Value v(value);
    set(name, v);
}

void pypilotClient::set(std::string name, std::string &value)
{
    Json::Value v(value);
    set(name, v);
}

void pypilotClient::set(std::string name, const char *value)
{
    Json::Value v(value);
    set(name, v);
}

void pypilotClient::watch(std::string name, bool on, double period)
{
    Json::Value request;
    if(on)
        request[name] = period;
    else
        request[name] = false;
    set("watch", request);
}

bool pypilotClient::info(std::string name, Json::Value &info)
{
    info = m_list[name.c_str()];
    return !info.isNull();
}

void pypilotClient::update_watchlist(std::map<std::string, double> &watchlist)
{
    Json::Value request;
    // watch new keys we weren't watching
    for(std::map<std::string, double>::iterator it = watchlist.begin(); it != watchlist.end(); it++)
        if(m_watchlist.find(it->first) == m_watchlist.end())
            request[it->first] = it->second;

    // unwatch old keys we don't need
    for(std::map<std::string, double>::iterator it = m_watchlist.begin(); it != m_watchlist.end(); it++)
        if(watchlist.find(it->first) == watchlist.end())
            request[it->first] = false;

    if(request.size())
        set("watch", request);
    m_watchlist = watchlist;
}

void pypilotClient::OnSocketEvent(wxSocketEvent& event)
{
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
            m_queue.clear();
            m_map.clear();
            m_sock_buffer.clear();
            m_list = Json::Value();

            if(m_bRequestList)
                watch("values");

            if(m_watchlist.size()) {
                Json::Value request;
                for(std::map<std::string, double>::iterator it = m_watchlist.begin(); it != m_watchlist.end(); it++)
                    request[it->first] = it->second;
                if(request.size())
                    set("watch", request);
            }
            
            OnConnected();
            break;

        case wxSOCKET_LOST:
            disconnect();
            break;

        case wxSOCKET_INPUT:
        {
    #define RD_BUF_SIZE    65536
            std::vector<char> data(RD_BUF_SIZE+1);

            event.GetSocket()->Read(&data.front(), RD_BUF_SIZE);
            if(!event.GetSocket()->Error()) {
                size_t count = event.GetSocket()->LastCount();
                if(count) {
                    data[count]=0;
                    m_sock_buffer += (&data.front());
                }

                // overflow and reset connection at 640k in buffer
                if(m_sock_buffer.size() >= 1024*640) {
                    wxLogMessage( "pypilot client input buffer overflow!\n" );
                    disconnect();
                    break;
                }
            }

            for(;;) {
                int line_end = m_sock_buffer.find_first_of("\n");
                if(line_end <= 0)
                    break;
                std::string line = m_sock_buffer.substr(0, line_end);
                long unsigned int c = line.find('=');
                //printf("LINE: %s\n", line.c_str());
                if(c == std::string::npos) {
                    wxString sLogMessage;
                    sLogMessage.Append(wxT("pypilot_pi: Error parsing - "));
                    sLogMessage.Append( line );
                    wxLogMessage( sLogMessage );
                } else {
                    std::string key = line.substr(0, c);
                    std::string json_line = line.substr(c+1);
                    Json::Value value;
                    Json::Reader reader;
                    if(!reader.parse(json_line, value)) {
                        wxString sLogMessage;
                        sLogMessage.Append(wxT("pypilot_pi: Error parsing Json::Value message - "));
                        sLogMessage.Append( json_line );
                        wxLogMessage( sLogMessage );
                    } else if(key == "values") {
                        if(m_list.isNull())
                            m_list = value;
                        else
                            for(Json::ValueIterator val = value.begin(); val != value.end(); val++)
                                m_list[val.key().asString()] = *val;
                    } else {
                        if(m_bQueueMode) {
                            if(m_queue.size() >= 4096) {
                                wxLogMessage( "pypilot client message overflow" );
                                m_queue.clear();
                            }
                            std::pair<std::string, Json::Value > p(key, value);
                            m_queue.push_back(p);
                        } else
                            m_map[key] = value;
                    }
                }

                if(line_end > (int)m_sock_buffer.size())
                    m_sock_buffer.clear();
                else
                    m_sock_buffer = m_sock_buffer.substr(line_end+1);
            }
        } break;
    default:;
    }
}

void pypilotClient::GetSettings(std::list<std::string> &settings, std::string member)
{
    if(m_list.isNull())
        return;

    for(Json::ValueIterator val = m_list.begin(); val != m_list.end(); val++)
        if(val->isMember(member))
            settings.push_back(val.key().asString());
}
