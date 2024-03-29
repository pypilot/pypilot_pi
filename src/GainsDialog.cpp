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

#include "pypilotUI.h"
#include "pypilot_pi.h"
#include "GainsDialog.h"

struct Gain
{
    Gain(wxWindow *parent, wxString name, double min_val, double max_val);
    ~Gain();

    void set(double val) {
        int v = val * 1000.0;
        if(v == last_val)
            return;

        last_val = v;
        v = abs(v);
        if(v < gauge->GetRange()) {
            gauge->SetValue(v);
            gauge->SetBackgroundColour(val > 0 ? *wxRED : val < 0 ? *wxGREEN : *wxLIGHT_GREY);
        } else {
            gauge->SetValue(0);
            gauge->SetBackgroundColour(*wxBLUE);
        }
    }

    wxFlexGridSizer *sizer;
    wxStaticText *value;
    wxGauge *gauge;
    wxSlider *slider;
    double min, max;
    bool need_update, initial;
    wxDateTime last_change;
    int last_val;
    int slider_val(double gain_val) { return (gain_val-min)*1000/(max - min); }

    wxStaticText *stname;
};

Gain::Gain(wxWindow *parent, wxString name, double min_val, double max_val)
    : min(min_val), max(max_val), need_update(false), initial(true)
{
    sizer = new wxFlexGridSizer( 0, 1, 0, 0 );
    sizer->AddGrowableRow( 2 );
    sizer->SetFlexibleDirection( wxVERTICAL );

    stname = new wxStaticText( parent, wxID_ANY, name);
    sizer->Add( stname, 0, wxALL, 5 );
    value = new wxStaticText( parent, wxID_ANY, "   N/A   ");
    sizer->Add( value, 0, wxALL, 5 );

    wxFlexGridSizer *hsizer = new wxFlexGridSizer( 1, 0, 0, 0 );
    hsizer->AddGrowableRow( 0 );
    hsizer->SetFlexibleDirection( wxVERTICAL );
                
    gauge = new wxGauge( parent, -1, 1000, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL );
    hsizer->Add( gauge, 0, wxALL|wxEXPAND, 5 );
    slider = new wxSlider( parent, wxID_ANY, 0, 0, 1000, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL| wxSL_INVERSE);
    hsizer->Add( slider, 0, wxALL|wxEXPAND, 5 );

    sizer->Add( hsizer, 1, wxEXPAND, 5 );

    last_val = 1e6;
}

Gain::~Gain()
{
    delete stname;
    delete value;
    delete gauge;
    delete slider;
    delete sizer;
}

GainsDialog::GainsDialog(pypilot_pi &_pypilot_pi, wxWindow* parent) :
    GainsDialogBase(parent),
    m_pypilot_pi(_pypilot_pi)
{
#ifdef __OCPN__ANDROID__
        GetHandle()->setStyleSheet( qtStyleSheet);
#endif
    wxFileConfig *pConf = GetOCPNConfigObject();

    pConf->SetPath ( _T( "/PlugIns/pypilot" ) );

    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( GainsDialog::OnTimer ), NULL, this);
    m_Timer.Start(100);

#ifdef __WXGTK__
    Move(0, 0);        // workaround for gtk autocentre dialog behavior
#endif
    Move(pConf->Read ( _T ( "GainsDialogPosX" ), 20L ), pConf->Read ( _T ( "GainsDialogPosY" ), 20L ));
    SetSize(pConf->Read ( _T ( "GainsDialogW" ), 550L ), pConf->Read ( _T ( "GainsDialogH" ), 230L ));
}

GainsDialog::~GainsDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T ( "/PlugIns/pypilot" ) );

    wxPoint p = GetPosition();

    pConf->Write ( _T ( "GainsDialogPosX" ), p.x );
    pConf->Write ( _T ( "GainsDialogPosY" ), p.y );

    wxSize s = GetSize();
    pConf->Write ( _T ( "GainsDialogW" ), s.x );
    pConf->Write ( _T ( "GainsDialogH" ), s.y );
}

bool GainsDialog::Show( bool show )
{
    if(show && !IsShown()) {
        EnumeratePilots();
        EnumerateGains();
    }
    Fit();
    return GainsDialogBase::Show(show);
}

static bool Begins (std::string const &str, std::string const &beginning)
{
    if (str.length() < beginning.length())
        return false;
    return (0 == str.compare (0, beginning.length(), beginning));
}

static bool hasEnding (std::string const &str, std::string const &ending)
{
    if (str.length() < ending.length())
        return false;
    return (0 == str.compare (str.length() - ending.length(), ending.length(), ending));
}

void GainsDialog::Receive(std::string name, Json::Value &value)
{
    if(name == "ap.version") {
        std::string strversion = value.asString(), erase = "pypilot ";
        size_t pos = strversion.find(erase);
        if (pos != std::string::npos)
            strversion.erase(pos, erase.length());
        double version = std::stod(strversion);
        if(version < .4) {
            m_cProfile->Disable();
            m_bAddProfile->Disable();
            m_bRemoveProfile->Disable();
        }
    } else if(name == "profile") {
        if(value.isNumeric())
            m_profile = wxString::Format("%g", value.asDouble());
        else
            m_profile = value.asCString();
        int i = m_cProfile->FindString(m_profile);
        if(i >= 0)
            m_cProfile->SetSelection(i);
    } else if(name == "profiles") {
        wxString profile = m_cProfile->GetStringSelection();
        if(!profile)
            profile = m_profile;
        m_cProfile->Clear();
        for(unsigned int i=0; i<value.size(); i++)
            m_cProfile->Append(value[i].asString());
        int i = m_cProfile->FindString(m_profile);
        if(i >= 0)
            m_cProfile->SetSelection(i);
    } else if(name == "ap.pilot") {
        int i = m_cPilot->FindString(value.asCString());
        if(i >= 0) {
            m_cPilot->SetSelection(i);
            EnumerateGains();
        }
    } else if(hasEnding(name, "gain")) {
        name = name.substr(0, name.size()-4);
        if(m_gains.find(name) != m_gains.end())
            m_gains[name]->set(jsondouble(value));
    } else if(Begins(name, "ap.pilot")) {
        double val = jsondouble(value);
        m_gainvals[name] = val;
    }
}

void GainsDialog::OnProfile( wxCommandEvent& event )
{
    m_pypilot_pi.m_client.set("profile", m_cProfile->GetStringSelection());
}

void GainsDialog::OnAddProfile( wxCommandEvent& event )
{
    wxTextEntryDialog dialog(this, _("Add New Profile"), _("Profile"));
    if(dialog.ShowModal() == wxID_OK) {
        wxString profile = dialog.GetValue();
        int i = m_cProfile->Append(profile);
        m_cProfile->SetSelection(i);
        SendProfiles();
        m_pypilot_pi.m_client.set("profile", profile);
    }
}

void GainsDialog::OnRemoveProfile( wxCommandEvent& event )
{
    wxMessageDialog dialog(this, _("Remove Current Profile?"), _("Profile"), wxOK | wxCANCEL | wxICON_QUESTION);
    if(dialog.ShowModal() == wxID_OK) {
        int ind = m_cProfile->GetSelection();
        m_cProfile->Delete(ind);
        SendProfiles();
    }
}

void GainsDialog::SendProfiles()
{
    Json::Value profiles;
    for(unsigned int i=0; i<m_cProfile->GetCount(); i++) {
        wxString str = m_cProfile->GetString(i);
        profiles.append(Json::Value(str.mb_str()));
    }

    m_pypilot_pi.m_client.set("profiles", profiles);
}    

void GainsDialog::OnPilot( wxCommandEvent& event )
{
    int ind = m_cPilot->GetSelection();
    if(ind >= 0)
        m_pypilot_pi.m_client.set("ap.pilot", m_cPilot->GetString(ind));
}

void GainsDialog::OnClose( wxCommandEvent& event )
{
    Hide();
    m_pypilot_pi.UpdateWatchlist();
}

void GainsDialog::OnTimer( wxTimerEvent & )
{
    if(!IsShown())
        return;

    for(std::map<std::string, Gain*>::iterator i = m_gains.begin(); i != m_gains.end(); i++) {
        Gain *g = i->second;
        if(g->need_update) {
            g->need_update = false;
            double value = g->slider->GetValue() / 1000.0 * (g->max - g->min) + g->min;
            m_pypilot_pi.m_client.set(i->first, value);
        }

        std::string name = i->first;
        if(m_gainvals.find(name) == m_gainvals.end())
            continue;

        double gain_val = m_gainvals[name];
        int slider_val = g->slider_val(gain_val);
        if(g->slider->GetValue() != slider_val &&
           (!g->last_change.IsValid() || (wxDateTime::UNow() - g->last_change).GetMilliseconds() > 1000)) {
            g->slider->SetValue(slider_val);
            g->value->SetLabel(wxString::Format("%.5f", gain_val));
        } else if(g->initial) {
            g->initial = false;  // if gain is also set to zero
            g->value->SetLabel(wxString::Format("%.5f", gain_val));
        }        
    }
}

void GainsDialog::OnGainSlider( wxScrollEvent& event )
{
    wxSlider *slider = static_cast<wxSlider*>(event.GetEventObject());
    for(std::map<std::string, Gain*>::iterator i = m_gains.begin(); i != m_gains.end(); i++) {
        Gain *g = i->second;
        if(g->slider == slider) {
            int slider_val = g->slider->GetValue();
            double gain_value = slider_val * (g->max - g->min) / 1000.0 + g->min;
            g->value->SetLabel(wxString::Format("%.5f", gain_value));
            g->last_change = wxDateTime::UNow();
            g->need_update = true;
            break;
        }
    }
}

std::map<std::string, double> &GainsDialog::GetWatchlist()
{
    return m_watchlist;
}

void GainsDialog::EnumeratePilots()
{
    std::list<std::string> gains;
    m_pypilot_pi.m_client.GetSettings(gains, "AutopilotGain");

    // enumerate the pilots from the gains
    std::map<std::string, bool> pilots;
    for(std::list<std::string>::iterator i = gains.begin(); i != gains.end(); i++) {
        if(i->length() > 9) {
            std::string p = i->substr(0, 9);
            int c = p.compare("ap.pilot.");
            if(c == 0) {
                int end = i->find(".", 9);
                if(end > 0) {
                    p = i->substr(9, end-9);
                    pilots[p] = true;
                }
            }
        }
    }

    m_cPilot->Clear();
    for(std::map<std::string, bool>::iterator pilot = pilots.begin(); pilot != pilots.end(); pilot++)
        m_cPilot->Append(pilot->first);
}

void GainsDialog::EnumerateGains()
{
    int ind = m_cPilot->GetSelection();
    wxString pilot = ind >= 0 ? m_cPilot->GetString(ind) : "";

    while(!m_fgGains->IsEmpty())
        m_fgGains->Detach(0);

    for(std::map<std:: string, Gain*>::iterator i = m_gains.begin(); i != m_gains.end(); i++) {
        Gain *g = i->second;
        delete g;
    }

    std::list<std::string> gains;
    m_pypilot_pi.m_client.GetSettings(gains, "AutopilotGain");
    m_watchlist.clear();
    m_watchlist["profile"] = 0;
    m_watchlist["profiles"] = 0;
    m_watchlist["ap.pilot"] = 0;
    m_gains.clear();
    
    for(std::list<std::string>::iterator i = gains.begin(); i != gains.end(); i++) {
        std::string name = *i;
        
        m_watchlist[name] = .5;
        m_watchlist[name+"gain"] = .2;

        int ret = name.find(("ap.pilot." + pilot + ".").mb_str());
        if(ret < 0)
            continue;

        Json::Value info;
        m_pypilot_pi.m_client.info(name, info);
        double min_val = jsondouble(info["min"]), max_val = jsondouble(info["max"]);

        int start = name.rfind(".");
        std::string lname = name;
        if(start >=0 )
            lname = name.substr(start + 1);
        Gain *g = new Gain(m_swGains, lname, min_val, max_val);
        int events[] = {wxEVT_SCROLL_TOP, wxEVT_SCROLL_BOTTOM,
                        wxEVT_SCROLL_LINEUP, wxEVT_SCROLL_LINEDOWN,
                        wxEVT_SCROLL_PAGEUP, wxEVT_SCROLL_PAGEDOWN,
                        wxEVT_SCROLL_THUMBTRACK, wxEVT_SCROLL_THUMBRELEASE,
                        wxEVT_SCROLL_CHANGED};
        for(unsigned int i=0; i<(sizeof events) / (sizeof *events); i++)
            g->slider->Connect( events[i], wxScrollEventHandler( GainsDialog::OnGainSlider ), NULL, this );
        m_fgGains->Add( g->sizer, 1, wxEXPAND, 5 );
        m_gains[name] = g;
    }

    wxSize s = m_swGains->GetSize();
    s.x+=1;
    m_swGains->SetSize(s);
    m_swGains->Fit();

    s = GetSize();
    Fit();
    s.x+=1;
    SetSize(s);

//    s = GetSize();
//    SetSize(s);
//        Fit();
}

