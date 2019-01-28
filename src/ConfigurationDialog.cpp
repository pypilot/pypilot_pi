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
#include "SignalKClientDialog.h"

enum ui_place {SERVO, TACKING};
struct ui_setting {
    const char *signalk_name;
    const char *name, *units;
    double step;
    enum ui_place placement;
    wxStaticText *label;
    wxSpinButton *spin;
} ui_settings[] = {{"servo.period", "Period", "Seconds", .1, SERVO},
                   {"servo.max_current", "Max Current", "Amps", .1, SERVO},
                   {"ap.tack.angle", "Angle", "Degrees", 1, TACKING},
                   {"ap.tack.speed", "Speed", "Degrees/s", 1, TACKING},
                   {"ap.tack.complete", "Complete", "Degrees", 1, TACKING},
                   {"ap.tack.delay", "Delay", "Seconds", .5, TACKING}
};


ConfigurationDialog::ConfigurationDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
    : ConfigurationDialogBase(parent),
      m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
    GetHandle()->setStyleSheet( qtStyleSheet);
#endif

    for(unsigned int i=0; i<(sizeof ui_settings) / (sizeof *ui_settings); i++) {
        ui_setting &s = ui_settings[i];
        wxStaticBoxSizer *sbSizer = s.placement == SERVO ? m_sbSizerServo : m_sbSizerTacking;
            
        wxFlexGridSizer* fgSizer = new wxFlexGridSizer( 1, 0, 0, 0 );
        fgSizer->SetFlexibleDirection( wxBOTH );
        fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
        
        wxStaticText *stname = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _(s.name), wxDefaultPosition, wxDefaultSize, 0 );
        stname->Wrap( -1 );
        fgSizer->Add( stname, 0, wxALL, 3 );
        
        s.label = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, "-------", wxDefaultPosition, wxDefaultSize, 0 );
        s.label->Wrap( -1 );
        fgSizer->Add( s.label, 0, wxALL, 3 );
        
        s.spin = new wxSpinButton( sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxSP_VERTICAL );
        fgSizer->Add( s.spin, 0, wxALL, 3 );
        s.spin->SetRange(-1, 1);

	s.spin->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( ConfigurationDialog::OnSpin ), NULL, this );
        
        wxStaticText *stUnits = new wxStaticText( sbSizer->GetStaticBox(), wxID_ANY, _(s.units), wxDefaultPosition, wxDefaultSize, 0 );
        stUnits->Wrap( -1 );
        fgSizer->Add( stUnits, 0, wxALL, 3 );
            
        sbSizer->Add( fgSizer, 1, wxEXPAND, 5 );

        m_watchlist.push_back(s.signalk_name);
    }
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
    for(unsigned int i=0; i<(sizeof ui_settings) / (sizeof *ui_settings); i++) {
        ui_setting &s = ui_settings[i];
   
        if(name == s.signalk_name)
            s.label->SetLabel(jsonformat("%.1f", value));
    }
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

void ConfigurationDialog::OnSpin(wxSpinEvent& event )
{
    for(unsigned int i=0; i<(sizeof ui_settings) / (sizeof *ui_settings); i++) {
        ui_setting &s = ui_settings[i];
        if(!s.spin->HasFocus())
            continue;
    
        double d;
        if(s.label->GetLabel().ToDouble(&d)) {
            d = s.spin->GetValue() * s.step;
            s.label->SetLabel(wxString::Format("%.1f", d));
            s.spin->SetValue(0);
        }
    }
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

void ConfigurationDialog::OnSignalKClient( wxCommandEvent& event )
{
    m_pypilot_pi.m_SignalKClientDialog->Show(!m_pypilot_pi.m_SignalKClientDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
}


void ConfigurationDialog::OnOk( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();

    for(unsigned int i=0; i<(sizeof ui_settings) / (sizeof *ui_settings); i++) {
        ui_setting &s = ui_settings[i];
        double x;
        if(s.label->GetLabel().ToDouble(&x))
            m_pypilot_pi.m_client.set(s.signalk_name, x);
    }

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
