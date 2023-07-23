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

#include "pypilotUI.h"
#include "pypilot_pi.h"
#include "StatisticsDialog.h"

StatisticsDialog::StatisticsDialog(pypilot_pi &_pypilot_pi, wxWindow* parent) :
    StatisticsDialogBase(parent),
    m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
    GetHandle()->setStyleSheet( qtStyleSheet);
#endif
}

StatisticsDialog::~StatisticsDialog()
{
}

void StatisticsDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "ap.version")
        m_stVersion->SetLabel(value.asString());
    else if(name == "imu.uptime")
        m_stUptime->SetLabel(value.asString());
    else if(name == "ap.runtime")
        m_stAPRuntime->SetLabel(value.asString());
    else if(name == "servo.watts")
        m_stWatts->SetLabel(jsonformat("%.2f", value));
    else if(name == "servo.amp_hours")
        m_stAmpHours->SetLabel(jsonformat("%.2f", value));
    else if(name == "servo.voltage")
        m_stVoltage->SetLabel(jsonformat("%.2f", value));
    else if(name == "servo.controller_temp")
        m_stControllerTemp->SetLabel(jsonformat("%.1f", value));
    else if(name == "servo.motor_temp")
        m_stMotorTemp->SetLabel(jsonformat("%.1f", value));
    else if(wxString(name).EndsWith(".source")) {
        if(m_sources.find(name) == m_sources.end()) {
            m_fgStats->Add( new wxStaticText(this, wxID_ANY, name), 0, wxALL, 5);
            wxStaticText *s = new wxStaticText(this, wxID_ANY, "N/A");
            m_sources[name] = s;
            m_fgStats->Add( s, 0, wxALL, 5);
            m_fgStats->Add( 0, 0, 1, wxEXPAND, 5 );
            Fit();
        }
        m_sources[name]->SetLabel(value.asString());
    }
}

std::map<std::string, double> &StatisticsDialog::GetWatchlist()
{
    static std::map<std::string, double> watchlist;
    watchlist.clear();

    static const char *c_watchlist[] =
        {"ap.version", "imu.uptime", "ap.runtime", "servo.watts", "servo.amp_hours", "servo.voltage", "servo.controller_temp", "servo.motor_temp"};

    for(unsigned int  i=0; i<(sizeof c_watchlist)/(sizeof *c_watchlist); i++)
        watchlist[c_watchlist[i]] = 1;

    Json::Value list = m_pypilot_pi.m_client.list();
    for(Json::ValueIterator val = list.begin(); val != list.end(); val++) {
        std::string name = val.key().asString();
        if(wxString(name).EndsWith(".source"))
            watchlist[name] = 0;
    }

    return watchlist;
}

void StatisticsDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
#ifdef __OCPN__ANDROID__
//    EndModal();
#endif
}

void StatisticsDialog::OnResetAmpHours( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("servo.amp_hours", 0.0);
}
