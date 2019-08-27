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
v */

#include <vector>

#include "pypilot_pi.h"
#include "pypilotDialog.h"
#include "GainsDialog.h"
#include "ConfigurationDialog.h"
#include "CalibrationDialog.h"
#include "StatisticsDialog.h"

#ifdef __OCPN__ANDROID__
wxWindow *g_Window;
#endif

pypilotDialog::pypilotDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
    : pypilotDialogBase( parent ),
      m_bAPHaveGPS(false), m_bAPHaveWind(false),
      m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
    g_Window = this;
    GetHandle()->setStyleSheet( qtStyleSheet);
    Connect( wxEVT_MOTION, wxMouseEventHandler( pypilotDialog::OnMouseEvent ) );
#endif
    wxFileConfig *pConf = GetOCPNConfigObject();

    pConf->SetPath ( _T( "/Settings/pypilot" ) );

#ifdef __WXGTK__
    Move(0, 0);        // workaround for gtk autocentre dialog behavior
#endif
    Move(pConf->Read ( _T ( "DialogPosX" ), 20L ), pConf->Read ( _T ( "DialogPosY" ), 20L ));

    m_HeadingCommandUpdate = wxDateTime::UNow() - wxTimeSpan::Seconds(5);
    m_HeadingCommand = NAN;
    
    RebuildControlAngles();
    this->GetSizer()->Fit( this );
    this->Layout();
    this->SetSizeHints( GetSize().x, GetSize().y );

    m_ManualTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                          ( pypilotDialog::OnManualTimer ), NULL, this);
    m_RudderPollTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                          ( pypilotDialog::OnRudderPollTimer ), NULL, this);

    Disconnected();
}

pypilotDialog::~pypilotDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T ( "/Settings/pypilot" ) );

    wxPoint p = GetPosition();

    pConf->Write ( _T ( "DialogPosX" ), p.x );
    pConf->Write ( _T ( "DialogPosY" ), p.y );
}


#ifdef __OCPN__ANDROID__ 
wxPoint g_startPos;
wxPoint g_startMouse;
wxPoint g_mouse_pos_screen;

void pypilotDialog::OnMouseEvent( wxMouseEvent& event )
{
    g_mouse_pos_screen = ClientToScreen( event.GetPosition() );
    
    if(event.Dragging()){
        int x = wxMax(0, g_startPos.x + (g_mouse_pos_screen.x - g_startMouse.x));
        int y = wxMax(0, g_startPos.y + (g_mouse_pos_screen.y - g_startMouse.y));
        int xmax = ::wxGetDisplaySize().x - GetSize().x;
        x = wxMin(x, xmax);
        int ymax = ::wxGetDisplaySize().y - (GetSize().y * 2);          // Some fluff at the bottom
        y = wxMin(y, ymax);
        
        g_Window->Move(x, y);
    }
}

void pypilotDialog::OnEvtPinchGesture( wxQT_PinchGestureEvent &event)
{
}

void pypilotDialog::OnEvtPanGesture( wxQT_PanGestureEvent &event)
{
    switch(event.GetState()){
        case GestureStarted:
            g_startPos = GetPosition();
            g_startMouse = event.GetCursorPos(); //g_mouse_pos_screen;
            break;
            
        case GestureFinished:
            break;
            
        case GestureCanceled:
            break;
            
        default:
            break;
    }
    
}
#endif

void pypilotDialog::Disconnected()
{
    m_fgControlAnglesPos->Show(false);
    m_fgControlAnglesNeg->Show(false);
    m_fgControlManual->Show(false);

    wxSize s(100,100);
    SetMinSize(s);
    Fit();
}

void pypilotDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "ap.heading_command")
        m_HeadingCommand = ApplyTrueNorth(value.asDouble());
    else if(name == "ap.heading")
        m_stHeading->SetLabel(wxString::Format("%.1f", ApplyTrueNorth(value.asDouble())));
    else if(name == "ap.mode") {
        m_sAPMode = value.asString();
        m_cMode->SetStringSelection(m_sAPMode);
        RebuildControlAngles();

        SetAPColor(m_sAPMode);
    } else if(name == "ap.enabled") {
        bool enabled = value.asBool();
        m_bAP->SetValue(enabled);

        m_fgControlAnglesPos->Show(enabled);
        m_fgControlAnglesNeg->Show(enabled);
        m_fgControlManual->Show(!enabled);
        if(enabled)
            m_RudderPollTimer.Stop();
        else
            m_RudderPollTimer.Start(500, false);

        SetAPColor(m_cMode->GetStringSelection());

        wxSize s(100, 100);
        SetMinSize(s);
        Fit();
    } else if(name == "ap.tack.state") {
        m_stTackState->SetLabel(value.asString());
        if(value.asString() == "none")
            m_bTack->SetLabel(_("Tack"));
        else
            m_bTack->SetLabel(_("Cancel"));
    } else if(name == "ap.tack.direction") {
        if(value.asString() == "port")
            m_cTackDirection->SetSelection(0);
        else
            m_cTackDirection->SetSelection(1);
    } else if(name == "gps.source") {
        m_bAPHaveGPS = value.asString() != "none";
        UpdateModes();
    } else if(name == "wind.source") {
        m_bAPHaveWind = value.asString() != "none";
        UpdateModes();
    } else if(name == "servo.state") {
        if(m_servoController != "none")
            m_stServoState->SetLabel(value.asString());
    } else if(name == "servo.flags") {
        m_stServoFlags->SetLabel(value.asString());
    } else if(name == "servo.controller") {
        if(value == "none")
            m_stServoState->SetLabel(_("No Motor Controller"));
        else
            m_stServoState->SetLabel(_("OK"));
        m_servoController = value.asString();
    } else if(name == "rudder.angle") {
        wxString str = value.asString();
        bool show_center=!m_bAP->GetValue();
        if(str == "False") {
            str = "";
            show_center=false;
        }

        if(m_bCenter->IsShown() != show_center)
            m_bCenter->Show(show_center);
        
        m_stRudder->SetLabel(wxString::Format("%.1f", value.asDouble()));
    }

    if(!wxIsNaN(m_HeadingCommand) &&
       (wxDateTime::UNow() - m_HeadingCommandUpdate).GetMilliseconds() > 1000) {
        m_stCommand->SetLabel(wxString::Format("%.1f", m_HeadingCommand));
        m_HeadingCommand = NAN;
    }
}

void pypilotDialog::SetAPColor(wxString mode)
{
    wxColour c = *wxBLACK;
    wxString sel = m_cMode->GetStringSelection();
    if(m_bAP->GetValue()) {
        if(mode == "compass")
            c = *wxGREEN;
        else if(mode == "gps")
            c = *wxYELLOW;
        else if(mode == "wind")
            c = *wxBLUE;
        else if(mode == "true wind")
            c = *wxCYAN;
    }
    m_bAP->SetForegroundColour(c);
}

const char **pypilotDialog::GetWatchlist()
{
    static const char *watchlist[] =
        {"ap.enabled", "ap.mode", "ap.heading", "ap.heading_command",
         "ap.tack.state", "ap.tack.direction",
         "gps.source", "wind.source",
         "servo.state", "servo.flags", "servo.controller", 0};
    return watchlist;
}

void pypilotDialog::RebuildControlAngles()
{
    bool shown = m_fgControlAnglesPos->AreAnyItemsShown();

    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/pypilot" ) );
    wxString ControlAngles = pConf->Read ( _T ( "ControlAngles" ), "1;10;110;" );
    while(!m_fgControlAnglesPos->IsEmpty())
        delete m_fgControlAnglesPos->GetItem((size_t)0)->GetWindow();
    while(!m_fgControlAnglesNeg->IsEmpty()) {
        wxWindow *win = m_fgControlAnglesNeg->GetItem((size_t)0)->GetWindow();
        if(win)
            delete win;
        else
            m_fgControlAnglesNeg->Remove(0);
    }

    std::vector<int> angles;
    while(ControlAngles.size()) {
        wxString angle = ControlAngles.BeforeFirst(';');
        long a;
        if(angle.ToLong(&a))
            angles.push_back(a);
        ControlAngles = ControlAngles.AfterFirst(';');
    }

    int cols = pConf->Read ( _T ( "ControlColumns" ), 3 );
    m_fgControlAnglesPos->SetCols(cols);
    m_fgControlAnglesNeg->SetCols(cols);

    for(unsigned int i=0; i<angles.size()+cols-1; i++) {
        if(i < angles.size())
            AddButton(angles[i], m_fgControlAnglesPos);
        unsigned int negind = cols-1-i%cols+i/cols*cols; 
        if(negind < angles.size())
            AddButton(-angles[negind], m_fgControlAnglesNeg);
        else
            m_fgControlAnglesNeg->AddSpacer(0);
    }

    m_fgControlAnglesPos->Show(shown);
    m_fgControlAnglesNeg->Show(shown);
    
    m_bTrueNorthMode = (bool)pConf->Read ( _T ( "TrueNorthMode" ), 0L );
    if(m_bTrueNorthMode && (wxDateTime::UNow() - m_pypilot_pi.m_declinationTime).GetSeconds() > 2000) {
        wxMessageDialog mdlg(GetOCPNCanvasWindow(), _("\
True North mode not possible without declination.\n\nIs the wmm plugin enabled and a gps fix available?"),
                         "pypilot", wxOK | wxICON_WARNING);
        mdlg.ShowModal();
        m_bTrueNorthMode = false;
    }

    Fit();
}

void pypilotDialog::Fit()
{
    GetSizer()->Fit(this);
    pypilotDialogBase::Fit();
    
    // hack to rearrange
    wxSize s = GetSize();
    s.x+=1;
    SetSize(s);
    s.x-=1;
    SetSize(s);
}

void pypilotDialog::OnAP( wxCommandEvent& event )
{
    if(m_bAP->GetValue()) {
        double heading;
        if(m_stHeading->GetLabel().ToDouble(&heading))
            m_pypilot_pi.m_client.set("ap.heading_command", wxRound(heading));
    }
    m_pypilot_pi.m_client.set("ap.enabled", m_bAP->GetValue());
}

void pypilotDialog::OnMode( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("ap.mode", m_cMode->GetStringSelection().mb_str());
}

void pypilotDialog::OnGains( wxCommandEvent& event )
{
    m_pypilot_pi.m_GainsDialog->Show(!m_pypilot_pi.m_GainsDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
}

void pypilotDialog::OnConfiguration( wxCommandEvent& event )
{
    m_pypilot_pi.m_ConfigurationDialog->Show(!m_pypilot_pi.m_ConfigurationDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
}

void pypilotDialog::OnCalibration( wxCommandEvent& event )
{
    m_pypilot_pi.m_CalibrationDialog->Show(!m_pypilot_pi.m_CalibrationDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
}

void pypilotDialog::OnStatistics( wxCommandEvent& event )
{
    (!m_pypilot_pi.m_StatisticsDialog->IsShown());
    m_pypilot_pi.m_StatisticsDialog->Show(!m_pypilot_pi.m_StatisticsDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
#ifdef __OCPN__ANDROID__
    m_pypilot_pi.m_StatisticsDialog->ShowModal();
#endif
}

void pypilotDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void pypilotDialog::OnControlAngle( wxCommandEvent& event )
{
    wxButton *button = static_cast<wxButton*>(event.GetEventObject());
    wxString angle = button->GetLabel(), heading_command = m_stCommand->GetLabel();
    double a, b;
    if(heading_command.ToDouble(&a) && angle.ToDouble(&b)) {
        double cmd = heading_resolve_pos(a + b);
        m_stCommand->SetLabel(wxString::Format("%.1f", cmd));
        m_HeadingCommandUpdate = wxDateTime::UNow();
        if(m_bTrueNorthMode && m_cMode->GetSelection() == 0 /*compass*/)
            cmd -= m_pypilot_pi.m_declination;
        cmd = heading_resolve_pos(cmd);
        m_pypilot_pi.m_client.set("ap.heading_command", cmd);
    }        
}

void pypilotDialog::OnTack( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("ap.tack.state", m_bTack->GetLabel() == _("Tack") ? "begin": "");
}

void pypilotDialog::OnTackDirection( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("ap.tack.direction", m_cTackDirection->GetSelection() ? "port" : "starboard");
}

void pypilotDialog::UpdateModes()
{
    m_cMode->Clear();
    m_cMode->Append("compass");
    if(m_bAPHaveGPS)
        m_cMode->Append("gps");
    if(m_bAPHaveWind)
        m_cMode->Append("wind");
    if(m_bAPHaveGPS && m_bAPHaveWind)
        m_cMode->Append("true wind");
    m_cMode->SetStringSelection(m_sAPMode);
}

void pypilotDialog::Manual(double amount)
{
    m_ManualCommand = amount > 0 ? 1 : -1;
    m_ManualTimeout = wxDateTime::UNow() + wxTimeSpan::Milliseconds(abs(1000.0*amount));
    m_ManualTimer.Start(100);
}

void pypilotDialog::OnManualCenter( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("servo.position_command", 0.0);
}

void pypilotDialog::OnManualTimer( wxTimerEvent & )
{
    if(wxDateTime::UNow() >= m_ManualTimeout) {
        m_ManualCommand = 0;
        m_ManualTimer.Stop();
    }
    //printf("manual %f %d\n", m_ManualCommand, (wxDateTime::UNow() - m_ManualTimeout).GetMilliseconds());
    m_pypilot_pi.m_client.set("servo.command", m_ManualCommand);
}


void pypilotDialog::OnRudderPollTimer( wxTimerEvent & )
{
    m_pypilot_pi.m_client.get("rudder.angle");
}

void pypilotDialog::AddButton(int angle, wxSizer *sizer)
{
    if(m_sAPMode.Contains("wind"))
        angle = -angle;

    wxButton *button = new wxButton( this, wxID_ANY, wxString::Format("%i", angle));
    button->Connect( wxEVT_COMMAND_BUTTON_CLICKED,
                     wxCommandEventHandler( pypilotDialog::OnControlAngle ), NULL, this );
    button->SetMaxSize(wxSize(60, -1));
    sizer->Add( button, 0, wxALL, 5 );
}

double pypilotDialog::ApplyTrueNorth(double value)
{
    if(!m_bTrueNorthMode || m_cMode->GetSelection() != 0 /*compass*/)
        return value;
    return heading_resolve_pos(value + m_pypilot_pi.m_declination);
}
