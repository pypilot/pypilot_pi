/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Sean D'Epagnier                                 *
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

#include <wx/wx.h>
#include <wx/socket.h>

#include "wxJSON/jsonreader.h"
#include "wxJSON/jsonwriter.h"

class SignalKClient : public wxEvtHandler
{
public:
    SignalKClient();

    void connect(wxString host, int port=0);
    bool connected() { return m_sock.IsConnected(); }
    bool receive(wxJSONValue &value);
    void get(wxString name);
    void set(wxString name, wxJSONValue &value);
    void watch(wxString name, bool on=true);
    void request_list_values();

protected:
    virtual void OnConnected() = 0;
    virtual void OnDisconnected() = 0;

private:
    void send(wxJSONValue &request);
    void OnSocketEvent(wxSocketEvent& event);

    wxSocketClient      m_sock;
    std::string         m_sock_buffer;
    std::deque<wxJSONValue> m_values;
DECLARE_EVENT_TABLE()
};
