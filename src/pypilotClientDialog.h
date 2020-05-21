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

#include <map>
#include <list>

#include "pypilotUI.h"

class pypilot_pi;

class pypilotClientDialog : public pypilotClientDialogBase
{
public:
    pypilotClientDialog( pypilot_pi &_pypilot_pi, wxWindow* parent);
    ~pypilotClientDialog() {}

    void Receive(std::string name, Json::Value &value);
    std::map<std::string, double> &GetWatchlist();

    bool Show( bool show=true );

private:
    void OnCommand(wxCommandEvent &event) { SendValues(); }
    void OnSpin(wxSpinDoubleEvent &event) { SendValues(); }

    void SendValues();

    void OnOK( wxCommandEvent& event );

    std::map<std::string, wxStaticText*> m_values;
    std::map<std::string, wxControl*> m_controls;

    pypilot_pi &m_pypilot_pi;
};
