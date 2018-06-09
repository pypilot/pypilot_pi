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

void CalibrationDialog::Receive(std::string name, Json::Value &value)
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
        m_stCompassCalibrationAge->SetLabel(value.asString());
    else if(name == "imu.heading_offset") {
        if(!m_lastOffsetTime.IsValid() || (wxDateTime::Now() - m_lastOffsetTime).GetSeconds() > 3)
            m_sHeadingOffset->SetValue(jsondouble(value));
    } else if(name == "imu.compass_calibration_locked")
        m_cbCalibrationLocked->SetValue(value.asBool());
}

const char **CalibrationDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"imu.pitch", "imu.roll", "imu.alignmentCounter", "imu.compass_calibration_age", "imu.heading_offset", "imu.compass_calibration_locked", 0};

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

void CalibrationDialog::OnAboutLevel( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("Press the level button when the boat is sitting level in the water \
to align the inertial sensors used by the autopilot.\n\n\
This alignment is critical for the autopilot to work correctly, and also for the compass to calibrate automatically."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void CalibrationDialog::OnHeadingOffset( wxSpinEvent& event )
{
    m_pypilot_pi.m_client.set("imu.heading_offset", m_sHeadingOffset->GetValue());
    m_lastOffsetTime = wxDateTime::Now();
}

void CalibrationDialog::OnAboutHeadingOffset( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("You may manually adjust the alignment of the compass. The autopilot may work without the correct alignment, but the reported headings will not be correct.\n\nThe autopilot may also work better depending on control algorithm if the heading is correctly aligned."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void CalibrationDialog::OnCalibrationLocked( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("imu.compass_calibration_locked", m_cbCalibrationLocked->GetValue());
}


void CalibrationDialog::OnAboutCalibrationLocked( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("You may wish to lock the compass calibration against automatically updating"), "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}
