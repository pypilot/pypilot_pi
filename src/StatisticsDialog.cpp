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
}

StatisticsDialog::~StatisticsDialog()
{
}

void StatisticsDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "imu.uptime")
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
}

const char **StatisticsDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"imu.uptime", "ap.runtime", "servo.watts", "servo.amp_hours", "servo.voltage", "servo.controller_temp", "servo.motor_temp", 0};
    return watchlist;
}

void StatisticsDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void StatisticsDialog::OnResetAmpHours( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("servo.amp_hours", 0.0);
}
