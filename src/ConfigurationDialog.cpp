/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2019 by Sean D'Epagnier                                 *
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
}

bool ConfigurationDialog::Show( bool show )
{
    if(show) {
        wxFileConfig *pConf = GetOCPNConfigObject();
        pConf->SetPath ( _T( "/Settings/pypilot" ) );
        m_cbAutoDiscover->SetValue(pConf->Read ( _T ( "AutoDiscover" ), true));
        m_cHost->SetSelection(0);
        wxString host = pConf->Read ( _T ( "Host" ), "192.168.14.1" );
        if(m_cHost->GetString(0) != host) {
            m_cHost->Insert(host, 0);
            m_cHost->SetSelection(0);
        }
        m_cbTackingButton->SetValue((bool)pConf->Read ( _T ( "TackingButton" ), 1));
        m_cbCenterButton->SetValue((bool)pConf->Read ( _T ( "CenterButton" ), 1));
        m_cbForwardNMEA->SetValue((bool)pConf->Read ( _T ( "ForwardNMEA" ), 0L ));
        m_cbEnableGraphicOverlay->SetValue((bool)pConf->Read ( _T ( "EnableGraphicOverlay" ), 0L ));
        m_cbTrueNorthMode->SetValue((bool)pConf->Read ( _T ( "TrueNorthMode" ), 0L ));
        m_cbSwitchToNAVMode->SetValue((bool)pConf->Read ( _T ( "SwitchToNAVMode" ), 0L ));

        m_lControlAngles->Clear();
        wxString ControlAngles = pConf->Read ( _T ( "ControlAngles" ), "1;10;" );
        while(ControlAngles.size()) {
            wxString angle = ControlAngles.BeforeFirst(';');
            long a;
            if(angle.ToLong(&a))
                m_lControlAngles->Append(wxString::Format("%ld", a));
            ControlAngles = ControlAngles.AfterFirst(';');
        }
        m_sControlColumns->SetValue(pConf->Read ( _T ( "ControlColumns" ), 3 ));


        Json::Value list = m_pypilot_pi.m_client.list();
        if(!list.isNull()) {
            for(Json::ValueIterator val = list.begin(); val != list.end(); val++)
                std::string name = val.key().asString();
        }
    }
    
    return ConfigurationDialogBase::Show(show);
}

void ConfigurationDialog::DetectedHost(wxString host)
{
    if(m_cHost->GetString(0) != host) {
        m_cHost->SetString(0, host + " (discovered)");
        m_cHost->SetSelection(0);
    }
}

void ConfigurationDialog::OnAboutTacking( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(), _("\
Make the buttons for tacking visible."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAboutCenter( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(), _("\
If enabled, and rudder feedback is working, a button to center the rudder in manual mode appears."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAboutForwardNMEA( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(), _("\
Plugin automatically sends and receives nmea data between opencpn and pypilot.\n\
\n\
The plugin communicates directly to pypilot, but nmea0183 is needed\n\
by other opencpn plugins and for route following.\n\
\n\
Eliminates the need to make the tcp connection in opencpn connection settings.\n\
If you need specific nmea filtering you should disable this, and instead make a tcp connection\n\
to the pypilot host tcp port 20220 in the opencpn connections settings.\n"),
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
This affects compass mode only, and requires the wmm plugin to be active.  The conversion is applied only within the plugin, the autopilot is commanded in the corrected magnetic heading."),
                         "pypilot", wxOK | wxICON_INFORMATION);
    mdlg.ShowModal();
}

void ConfigurationDialog::OnAboutSwitchToNAVMode( wxCommandEvent& event )
{
    wxMessageDialog mdlg(GetOCPNCanvasWindow(),
                         _("Automatically switch pypilot to NAV mode whenever a route is active"),
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

    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/pypilot" ) );
    pConf->Write ( _T ( "AutoDiscover" ), m_cbAutoDiscover->GetValue());
    pConf->Write ( _T ( "Host" ), m_cHost->GetValue().BeforeFirst(' '));
    pConf->Write ( _T ( "TackingButton" ), m_cbTackingButton->GetValue());
    pConf->Write ( _T ( "CenterButton" ), m_cbCenterButton->GetValue());
    pConf->Write ( _T ( "ForwardNMEA" ), m_cbForwardNMEA->GetValue());
    pConf->Write ( _T ( "EnableGraphicOverlay" ), m_cbEnableGraphicOverlay->GetValue());
    pConf->Write ( _T ( "TrueNorthMode" ), m_cbTrueNorthMode->GetValue());
    pConf->Write ( _T ( "SwitchToNAVMode" ), m_cbSwitchToNAVMode->GetValue());

    wxString ControlAngles;
    for(unsigned int i=0; i<m_lControlAngles->GetCount(); i++)
        ControlAngles += m_lControlAngles->GetString(i) + ";";
    pConf->Write ( _T ( "ControlAngles" ), ControlAngles);
    pConf->Write ( _T ( "ControlColumns" ), m_sControlColumns->GetValue());
    
    m_pypilot_pi.ReadConfig();    
}

void ConfigurationDialog::OnClose( wxCommandEvent& event )
{
    Hide();
}

void ConfigurationDialog::OnHost( wxCommandEvent& event )
{
    m_cHost->SetValue(m_cHost->GetValue().BeforeFirst(' '));
}
