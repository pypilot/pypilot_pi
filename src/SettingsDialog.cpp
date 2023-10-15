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

#include "pypilotUI.h"
#include "pypilot_pi.h"
#include "pypilotClientDialog.h"

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(pypilot_pi &_pypilot_pi, wxWindow* parent) :
    SettingsDialogBase(parent),
    m_pypilot_pi(_pypilot_pi)
{
    m_settings_time = wxDateTime::UNow();
}

void SettingsDialog::Receive(std::string name, Json::Value &value)
{
    if(m_settings.find(name) != m_settings.end())
        m_settings_values[name] = value.asDouble();
    if((wxDateTime::UNow() - m_settings_time).GetMilliseconds() > 3000) {
        for(std::map<std::string, double>::iterator i = m_settings_values.begin(); i != m_settings_values.end(); i++)
            m_settings[i->first]->SetValue(i->second);
        m_settings_time = wxDateTime::UNow();
    }
}

std::map<std::string, double> &SettingsDialog::GetWatchlist()
{
    static std::map<std::string, double> list;
    if(list.size())
        return list;

    std::list<std::string> settings;
    m_pypilot_pi.m_client.GetSettings(settings, "units");
    if(settings.size() == 0)
        return list;

    double period = 0.5;
    for(std::list<std::string>::iterator i = settings.begin(); i != settings.end(); i++) {
        Json::Value &clist = m_pypilot_pi.m_client.list();
        Json::Value setting = clist[*i];
        wxSpinCtrlDouble *s = new wxSpinCtrlDouble(this, wxID_ANY);
        double min = setting["min"].asDouble(), max = setting["max"].asDouble();
        s->SetRange(min, max);
        s->SetIncrement(wxMin(1, (max - min) / 100.0));
        s->SetDigits(-log(s->GetIncrement()) / log(10) + 1);
        m_fgSettings->Add(new wxStaticText(this, wxID_ANY, *i), 0, wxALL, 5 );
        m_fgSettings->Add(s, 0, wxALL | wxEXPAND);
        m_fgSettings->Add(new wxStaticText(this, wxID_ANY, setting["units"].asString()), 0, wxALL, 5 );
        m_settings[*i] = s;
        s->Connect( wxEVT_SPINCTRLDOUBLE, wxSpinDoubleEventHandler( SettingsDialog::OnSpin ), NULL, this);
        list[*i] = period;
    }
    Fit();

    return list;
}

void SettingsDialog::OnpypilotClient( wxCommandEvent& event )
{
    m_pypilot_pi.m_pypilotClientDialog->Show(!m_pypilot_pi.m_pypilotClientDialog->IsShown());
    m_pypilot_pi.UpdateWatchlist();
}

void SettingsDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void SettingsDialog::OnSpin(wxSpinDoubleEvent& event )
{
    for(std::map<std::string, wxSpinCtrlDouble*>::iterator i = m_settings.begin();
        i != m_settings.end(); i++) {
        wxSpinCtrlDouble *s = i->second;
#ifdef __OCPN__ANDROID__
        if(!s->HasFocus())
            continue;
#else
        if(event.GetEventObject() != s)
            continue;
#endif
        std::string name = i->first;
        m_pypilot_pi.m_client.set(name, s->GetValue());
        m_settings_time = wxDateTime::UNow();
    }
}
