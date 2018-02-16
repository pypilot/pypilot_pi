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

#include <list>

#include "pypilotUI.h"
class pypilot_pi;

struct Gain;

class GainsDialog : public GainsDialogBase
{
public:
    GainsDialog( pypilot_pi &_pypilot_pi, wxWindow* parent);
    ~GainsDialog();

    bool Show( bool show=true );

    void Receive(wxString &name, wxJSONValue &value);
    std::list<wxString> GetWatchlist();

private:
    void OnClose( wxCommandEvent& event );
    void OnTimer( wxTimerEvent & );
    void OnGainSlider( wxScrollEvent& event );

    wxTimer m_Timer;
    std::list<wxString> m_watchlist;
    std::map<wxString, Gain*> m_gains;
    pypilot_pi &m_pypilot_pi;
};
