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
#include "ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
    : ConfigurationDialogBase(parent),
      m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
        GetHandle()->setStyleSheet( qtStyleSheet);
#endif
    m_sPeriod->SetRange(1, 30);
    m_sMaxCurrent->SetRange(0, 600);
}

ConfigurationDialog::~ConfigurationDialog()
{
}

bool ConfigurationDialog::Show( bool show )
{
    if(show) {
        wxFileConfig *pConf = GetOCPNConfigObject();
        pConf->SetPath ( _T( "/Settings/pypilot" ) );
        m_cHost->Insert(pConf->Read ( _T ( "Host" ), "192.168.14.1" ), 0);
        m_cHost->SetSelection(0);
        m_cbForwardnmea->SetValue((bool)pConf->Read ( _T ( "Forwardnema" ), 0L ));
        m_cbEnableGraphicOverlay->SetValue((bool)pConf->Read ( _T ( "EnableGraphicOverlay" ), 0L ));
        m_cbTrueNorthMode->SetValue((bool)pConf->Read ( _T ( "TrueNorthMode" ), 0L ));

        m_lControlAngles->Clear();
        wxString ControlAngles = pConf->Read ( _T ( "ControlAngles" ), "1;10;110;" );
        while(ControlAngles.size()) {
            wxString angle = ControlAngles.BeforeFirst(';');
            long a;
            if(angle.ToLong(&a))
                m_lControlAngles->Append(wxString::Format("%ld", a));
            ControlAngles = ControlAngles.AfterFirst(';');
        }
        m_sControlColumns->SetValue(pConf->Read ( _T ( "ControlColumns" ), 3 ));
    }
    return ConfigurationDialogBase::Show(show);
}

void ConfigurationDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "servo.period") {
        m_sPeriod->SetValue(jsondouble(value) * 10);
        m_stPeriod->SetLabel(jsonformat("%.1f", value));
    } else if(name == "servo.max_current") {
        m_sMaxCurrent->SetValue(jsondouble(value) * 10);
        m_stMaxCurrent->SetLabel(jsonformat("%.1f", value));
    } else if(name == "servo.min_speed")
        m_sMinSpeed->SetValue(jsondouble(value)*100);
    else if(name == "servo.max_speed")
        m_sMaxSpeed->SetValue(jsondouble(value)*100);
    else if(name == "servo.max_controller_temp")
        m_sMaxControllerTemp->SetValue(jsondouble(value));
    else if(name == "servo.max_motor_temp")
        m_sMaxMotorTemp->SetValue(jsondouble(value));
}

const char **ConfigurationDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"servo.period", "servo.max_current", "servo.min_speed", "servo.max_speed", "servo.max_controller_temp", "servo.max_motor_temp", 0};
    return watchlist;
}

void ConfigurationDialog::OnAboutForwardnema( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(), _("\
Eliminates the need to make the tcp connection to the autopilot from the OpenCPN connections list"),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAboutEnableOverlay( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("Displays lines on the chart showing the autopilot's configured headings"),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAboutTrueNorth( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("Converts displayed headings to true north rather than magnetic north.\n\
This affects compass mode only, and requires the wmm plugin to be active.  The conversion is applied only within the plugin, the autopilot is commanded in the correct magnetic heading."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAddControlAngle( wxCommandEvent& event )
{
    int angle = m_sControlAngle->GetValue();
    unsigned int i;
    for(i=0; i<m_lControlAngles->GetCount(); i++) {
        long a;
        m_lControlAngles->GetString(i).ToLong(&a);
        if(angle < a)
            break;
        if(angle == a)
            return;
    }
    m_lControlAngles->Insert(wxString::Format("%d", angle), i);
}

void ConfigurationDialog::OnRemoveControlAngle( wxCommandEvent& event )
{
    int selection = m_lControlAngles->GetSelection();
    if(selection >= 0)
        m_lControlAngles->Delete(selection);
}

static void HandleSpin(wxSpinButton *s, wxStaticText *st)
{
    double d;
    if(st->GetLabel().ToDouble(&d)) {
        d = s->GetValue() / 10.0;
        st->SetLabel(wxString::Format("%.1f", d));
    }
}

void ConfigurationDialog::OnPeriod( wxSpinEvent& event )
{
    HandleSpin(m_sPeriod, m_stPeriod);
}

void ConfigurationDialog::OnMaxCurrent( wxSpinEvent& event )
{
    HandleSpin(m_sMaxCurrent, m_stMaxCurrent);
}

void ConfigurationDialog::OnInformation( wxCommandEvent& event )
{
#ifdef __OCPN__ANDROID__
        wxMessageDialog mdlg(GetOCPNCanvasWindow(), "\
Visit http://www.github.com/pypilot/pypilot_pi",
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
#endif
    wxLaunchDefaultBrowser("http://www.github.com/pypilot/pypilot_pi");
}

void ConfigurationDialog::OnOk( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();

    double x;
    if(m_stPeriod->GetLabel().ToDouble(&x))
        m_pypilot_pi.m_client.set("servo.period", x);
    if(m_stMaxCurrent->GetLabel().ToDouble(&x))
        m_pypilot_pi.m_client.set("servo.max_current", x);
    m_pypilot_pi.m_client.set("servo.min_speed", m_sMinSpeed->GetValue()/100.0);
    m_pypilot_pi.m_client.set("servo.max_speed", m_sMaxSpeed->GetValue()/100.0);
    m_pypilot_pi.m_client.set("servo.max_controller_temp", m_sMaxControllerTemp->GetValue());
    m_pypilot_pi.m_client.set("servo.max_motor_temp", m_sMaxMotorTemp->GetValue());

    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/pypilot" ) );
    pConf->Write ( _T ( "Host" ), m_cHost->GetValue().BeforeFirst(' '));
    pConf->Write ( _T ( "Forwardnema" ), m_cbForwardnmea->GetValue());
    pConf->Write ( _T ( "EnableGraphicOverlay" ), m_cbEnableGraphicOverlay->GetValue() );
    pConf->Write ( _T ( "TrueNorthMode" ), m_cbTrueNorthMode->GetValue() );

    wxString ControlAngles;
    for(unsigned int i=0; i<m_lControlAngles->GetCount(); i++)
        ControlAngles += m_lControlAngles->GetString(i) + ";";
    pConf->Write ( _T ( "ControlAngles" ), ControlAngles );
    pConf->Write ( _T ( "ControlColumns" ), m_sControlColumns->GetValue() );
    
    m_pypilot_pi.ReadConfig();    
}

void ConfigurationDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void ConfigurationDialog::OnHost( wxCommandEvent& event )
{
    m_cHost->SetValue(m_cHost->GetValue().BeforeFirst(' '));
}
