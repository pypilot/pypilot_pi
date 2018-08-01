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

static JSONCPP_STRING StringValue(Json::Value &value)
{
    if(value.type() == Json::realValue) {
        char buf[16];
        snprintf(buf, sizeof buf, "%.3f", value.asDouble());
        return buf;
    }

    if(value.type() == Json::arrayValue) {    
        JSONCPP_STRING ret = "[";
        for(unsigned int i = 0; i < value.size(); i++) {
            if(i)
                ret += ", ";
            ret += StringValue(value[i]);
        }
        ret += "]\n";
        return ret;
    }

    return value.asString();
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
    else if(name == "imu.accel.calibration")
        m_stAccelCalibration->SetLabel(StringValue(value)), Fit();
    else if(name == "imu.accel.calibration.age")
        m_stAccelCalibrationAge->SetLabel(value.asString());
    else if(name == "imu.accel.calibration.locked")
        m_cbAccelCalibrationLocked->SetValue(value.asBool());
    else if(name == "imu.compass.calibration")
        m_stCompassCalibration->SetLabel(StringValue(value)), Fit();
    else if(name == "imu.compass.calibration.age")
        m_stCompassCalibrationAge->SetLabel(value.asString());
    else if(name == "imu.compass.calibration.locked")
        m_cbCompassCalibrationLocked->SetValue(value.asBool());
    else if(name == "imu.heading_offset") {
        if(!m_lastOffsetTime.IsValid() || (wxDateTime::Now() - m_lastOffsetTime).GetSeconds() > 3)
            m_sHeadingOffset->SetValue(jsondouble(value));
    } else if(name == "servo.rudder") {
        m_rudder = value.asDouble();
        m_stRudder->SetLabel(wxString::Format("%.3f", value.asDouble()));
    } else if(name == "servo.rudder.offset")
        m_rudder_offset = value.asDouble();
    else if(name == "servo.rudder.scale")
        m_rudder_scale = value.asDouble();
    else if(name == "servo.rudder.range")
        m_sRudderRange->SetValue(value.asDouble());
}

const char **CalibrationDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"imu.pitch", "imu.roll", "imu.alignmentCounter",
         "imu.accel.calibration", "imu.accel.calibration.age",
         "imu.accel.calibration.locked",
         "imu.compass.calibration", "imu.compass.calibration.age",
         "imu.compass.calibration.locked",
         "imu.heading_offset",
         "servo.rudder", "servo.rudder.offset", "servo.rudder.scale", "servo.rudder.range"};

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

void CalibrationDialog::OnRudderCentered( wxCommandEvent& event )
{
    double rudder_pos = m_rudder / m_rudder_scale - m_rudder_offset + .5;
    m_pypilot_pi.m_client.set("servo.rudder.offset", .5 - rudder_pos);
}

void CalibrationDialog::OnRudderAtRange( wxCommandEvent& event )
{
    double scale = m_sRudderRange->GetValue() * m_rudder_scale / m_rudder;
    m_pypilot_pi.m_client.set("servo.rudder.scale", scale);
}

void CalibrationDialog::OnRudderRange( wxSpinEvent& event )
{
    m_pypilot_pi.m_client.set("servo.rudder.range", m_sRudderRange->GetValue());
}

void CalibrationDialog::OnAboutRudderCalibration( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("To calibrate rudder feedback, first manually center the rudder, and press 'Centered'.\n\nNext, turn the rudder to starboard as far as the autopilot maximum range should be, and enter this value in degrees and press 'At Range'."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void CalibrationDialog::OnCalibrationLocked( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("imu.accel.calibration.locked", m_cbAccelCalibrationLocked->GetValue());
    m_pypilot_pi.m_client.set("imu.compass.calibration.locked", m_cbCompassCalibrationLocked->GetValue());
}


void CalibrationDialog::OnAboutCalibrationLocked( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("You may wish to lock the compass calibration against automatically updating"), "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}
