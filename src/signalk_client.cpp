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
    m_list = wxJSONValue();
    OnDisconnected();
}

bool SignalKClient::receive(wxString &name, wxJSONValue &value)
{
    if(m_bQueueMode) {
        if(m_queue.empty())
            return false;

        std::pair<wxString, wxJSONValue> val = m_queue.front();
        m_queue.pop_front();
    
        name = val.first;
        value = val.second;
        return true;
    }

    if(m_map.empty())
        return false;

    std::map<wxString, wxJSONValue>::iterator it = m_map.begin();
    name = it->first;
    value = it->second;
    m_map.erase(it);
    return true;
}

void SignalKClient::get(wxString name)
{
    wxJSONValue request;
    request["method"] = wxString("get");
    request["name"] = name;
    send(request);
}

void SignalKClient::set(wxString name, wxJSONValue &value)
{
    wxJSONValue request;
    request["method"] = wxString("set");
    request["name"] = name;
    request["value"] = value;
    send(request);
}

void SignalKClient::set(wxString name, double value)
{
    wxJSONValue v(value);
    set(name, v);
}

void SignalKClient::set(wxString name, wxString value)
{
    wxJSONValue v(value);
    set(name, v);
}

void SignalKClient::watch(wxString name, bool on)
{
    if(on)
        get(name);
    wxJSONValue request;
    request["method"] = wxString("watch");
    request["name"] = name;
    request["value"] = on;
    send(request);
}

bool SignalKClient::info(wxString name, wxJSONValue &info)
{
    info = m_list[name];
    return !info.IsNull();
}

void SignalKClient::request_list_values()
{
    wxJSONValue request;
    request["method"] = wxString("list");
    send(request);
}

void SignalKClient::send(wxJSONValue &request)
{
    wxJSONWriter writer(wxJSONWRITER_NONE);
    wxString str;
    writer.Write(request, str);
    str += "\n";
    m_sock.Write(str.mb_str(), str.Length());
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
                m_list = wxJSONValue();
                request_list_values();
                m_bRequestingList = true;
            } else
                OnConnected();
            break;

        case wxSOCKET_LOST:
            disconnect();
            break;

        case wxSOCKET_INPUT:
    #define RD_BUF_SIZE    4096
            std::vector<char> data(RD_BUF_SIZE+1);
            event.GetSocket()->Read(&data.front(),RD_BUF_SIZE);
            if(!event.GetSocket()->Error())
            {
                size_t count = event.GetSocket()->LastCount();
                if(count)
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
                wxJSONValue value;
                wxJSONReader reader;
                if(reader.Parse(json_line, &value)) {
                    const wxArrayString& errors = reader.GetErrors();
                    wxString sLogMessage;
                    sLogMessage.Append(wxT("pypilot_pi: Error parsing JSON message - "));
                    sLogMessage.Append( json_line );
                    for(size_t i = 0; i < errors.GetCount(); i++)
                        sLogMessage.append( errors.Item( i ) );
                    wxLogMessage( sLogMessage );
                } else {
                    if(m_bRequestingList) {
                        m_list = value;
                        m_bRequestingList = false;
                        OnConnected();
                    } else {
                        wxArrayString names = value.GetMemberNames();
                        for(unsigned int i=0; i<names.Count(); i++) {
                            if(m_bQueueMode) {
                                if(m_queue.size() >= 4096) {
                                    wxLogMessage( "SignalK client message overflow" );
                                    m_queue.clear();
                                }
                                std::pair<wxString, wxJSONValue> val(names[i], value[names[i]]);
                                m_queue.push_back(val);
                            } else
                                m_map[names[i]] = value[names[i]];
                        }
                    }
                }

                if(line_end > (int)m_sock_buffer.size())
                    m_sock_buffer.clear();
                else
                    m_sock_buffer = m_sock_buffer.substr(line_end+1);
            }
            break;
    }
}
