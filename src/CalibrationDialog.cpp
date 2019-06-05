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
#ifdef __OCPN__ANDROID__
        GetHandle()->setStyleSheet( qtStyleSheet);
#endif
}

CalibrationDialog::~CalibrationDialog()
{
}

static wxString StringValue(Json::Value &value)
{
    if(value.type() == Json::realValue) {
        char buf[16];
        snprintf(buf, sizeof buf, "%.3f", value.asDouble());
        return buf;
    }

    if(value.type() == Json::arrayValue) {    
        wxString ret = "[";
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
    if(name == "imu.pitch")
        m_pitch = jsondouble(value);
    else if(name == "imu.roll") {
        double roll = jsondouble(value);
        m_stPitchRoll->SetLabel(wxString::Format("%.1f / %.1f", m_pitch, roll));
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
    } else if(name == "rudder.angle")
        m_stRudderAngle->SetLabel(wxString::Format("%.3f", value.asDouble()));
    else if(name == "rudder.offset")
        m_stRudderOffset->SetLabel(wxString::Format("%.3f", value.asDouble()));
    else if(name == "rudder.scale")
        m_stRudderScale->SetLabel(wxString::Format("%.3f", value.asDouble()));
    else if(name == "rudder.nonlinearity")
        m_stRudderNonlinearity->SetLabel(wxString::Format("%.3f", value.asDouble()));
    else if(name == "rudder.range")
        m_sRudderRange->SetValue(value.asDouble());
}

std::list<std::string> &CalibrationDialog::GetWatchlist()
{
    static std::list<std::string> list;
    if(list.size() == 0) {
        list.push_back("imu.pitch");
        list.push_back("imu.roll");
        list.push_back("imu.alignmentCounter");
        list.push_back("imu.accel.calibration");
        list.push_back("imu.accel.calibration.age");
        list.push_back("imu.accel.calibration.locked");
        list.push_back("imu.compass.calibration");
        list.push_back("imu.compass.calibration.age");
        list.push_back("imu.compass.calibration.locked");
        list.push_back("imu.heading_offset");
        list.push_back("rudder.angle");
        list.push_back("rudder.offset");
        list.push_back("rudder.scale");
        list.push_back("rudder.nonlinearity");
        list.push_back("rudder.range");
    }
    return list;
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
    m_pypilot_pi.m_client.set("rudder.calibration_state", "centered");
}

void CalibrationDialog::OnRudderStarboardRange( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("rudder.calibration_state", "starboard range");
}

void CalibrationDialog::OnRudderPortRange( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("rudder.calibration_state", "portboard range");
}

void CalibrationDialog::OnRudderRange( wxSpinEvent& event )
{
    m_pypilot_pi.m_client.set("rudder.range", m_sRudderRange->GetValue());
}

void CalibrationDialog::OnAboutRudderCalibration( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("To calibrate rudder feedback:\n\
1) manually center the rudder and press 'Centered'.\n\
2) set 'Range' to the angle the autopilot maximum range should be\n\
3) manually turn rudder to starboard this maximum angle and press 'Starboard Range'\n\
4) manually turn rudder to port this maximum angle and press 'Port Range'"),
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
