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

#include <deque>
#include <map>

#include <wx/wx.h>
#include <wx/socket.h>

#include "wxJSON/jsonreader.h"
#include "wxJSON/jsonwriter.h"

class SignalKClient : public wxEvtHandler
{
public:
    SignalKClient(bool queue_mode = true, bool request_list = true);

    void connect(wxString host, int port=0);
    void disconnect() { m_sock.Close(); }
    bool connected() { return m_sock.IsConnected(); }
    virtual bool receive(wxString &name, wxJSONValue &value);

    void get(wxString name);
    void set(wxString name, wxJSONValue &value);
    void set(wxString name, double value);
    void set(wxString name, wxString value);
    void watch(wxString name, bool on=true);

    bool info(wxString name, wxJSONValue &info);

protected:
    virtual void OnConnected() = 0;
    virtual void OnDisconnected() = 0;
    wxJSONValue m_list;

private:
    void request_list_values();
    void send(wxJSONValue &request);
    void OnSocketEvent(wxSocketEvent& event);

    wxSocketClient      m_sock;
    std::string         m_sock_buffer;
    std::deque<std::pair<wxString, wxJSONValue> > m_queue;
    std::map<wxString, wxJSONValue> m_map;

    bool m_bQueueMode;
    
    bool m_bRequestList, m_bRequestingList;

DECLARE_EVENT_TABLE()
};
