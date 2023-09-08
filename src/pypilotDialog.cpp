/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2020 by Sean D'Epagnier                                 *
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
#include "SettingsDialog.h"
#include "StatisticsDialog.h"

#ifdef __OCPN__ANDROID__
wxWindow *g_Window;
#endif

class TackDialog : public TackDialogBase
{
public:
    TackDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
        : TackDialogBase(parent),
              m_pypilot_pi(_pypilot_pi)
        {
        }

private:
    void OnTackPort( wxCommandEvent& event )       { tack("port"); }
    void OnClose( wxCommandEvent& event )          { tack("none"); }
    void OnTackStarboard( wxCommandEvent& event )  { tack("starboard"); }

    void tack(wxString direction) {
        m_pypilot_pi.m_client.set("ap.tack.direction", direction);
        m_pypilot_pi.m_client.set("ap.tack.state", "begin");
        Hide();
    }

    pypilot_pi &m_pypilot_pi;    
};

pypilotDialog::pypilotDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
    : pypilotDialogBase( parent ),
      m_bAPHaveRudder(false),
      m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
    g_Window = this;
    GetHandle()->setStyleSheet( qtStyleSheet);
    Connect( wxEVT_MOTION, wxMouseEventHandler( pypilotDialog::OnMouseEvent ) );
#endif
    wxFileConfig *pConf = GetOCPNConfigObject();

    pConf->SetPath ( _T( "/PlugIns/pypilot" ) );

#ifdef __WXGTK__
    Move(0, 0);        // workaround for gtk autocentre dialog behavior
#endif
    Move(pConf->Read ( _T ( "DialogPosX" ), 20L ), pConf->Read ( _T ( "DialogPosY" ), 20L ));

    m_HeadingCommandUpdate = wxDateTime::UNow() - wxTimeSpan::Seconds(5);
    m_HeadingCommand = m_pypilot_pi.HeadingCommand();

    ShowTacking();
    RebuildControlAngles();

    this->GetSizer()->Fit( this );
    this->Layout();
    //this->SetSizeHints( GetSize().x, GetSize().y );

    m_ManualTimer.Connect(wxEVT_TIMER, wxTimerEventHandler
                          ( pypilotDialog::OnManualTimer ), NULL, this);

    m_TackDialog = new TackDialog(m_pypilot_pi, this);
   
    Disconnected();
}

pypilotDialog::~pypilotDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T ( "/PlugIns/pypilot" ) );

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
    m_tack_direction = "none";

    m_fgControlAnglesPos->Show(false);
    m_fgControlAnglesNeg->Show(false);
    m_fgControlManual->Show(false);

    Fit();
}

void pypilotDialog::SetEnabled(bool enabled)
{
    m_bAP->SetValue(enabled);

    m_fgControlAnglesPos->Show(enabled);
    m_fgControlAnglesNeg->Show(enabled);
    m_fgControlManual->Show(!enabled);

    SetAPColor();
    ShowCenter();
    ShowTacking();

    Fit();
}

void pypilotDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "imu.error") {
        m_imuerror = value.asString();
        UpdateStatus();
    } else if(name == "imu.warning") {
        m_imuwarning = value.asString();
        UpdateStatus();
    } else if(name == "ap.heading_command")
        m_HeadingCommand = ApplyTrueNorth(value.asDouble());
    else if(name == "ap.heading")
        m_stHeading->SetLabel(wxString::Format(" %05.1f", ApplyTrueNorth(value.asDouble())));
    else if(name == "ap.mode") {
        RebuildControlAngles();
        SetAPColor();
        wxString mode = value.asString();
        if(m_cMode->FindString(mode, true)==-1)
            m_cMode->Append(mode);
        m_cMode->SetStringSelection(mode);
    } else if(name == "ap.modes") {
        m_cMode->Clear();
        for(unsigned int i=0; i < value.size(); i++)
            m_cMode->Append(value[i].asString());
        m_cMode->SetStringSelection(m_pypilot_pi.m_mode);
    } else if(name == "ap.enabled")
        SetEnabled(value.asBool());
    else if(name == "ap.tack.state") {
        m_stTackState->SetLabel(value.asString());
        if(value.asString() == "none")
            m_bTack->SetLabel(_("Tack"));
        else
            m_bTack->SetLabel(_("Cancel"));
    } else if(name == "ap.tack.direction")
        m_tack_direction = value.asString();
    else if(name == "servo.state") {
        if(m_servoController != "none")
            m_stServoState->SetLabel(value.asString());
    } else if(name == "servo.flags") {
        m_servoflags = value.asString();
        UpdateStatus();
    } else if(name == "servo.controller") {
        if(value == "none")
            m_stServoState->SetLabel(_("No Motor Controller"));
        else
            m_stServoState->SetLabel(_("OK"));
        m_servoController = value.asString();
    } else if(name == "rudder.angle") {
        wxString str = value.asString();
        m_bAPHaveRudder = str != "false";
        if(m_bAPHaveRudder)
            m_stRudder->SetLabel(wxString::Format("%.1f", value.asDouble()));
        ShowCenter();
    }

    if(!isnan(m_HeadingCommand) &&
       (wxDateTime::UNow() - m_HeadingCommandUpdate).GetMilliseconds() > 1000) {
        m_stCommand->SetLabel(wxString::Format("%05.1f", m_HeadingCommand));
        m_HeadingCommand = NAN;
    }
}

void pypilotDialog::SetAPColor()
{
    wxString mode = m_pypilot_pi.m_mode;
    wxColour c = *wxBLACK;
    wxString sel = m_cMode->GetStringSelection();
    if(m_bAP->GetValue()) {
        if(mode == "compass")
            c = *wxGREEN;
        else if(mode == "gps")
            c = *wxYELLOW;
        else if(mode == "nav")
            c = wxColour(255, 0, 255);
        else if(mode == "wind")
            c = *wxBLUE;
        else if(mode == "true wind")
            c = *wxCYAN;
    }
    m_bAP->SetForegroundColour(c);
}

std::map<std::string, double> &pypilotDialog::GetWatchlist()
{
    static std::map<std::string, double> list;
    list.clear();
    // continuous updates for these
    static const char *watchlist[] =
        {"imu.error", "imu.warning",
         "ap.enabled", "ap.mode", "ap.modes", "ap.heading", "ap.heading_command",
         "ap.tack.state", "ap.tack.direction",
         "servo.state", "servo.flags", "servo.controller"};
    for(unsigned int i=0; i<(sizeof watchlist)/(sizeof *watchlist); i++)
        list[watchlist[i]] = .2;
    
    // get updates twice a second
    list["rudder.angle"] = .5;
    return list;
}

void pypilotDialog::RebuildControlAngles()
{
    m_cMode->SetStringSelection(m_pypilot_pi.m_mode);

    bool shown = m_fgControlAnglesPos->AreAnyItemsShown();

    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/pypilot" ) );
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

void pypilotDialog::UpdateStatus()
{
    wxString status;
    if(!m_imuerror.empty())
        status += m_imuerror + ' ';
    if(!m_imuwarning.empty())
        status += m_imuwarning + ' ';
    status += m_servoflags;
    
    m_stStatus->SetLabel(status);
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

void pypilotDialog::OnManualEvents( wxMouseEvent& event )
{
    double speed, length;
    int timeout;
    
    if(event.GetEventObject() == m_bManualPortLong)
        speed = 1, timeout = 300;
    else if(event.GetEventObject() == m_bManualPortShort)
        speed = .6, timeout = 200;
    else if(event.GetEventObject() == m_bManualStarboardShort)
        speed = -.6, timeout = 200;
    else if(event.GetEventObject() == m_bManualStarboardLong)
        speed = -1, timeout = 300;
    else
        return;

    speed *= m_pypilot_pi.m_ConfigurationDialog->m_sManualControlSpeed->GetValue();
      
    if(event.LeftDown()) {
        m_ManualCommand = speed;
        if(!m_ManualTimer.IsRunning()) {
            m_ManualTimeout = wxDateTime::UNow();
            wxTimerEvent e;
            OnManualTimer(e);
            m_ManualTimer.Start(timeout);
        }
    }

    if(event.ButtonUp()) {
        m_ManualCommand = 0;
        long ms = (wxDateTime::UNow() - m_ManualTimeout).GetMilliseconds().ToLong();
        m_ManualTimer.Start(fmax(timeout-ms, 0));
    }

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

void pypilotDialog::OnSettings( wxCommandEvent& event )
{
    m_pypilot_pi.m_SettingsDialog->Show(!m_pypilot_pi.m_SettingsDialog->IsShown());
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
        double cmd;
        if(m_pypilot_pi.m_mode.Contains("wind"))
            cmd = heading_resolve(a + b);
        else
            cmd = heading_resolve_pos(a + b);
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
    if(m_tack_direction != "none" && !m_pypilot_pi.m_ConfigurationDialog->m_cbAlwaysConfirmTacking->GetValue())
        m_pypilot_pi.m_client.set("ap.tack.state", m_bTack->GetLabel() == _("Tack") ? "begin": "none");
    else
        m_TackDialog->Show();
}

void pypilotDialog::OnManualCenter( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("servo.position_command", 0.0);
}

void pypilotDialog::OnManualTimer( wxTimerEvent & )
{
    if(!m_ManualCommand ||
       wxDateTime::UNow() >= m_ManualTimeout + wxTimeSpan::Milliseconds(5000)) {
        m_ManualCommand = 0;
        m_ManualTimer.Stop();
    }

    m_pypilot_pi.m_client.set("servo.command", m_ManualCommand);

    m_ManualCommand *= 1.05; // acceleration
    m_ManualCommand = fmax(fmin(m_ManualCommand, 1), -1);
}

void pypilotDialog::ShowCenter()
{
    bool show_center=!m_bAP->GetValue();
    if(!m_bAPHaveRudder || !m_pypilot_pi.m_ConfigurationDialog->m_cbCenterButton->GetValue())
        show_center=false;

    if(m_bCenter->IsShown() != show_center) {
        m_bCenter->Show(show_center);
        Fit();
    }
}

void pypilotDialog::ShowTacking()
{
    bool show_tacking = false;
    if(m_bAP->GetValue()) {
        wxFileConfig *pConf = GetOCPNConfigObject();
        pConf->SetPath ( _T( "/Settings/pypilot" ) );
        show_tacking  = (bool)pConf->Read ( _T ( "TackingButton" ), 1);
    }

    if(m_bTack->IsShown() != show_tacking)
        m_fgSizerTacking->Show(show_tacking);
}

void pypilotDialog::AddButton(int angle, wxSizer *sizer)
{
    if(m_pypilot_pi.m_mode.Contains("wind"))
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
