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

#include <deque>
#include <map>
#include <list>

#include <wx/wx.h>
#include <wx/socket.h>

#include <json/json.h>

class pypilotClient : public wxEvtHandler
{
public:
    pypilotClient(bool queue_mode = true, bool request_list = true);

    void connect(wxString host, int port=0);
    void disconnect();
    bool connected() { return m_sock.IsConnected(); }
    virtual bool receive(std::string &name, Json::Value &value);

    void set(std::string name, Json::Value &value);
    void set(std::string name, double value);
    void set(std::string name, std::string &value);
    void set(std::string name, const char *value);
    void watch(std::string name, bool on=true, double period=0);

    bool info(std::string name, Json::Value &info);
    Json::Value &list() { return m_list; }
    void update_watchlist(std::map<std::string, double> &watchlist);

    void GetSettings(std::list<std::string> &settings, std::string member);
    
protected:
    virtual void OnConnected() = 0;
    virtual void OnDisconnected() = 0;
    Json::Value m_list;

private:
    void OnSocketEvent(wxSocketEvent& event);
    void OnTimer( wxTimerEvent & );

    wxSocketClient      m_sock;
    std::string         m_sock_buffer;
    std::deque<std::pair<std::string, Json::Value> > m_queue;
    std::map<std::string, Json::Value> m_map;

    bool m_bQueueMode;
    
    bool m_bRequestList;

    std::map<std::string, double> m_watchlist;

    wxTimer m_timer;

DECLARE_EVENT_TABLE()
};
