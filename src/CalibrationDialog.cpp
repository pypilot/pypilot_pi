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
#include "CalibrationDialog.h"

CalibrationDialog::CalibrationDialog(pypilot_pi &_pypilot_pi, wxWindow* parent) :
    CalibrationDialogBase(parent),
    m_pypilot_pi(_pypilot_pi)
{
}

CalibrationDialog::~CalibrationDialog()
{
}

void CalibrationDialog::Receive(wxString &name, wxJSONValue &value)
{
    if(name == "imu.pitch" || name == "imu.roll") {
        if(name == "imu.pitch")
            m_pitch = jsondouble(value);
        else {
            double roll = jsondouble(value);
            m_stPitchRoll->SetLabel(wxString::Format("%.1f / %.1f", m_pitch, roll));
        }
    } else if(name == "imu.alignmentCounter")
        m_gLevel->SetValue(100-jsondouble(value));
    else if(name == "imu.compass_calibration_age")
        m_stCompassCalibrationAge->SetLabel(value.AsString());
}

const char **CalibrationDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"imu.pitch", "imu.roll", "imu.alignmentCounter", "imu.compass_calibration_age", 0};

    return watchlist;
}

void CalibrationDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void CalibrationDialog::OnLevel( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("imu.alignmentCounter", 100);
}
