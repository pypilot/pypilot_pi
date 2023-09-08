/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2023 by Sean D'Epagnier                                 *
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

#include "pypilotUI.h"

class pypilot_pi;

class SettingsDialog : public SettingsDialogBase
{
public:
    SettingsDialog( pypilot_pi &_pypilot_pi, wxWindow* parent);

    void Receive(std::string name, Json::Value &value);
    std::map<std::string, double> &GetWatchlist();

private:
    void OnpypilotClient( wxCommandEvent& event );
    void OnClose( wxCommandEvent& event );
    void OnSpin(wxSpinDoubleEvent& event );

    pypilot_pi &m_pypilot_pi;

    std::map<std::string, wxSpinCtrlDouble*> m_settings;

    std::map<std::string, double> m_settings_values;
    wxDateTime m_settings_time;
};
