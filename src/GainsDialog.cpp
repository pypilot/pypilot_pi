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

    wxFlexGridSizer *sizer;
    wxStaticText *value;
    wxGauge *gauge;
    wxSlider *slider;
    double min, max;
    bool need_update;
    wxDateTime last_change;
    double slider_val;
};

Gain::Gain(wxWindow *parent, wxString name, double min_val, double max_val)
    : min(min_val), max(max_val), need_update(false), last_change(wxDateTime::Now()), slider_val(0)
{
    sizer = new wxFlexGridSizer( 0, 1, 0, 0 );
    sizer->AddGrowableRow( 2 );
    sizer->SetFlexibleDirection( wxVERTICAL );

    wxStaticText *stname = new wxStaticText( parent, wxID_ANY, name);
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
}

GainsDialog::GainsDialog(pypilot_pi &_pypilot_pi, wxWindow* parent) :
    GainsDialogBase(parent),
    m_pypilot_pi(_pypilot_pi)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    pConf->SetPath ( _T( "/Settings/pypilot" ) );

    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( GainsDialog::OnTimer ), NULL, this);
    m_Timer.Start(500);

#ifdef __WXGTK__
    Move(0, 0);        // workaround for gtk autocentre dialog behavior
#endif
    Move(pConf->Read ( _T ( "GainsDialogPosX" ), 20L ), pConf->Read ( _T ( "GainsDialogPosY" ), 20L ));
    SetSize(pConf->Read ( _T ( "GainsDialogW" ), 550L ), pConf->Read ( _T ( "GainsDialogH" ), 230L ));
}

GainsDialog::~GainsDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T ( "/Settings/pypilot" ) );

    wxPoint p = GetPosition();

    pConf->Write ( _T ( "GainsDialogPosX" ), p.x );
    pConf->Write ( _T ( "GainsDialogPosY" ), p.y );

    wxSize s = GetSize();
    pConf->Write ( _T ( "GainsDialogW" ), s.x );
    pConf->Write ( _T ( "GainsDialogH" ), s.y );
}

bool GainsDialog::Show( bool show )
{
    if(show) {
        while(!m_fgGains->IsEmpty())
            m_fgGains->Remove(0);
        m_watchlist.clear();
        std::list<wxString> gains;
        m_pypilot_pi.m_client.GetGains(gains);
        for(std::list<wxString>::iterator i = gains.begin(); i != gains.end(); i++) {
            wxString name = *i;
            m_watchlist.push_back(name);
            m_watchlist.push_back(name+"gain");

            wxJSONValue info;
            m_pypilot_pi.m_client.info(name, info);
            double min_val = jsondouble(info["min"]), max_val = jsondouble(info["max"]);

            Gain *g = new Gain(m_swGains, name, min_val, max_val);
            g->slider->Connect( wxEVT_SCROLL_CHANGED,
                     wxScrollEventHandler( GainsDialog::OnGainSlider ), NULL, this );
            m_fgGains->Add( g->sizer, 1, wxEXPAND, 5 );
            m_gains[name] = g;
        }
    }
    return GainsDialogBase::Show(show);
}

void GainsDialog::Receive(wxString &name, wxJSONValue &value)
{
    if(name.EndsWith("gain")) {
        name = name.Left(name.Length()-4);
        if(m_gains.find(name) != m_gains.end()) {
            Gain *g = m_gains[name];
            double val = jsondouble(value);
            double v = fabs(val) * 1000.0;
            if(v < g->gauge->GetRange()) {
                g->gauge->SetValue(v);
                g->gauge->SetBackgroundColour(val > 0 ? *wxRED : val < 0 ? *wxGREEN : *wxLIGHT_GREY);
            } else {
                g->gauge->SetValue(0);
                g->gauge->SetBackgroundColour(*wxBLUE);
            }
        }
    } else if(m_gains.find(name) != m_gains.end()) {
        Gain *g = m_gains[name];
        g->value->SetLabel(jsonformat("%.5f", value));
        g->slider_val = (jsondouble(value)-g->min)*1000/(g->max - g->min);
    }
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

    for(std::map<wxString, Gain*>::iterator i = m_gains.begin(); i != m_gains.end(); i++) {
        Gain *g = i->second;
        if(g->need_update) {
            g->need_update = false;
            double value = g->slider->GetValue() / 1000.0 * (g->max - g->min) + g->min;
            m_pypilot_pi.m_client.set(i->first, value);
        }
                
        if(g->slider->GetValue() != g->slider_val &&
           (wxDateTime::Now() - g->last_change).GetMilliseconds() > 1000)
            g->slider->SetValue(g->slider_val);
    }
}

void GainsDialog::OnGainSlider( wxScrollEvent& event )
{
    wxSlider *slider = static_cast<wxSlider*>(event.GetEventObject());
    for(std::map<wxString, Gain*>::iterator i = m_gains.begin(); i != m_gains.end(); i++) {
        Gain *g = i->second;
        if(g->slider == slider) {
            g->need_update = true;
            g->last_change = wxDateTime::Now();
            break;
        }
    }
}

std::list<wxString> GainsDialog::GetWatchlist()
{
    return m_watchlist;
}
