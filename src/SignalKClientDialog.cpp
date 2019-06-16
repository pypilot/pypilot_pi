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
#include "SignalKClientDialog.h"

SignalKClientDialog::SignalKClientDialog( pypilot_pi &_pypilot_pi, wxWindow* parent)
    : SignalKClientDialogBase(parent),
      m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
         GetHandle()->setStyleSheet( qtStyleSheet);
#endif
}

wxString ValueAsString(Json::Value &value)
{
    if(value.type() == Json::realValue)
        return wxString::Format("%.8g", value.asDouble());
    
    if(value.type() != Json::arrayValue)
        return value.asString();

    std::string ret = "[";
    for(unsigned int i = 0; i<value.size(); i++) {
        if(i > 0)
            ret += ", ";
        ret += ValueAsString(value[i]);
    }
    ret += "]";
    return ret;
}

void SignalKClientDialog::Receive(std::string name, Json::Value &value)
{
    if(m_values.find(name) == m_values.end())
        return;

    m_values[name]->SetLabel(ValueAsString(value));

    wxControl *control = m_controls[name];

    wxTextCtrl *text = dynamic_cast<wxTextCtrl*>(control);
    wxCheckBox *checkbox = dynamic_cast<wxCheckBox*>(control);
    wxSlider *slider = dynamic_cast<wxSlider*>(control);
    wxSpinCtrlDouble *spin = dynamic_cast<wxSpinCtrlDouble*>(control);
    wxChoice *choice = dynamic_cast<wxChoice*>(control);

    if(text)
        text->SetValue(value.asString());
    else if(checkbox)
        checkbox->SetValue(value.asBool());
    else if(slider) {
        Json::Value info;
        if(m_pypilot_pi.m_client.info(name, info)) {
            double min_value = info["min"].asDouble(), max_value = info["max"].asDouble();
            slider->SetValue((value.asDouble() - min_value) * (max_value - min_value) * 1000.0);
        }
    } else if(spin)
        spin->SetValue(value.asDouble());
    else if(choice)
        choice->SetStringSelection(value.asString());
}

std::list<std::string> &SignalKClientDialog::GetWatchlist()
{
//    std::list<std::string> watchlist;
    m_watchlist.clear();

    Json::Value list = m_pypilot_pi.m_client.list();

    if(!list.isNull())
        for(Json::ValueIterator val = list.begin(); val != list.end(); val++)
            if((*val)["type"] != "SensorValue")
                m_watchlist.push_back(val.key().asString());
    
    return m_watchlist;
}

bool SignalKClientDialog::Show( bool show )
{
#ifdef __OCPN__ANDROID__  // wxqt broken reenumarate
    if(m_values.size())
        return SignalKClientDialogBase::Show(show);
#endif

    m_fgSizer->DeleteWindows();
    
    m_values.clear();
    m_controls.clear();

    Json::Value list = m_pypilot_pi.m_client.list();
    if(show && !list.isNull()) {
        for(Json::ValueIterator val = list.begin(); val != list.end(); val++) {
            std::string name = val.key().asString();
            m_fgSizer->Add( new wxStaticText(m_scrolledWindow, wxID_ANY, name), 0, wxALL, 5 );
            m_values[name] = new wxStaticText(m_scrolledWindow, wxID_ANY, "");
            m_fgSizer->Add( m_values[name], 0, wxALL|wxEXPAND, 5 );
            
            std::string t = (*val)["type"].asString();            
#if 0            
            if(t == "Property") {
                wxTextCtrl *tb = new wxTextCtrl(m_scrolledWindow, wxID_ANY);
                m_fgSizer->Add(tb, 0, wxEXPAND);
                m_controls[name] = tb;
            } else
#endif
            if(t == "BooleanProperty") {
                wxCheckBox *cb = new wxCheckBox(m_scrolledWindow, wxID_ANY, "");
                m_fgSizer->Add(cb, 0, wxEXPAND);
                m_controls[name] = cb;
                cb->Connect(wxEVT_CHECKBOX,  wxCommandEventHandler( SignalKClientDialog::OnCommand ), NULL, this);
            } else if(t == "RangeProperty") {
#ifdef __OCPN__ANDROID__
                bool useSlider = true;
#else
                bool useSlider = false;
#endif
                if(useSlider) {
                    wxSlider *s = new wxSlider(m_scrolledWindow, wxID_ANY, 0, 0, 1000);
                    m_fgSizer->Add( s, 0, wxEXPAND);
                    m_controls[name] = s;
                    s->Connect( wxEVT_SLIDER, wxCommandEventHandler( SignalKClientDialog::OnCommand ), NULL, this);
                } else {
                    wxSpinCtrlDouble  *s = new wxSpinCtrlDouble(m_scrolledWindow, wxID_ANY);
                    double min = (*val)["min"].asDouble(), max = (*val)["max"].asDouble();
                    s->SetRange(min, max);
                    s->SetIncrement(wxMin(1, (max - min) / 100.0));
                    s->SetDigits(-log(s->GetIncrement()) / log(10) + 1);
                    m_fgSizer->Add( s, 0, wxEXPAND);
                    m_controls[name] = s;
                    s->Connect( wxEVT_SPINCTRLDOUBLE, wxSpinDoubleEventHandler( SignalKClientDialog::OnSpin ), NULL, this);
                }
            } else if(t == "EnumProperty") {
                wxChoice *c = new wxChoice(m_scrolledWindow, wxID_ANY);
                Json::Value choices = (*val)["choices"];
                for(Json::ValueIterator choice = choices.begin(); choice != choices.end(); choice++)
                    c->Append(choice->asString());
                m_fgSizer->Add( c, 0, wxEXPAND);
                m_controls[name] = c;
                c->Connect( wxEVT_CHOICE, wxCommandEventHandler( SignalKClientDialog::OnCommand ), NULL, this);
            } else if(t == "ResettableValue") {
                wxButton *b = new wxButton(m_scrolledWindow, wxID_ANY, "Reset");
                m_fgSizer->Add( b, 0, wxEXPAND);
                m_controls[name] = b;
                b->Connect( wxEVT_BUTTON, wxCommandEventHandler( SignalKClientDialog::OnCommand ), NULL, this);
            } else { // really just a spacer since the user cannot modify this
                m_fgSizer->Add( new wxStaticText(m_scrolledWindow, wxID_ANY, ""), 0, wxEXPAND);
                if(t == "SensorValue") // sensors aren't in watchlist, too much bandwidth
                    m_pypilot_pi.m_client.get(val.key().asString());
            }
        }

        m_fgSizer->Fit(m_scrolledWindow);
        Layout();
    }
    return SignalKClientDialogBase::Show(show);
}

// unfortunatly GetEventObject is broken on android so we do this
void SignalKClientDialog::SendValues()
{
    std::string name;
    wxControl *control;
    for(std::map<std::string, wxControl*>::iterator i = m_controls.begin();
        i!=m_controls.end(); i++) {
        control = i->second;

        wxChoice *choice = dynamic_cast<wxChoice*>(control);
        if(choice) { // for some reason, has focus doesn't work on choice
            wxString value = m_values[i->first]->GetLabel();
            
            if(choice->GetStringSelection() != value) {
                m_pypilot_pi.m_client.set(i->first, choice->GetStringSelection());
                return;
            }
        } else
            if(control && control->HasFocus()) {
                name = i->first;
                break;
            }
    }

    if(name.empty())
        return;

    wxTextCtrl *text = dynamic_cast<wxTextCtrl*>(control);
    wxCheckBox *checkbox = dynamic_cast<wxCheckBox*>(control);
    wxSlider *slider = dynamic_cast<wxSlider*>(control);
    wxSpinCtrlDouble *spin = dynamic_cast<wxSpinCtrlDouble*>(control);
    wxButton *button = dynamic_cast<wxButton*>(control);

    if(text)
        m_pypilot_pi.m_client.set(name, text->GetValue());
    else if(checkbox)
        m_pypilot_pi.m_client.set(name, checkbox->GetValue());
    else if(slider) {
        Json::Value info;
        if(m_pypilot_pi.m_client.info(name, info)) {
            double min_value = info["min"].asDouble(), max_value = info["max"].asDouble();
            double v = slider->GetValue() / 1000.0 * (max_value - min_value) + min_value;
            m_pypilot_pi.m_client.set(name, v);
        }
    } else if(spin)
        m_pypilot_pi.m_client.set(name, spin->GetValue());
    else if(button)
        m_pypilot_pi.m_client.set(name, 0.0);
}

void SignalKClientDialog::OnOK( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}
