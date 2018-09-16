/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2018 by Sean D'Epagnier                                 *
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

#include "signalk_client.h"


BEGIN_EVENT_TABLE(SignalKClient, wxEvtHandler)
    EVT_SOCKET(-1, SignalKClient::OnSocketEvent)
END_EVENT_TABLE()

/* queue mode queues up data, where map mode replaces incoming data with most recent
   if receive is not called as often as the incoming data, map mode reduces processing
   but for scopes or loggers, we need queue mode */
SignalKClient::SignalKClient(bool queue_mode, bool request_list)
: m_bQueueMode(queue_mode), m_bRequestList(request_list)
{
//    m_sock.Connect(wxEVT_SOCKET, wxSocketEventHandler(SignalKClient::OnSocketEvent), NULL, this);
    
    m_sock.SetEventHandler(*this);
    m_sock.SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    m_sock.Notify(true);
    m_sock.SetTimeout(1);
}

void SignalKClient::connect(wxString host, int port)
{
    if(host.empty())
        host = "pypilot";
            
    if(port == 0)
        port = 21311; /* default port */

    wxIPV4address addr;
    addr.Hostname(host);
    addr.Service(port);
    m_sock.Connect(addr, false);
}

void SignalKClient::disconnect()
{
    m_sock.Close();
    m_list = Json::Value();
    m_watchlist.clear();
    OnDisconnected();
}

bool SignalKClient::receive(std::string &name, Json::Value &value)
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

void SignalKClient::get(std::string name)
{
    Json::Value request;
    request["method"] = "get";
    request["name"] = name;
    send(request);
}

void SignalKClient::set(std::string name, Json::Value &value)
{
    Json::Value request;
    request["method"] = "set";
    request["name"] = name;
    request["value"] = value;
    send(request);
}

void SignalKClient::set(std::string name, double value)
{
    Json::Value v(value);
    set(name, v);
}

void SignalKClient::set(std::string name, std::string &value)
{
    Json::Value v(value);
    set(name, v);
}

void SignalKClient::set(std::string name, const char *value)
{
    Json::Value v(value);
    set(name, v);
}

void SignalKClient::watch(std::string name, bool on)
{
    if(on)
        get(name);
    Json::Value request;
    request["method"] = "watch";
    request["name"] = name;
    request["value"] = on;
    send(request);
}

bool SignalKClient::info(std::string name, Json::Value &info)
{
    info = m_list[name.c_str()];
    return !info.isNull();
}

void SignalKClient::request_list_values()
{
    Json::Value request;
    request["method"] = "list";
    send(request);
}

void SignalKClient::send(Json::Value &request)
{
    Json::FastWriter writer;
    std::string str = writer.write(request);
    m_sock.Write(str.c_str(), str.size());
}

void SignalKClient::update_watchlist(std::map<std::string, bool> &watchlist, bool refresh)
{
        // watch new keys we weren't watching
    for(std::map<std::string, bool>::iterator it = watchlist.begin(); it != watchlist.end(); it++)
        if(m_watchlist.find(it->first) == m_watchlist.end())
            watch(it->first);
        else if(refresh)
            get(it->first); // make sure we get the value again to update dialog here

    // unwatch old keys we don't need
    for(std::map<std::string, bool>::iterator it = m_watchlist.begin(); it != m_watchlist.end(); it++)
        if(watchlist.find(it->first) == watchlist.end())
            watch(it->first, false);

    m_watchlist = watchlist;
}

void SignalKClient::OnSocketEvent(wxSocketEvent& event)
{
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
            m_queue.clear();
            m_map.clear();
            m_sock_buffer.clear();
            if(m_bRequestList) {
                m_list = Json::Value();
                request_list_values();
                m_bRequestingList = true;
            } else
                OnConnected();
            break;

        case wxSOCKET_LOST:
            disconnect();
            break;

        case wxSOCKET_INPUT:
        {
    #define RD_BUF_SIZE    8192
            std::vector<char> data(RD_BUF_SIZE+1);
            event.GetSocket()->Read(&data.front(),RD_BUF_SIZE);
            if(!event.GetSocket()->Error())
            {
                size_t count = event.GetSocket()->LastCount();
                if(count && count < RD_BUF_SIZE)
                {
                    data[count]=0;
                    m_sock_buffer += (&data.front());
                }
            }

            for(;;) {
                int line_end = m_sock_buffer.find_first_of("\n");
                if(line_end <= 0)
                    break;
                std::string json_line = m_sock_buffer.substr(0, line_end);
                Json::Value value;
                Json::Reader reader;
                if(!reader.parse(json_line, value)) {
                    wxString sLogMessage;
                    sLogMessage.Append(wxT("pypilot_pi: Error parsing Json::Value message - "));
                    sLogMessage.Append( json_line );
                    wxLogMessage( sLogMessage );
                } else {
                    if(m_bRequestingList) {
                        m_list = value;
                        m_bRequestingList = false;
                        OnConnected();
                    } else {
                        for(Json::ValueIterator val = value.begin(); val != value.end(); val++)
                            if(m_bQueueMode) {
                                if(m_queue.size() >= 4096) {
                                    wxLogMessage( "SignalK client message overflow" );
                                    m_queue.clear();
                                }
                                std::pair<std::string, Json::Value > p(val.key().asString(), *val);
                                m_queue.push_back(p);
                            } else
                                m_map[val.key().asString()] = *val;
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
