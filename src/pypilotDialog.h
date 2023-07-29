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

#ifdef __OCPN__ANDROID__
#include <wx/qt/private/wxQtGesture.h>
#endif

#include "pypilotUI.h"

class pypilot_pi;

class pypilotDialog : public pypilotDialogBase
{
public:
    pypilotDialog( pypilot_pi &_pypilot_pi, wxWindow* parent);
    ~pypilotDialog();

#ifdef __OCPN__ANDROID__
    void OnMouseEvent( wxMouseEvent& event );
    void OnEvtPinchGesture( wxQT_PinchGestureEvent &event);
    void OnEvtPanGesture( wxQT_PanGestureEvent &event);
#endif

    void Disconnected();

    void SetEnabled(bool enabled);
    void Receive(std::string name, Json::Value &value);
    void SetAPColor();
    std::map<std::string, double> &GetWatchlist();

    void RebuildControlAngles();
    void ShowTacking();
    void Fit();
    
private:
    void UpdateStatus();
    
    void OnAP( wxCommandEvent& event );
    void OnMode( wxCommandEvent& event );
    void OnManualEvents( wxMouseEvent& event );
    void OnGains( wxCommandEvent& event );
    void OnConfiguration( wxCommandEvent& event );
    void OnCalibration( wxCommandEvent& event );
    void OnSettings( wxCommandEvent& event );
    void OnStatistics( wxCommandEvent& event );
    void OnClose( wxCommandEvent& event );
    void OnControlAngle( wxCommandEvent& event );
    void OnTack( wxCommandEvent& event );

    void OnManualCenter( wxCommandEvent& );
    void OnManualTimer( wxTimerEvent & );
    void ShowCenter();

    void AddButton(int angle, wxSizer *sizer);

    bool m_bAPHaveRudder;
    
    double ApplyTrueNorth(double value);

    double m_HeadingCommand;
    wxDateTime m_HeadingCommandUpdate;

    double m_ManualCommand;
    wxDateTime m_ManualTimeout;
    wxTimer m_ManualTimer, m_RudderPollTimer;
    
    bool m_bTrueNorthMode;
    pypilot_pi &m_pypilot_pi;
    wxString m_servoController, m_imuerror, m_imuwarning, m_servoflags;
};
