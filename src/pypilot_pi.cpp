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

#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/stdpaths.h>

#ifdef __MSVC__
#include "msvcdefs.h"
#endif

#include "wxJSON/jsonreader.h"
#include "wxJSON/jsonwriter.h"

#include "pydc.h"

#include "pypilot_pi.h"

#include "pypilotDialog.h"
#include "ConfigurationDialog.h"
#include "StatisticsDialog.h"
#include "CalibrationDialog.h"

#include "icons.h"


double heading_resolve(double degrees)
{
    while(degrees < -180)
        degrees += 360;
    while(degrees >= 180)
        degrees -= 360;
    return degrees;
}

wxString jsonformat(const char *format, wxJSONValue &value)
{
    double d;
    if(value.IsDouble())
        d = value.AsDouble();
    else {
        wxString str = value.AsString();
        if(!str.ToDouble(&d))
            return str;
    }
    return wxString::Format(format, d);
}

double jsondouble(wxJSONValue &value)
{
    if(value.IsDouble())
        return value.AsDouble();
    double d;
    wxString str = value.AsString();
    if(str.ToDouble(&d))
        return d;
    return NAN;
}

static double deg2rad(double deg)
{
    return (deg * M_PI / 180.0);
}

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new pypilot_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//-----------------------------------------------------------------------------
//
//    pypilot PlugIn Implementation
//
//-----------------------------------------------------------------------------
pypilot_pi *g_pypilot_pi = NULL;

pypilot_pi::pypilot_pi(void *ppimgr)
    : opencpn_plugin_110(ppimgr), m_client(*this)
{
    // Create the PlugIn icons
    initialize_images();
    m_declination = NAN;
}

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

int pypilot_pi::Init(void)
{
    AddLocaleCatalog( PLUGIN_CATALOG_NAME );

    m_leftclick_tool_id  = InsertPlugInTool
        (_T(""), _img_pypilot, _img_pypilot, wxITEM_NORMAL,
         _("pypilot"), _T(""), NULL, PYPILOT_TOOL_POSITION, 0, this);
    
    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( pypilot_pi::OnTimer ), NULL, this);
    m_Timer.Start(500);
            
    m_pypilotDialog = NULL;
    m_ConfigurationDialog = NULL;
    m_StatisticsDialog = NULL;
    m_CalibrationDialog = NULL;

    m_status = _("Disconnected");

    ReadConfig();
        
    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_TOOLBAR_CALLBACK    |
            WANTS_NMEA_SENTENCES      |
            WANTS_NMEA_EVENTS         |
            WANTS_PLUGIN_MESSAGING);
}

bool pypilot_pi::DeInit(void)
{
    delete m_pypilotDialog;
    delete m_ConfigurationDialog;
    delete m_StatisticsDialog;
    delete m_CalibrationDialog;

    m_Timer.Stop();
    m_Timer.Disconnect(wxEVT_TIMER, wxTimerEventHandler( pypilot_pi::OnTimer ), NULL, this);

    RemovePlugInTool(m_leftclick_tool_id);

    return true;
}

int pypilot_pi::GetAPIVersionMajor()
{
    return MY_API_VERSION_MAJOR;
}

int pypilot_pi::GetAPIVersionMinor()
{
    return MY_API_VERSION_MINOR;
}

int pypilot_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int pypilot_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxBitmap *pypilot_pi::GetPlugInBitmap()
{
    return new wxBitmap(_img_pypilot->ConvertToImage().Copy());
}

wxString pypilot_pi::GetCommonName()
{
    return _("pypilot");
}

wxString pypilot_pi::GetShortDescription()
{
    return _("pypilot PlugIn for OpenCPN");
}

wxString pypilot_pi::GetLongDescription()
{
    return _("pypilot PlugIn for OpenCPN\n\
Alarm user of changing conditions.");
}

int pypilot_pi::GetToolbarToolCount(void)
{
    return 1;
}

void pypilot_pi::SetColorScheme(PI_ColorScheme cs)
{
    DimeWindow(m_pypilotDialog);
}

void pypilot_pi::RearrangeWindow()
{
    SetColorScheme(PI_ColorScheme());
    m_pypilotDialog->Fit();
}

void pypilot_pi::Receive(wxString &name, wxJSONValue &value)
{
    if(name == "ap.heading")
        m_ap_heading = value.AsDouble();
    else if(name == "ap.heading_command")
        m_ap_heading_command = value.AsDouble();
}

void pypilot_pi::UpdateStatus()
{
    if(m_pypilotDialog)
        m_pypilotDialog->m_stStatus->SetLabel(m_status);
}

static void MergeWatchlist(std::map<wxString, bool> &watchlist, const char **list)
{
    for(const char **w = list; *w; w++)
        watchlist[*w] = true;
}

void pypilot_pi::UpdateWatchlist()
{
    if(!m_client.connected())
        return;

    std::map<wxString, bool> watchlist;
    if(m_pypilotDialog) {
        // map allows watchlists to overlap if needed
        if(m_pypilotDialog->IsShown())
            MergeWatchlist(watchlist, m_pypilotDialog->GetWatchlist());
        
        if(m_ConfigurationDialog->IsShown())
            MergeWatchlist(watchlist, m_ConfigurationDialog->GetWatchlist());
        
        if(m_StatisticsDialog->IsShown())
            MergeWatchlist(watchlist, m_StatisticsDialog->GetWatchlist());
        
        if(m_CalibrationDialog->IsShown())
            MergeWatchlist(watchlist, m_CalibrationDialog->GetWatchlist());
    }

    if(m_bEnableGraphicOverlay) {
        static const char *wl[] = {"ap.heading", "ap.heading_command", 0};
        MergeWatchlist(watchlist, wl);
    }

    // watch new keys we weren't watching
    for(std::map<wxString, bool>::iterator it = watchlist.begin(); it != watchlist.end(); it++)
        if(m_watchlist.find(it->first) == m_watchlist.end()) {
//            printf("add watch %s\n", it->first.mb_str().data());
            m_client.watch(it->first);
        } else
            m_client.get(it->first); // make sure we get the value again to update dialog here

    // unwatch old keys we don't need
    for(std::map<wxString, bool>::iterator it = m_watchlist.begin(); it != m_watchlist.end(); it++)
        if(watchlist.find(it->first) == watchlist.end()) {
//            printf("remove watch %s\n", it->first.mb_str().data());
            m_client.watch(it->first, false);
        }

    m_watchlist = watchlist;
}

void pypilot_pi::OnToolbarToolCallback(int id)
{
    if(!m_pypilotDialog)
    {
        m_pypilotDialog = new pypilotDialog(*this, GetOCPNCanvasWindow());
        UpdateStatus();
                
        m_ConfigurationDialog = new ConfigurationDialog(*this, GetOCPNCanvasWindow());
        m_StatisticsDialog = new StatisticsDialog(*this, GetOCPNCanvasWindow());
        m_CalibrationDialog = new CalibrationDialog(*this, GetOCPNCanvasWindow());

        wxIcon icon;
        icon.CopyFromBitmap(*_img_pypilot);
        m_pypilotDialog->SetIcon(icon);
        m_ConfigurationDialog->SetIcon(icon);
        m_StatisticsDialog->SetIcon(icon);
        m_CalibrationDialog->SetIcon(icon);
    }

    m_pypilotDialog->Show(!m_pypilotDialog->IsShown());
    UpdateWatchlist();

    wxPoint p = m_pypilotDialog->GetPosition();
    m_pypilotDialog->Move(0, 0);        // workaround for gtk autocentre dialog behavior
    m_pypilotDialog->Move(p);
}

void pypilot_pi::OnContextMenuItemCallback(int id)
{
}

bool pypilot_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    if(!m_bEnableGraphicOverlay)
        return false;
    pyDC odc(dc);
    Render(odc, *vp);
    return true;
}

bool pypilot_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    if(!m_bEnableGraphicOverlay)
        return false;
    pyDC odc;
//    glEnable( GL_BLEND );
    Render(odc, *vp);
//    glDisable( GL_BLEND );
    return true;
}

void pypilot_pi::Render(pyDC &dc, PlugIn_ViewPort &vp)
{
    wxPoint boat;
    GetCanvasPixLL(&vp, &boat, m_lastfix.Lat, m_lastfix.Lon);

    double r = wxMin(vp.pix_width, vp.pix_height)/4;
    wxPoint p1(boat.x + r*sin(deg2rad(m_ap_heading)),
               boat.y - r*cos(deg2rad(m_ap_heading)));
    dc.SetPen(wxPen(*wxRED, 4));
    dc.DrawLine(boat.x, boat.y, p1.x, p1.y);

    wxPoint p2(boat.x + r*sin(deg2rad(m_ap_heading_command)),
               boat.y - r*cos(deg2rad(m_ap_heading_command)));
    dc.SetPen(wxPen(*wxGREEN, 4));
    dc.DrawLine(boat.x, boat.y, p2.x, p2.y);
}

void pypilot_pi::ReadConfig()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/Settings/pypilot" ) );
    wxString host = pConf->Read ( _T ( "Host" ), "192.168.14.1" );
    if(host != m_host) {
        m_client.disconnect();
        m_host = host;
    }
    m_bForwardnmea = pConf->Read ( _T ( "Forwardnema" ), 0L);
    m_bEnableGraphicOverlay = pConf->Read ( _T ( "EnableGraphicOverlay" ), 0L);
    if(m_pypilotDialog)
        m_pypilotDialog->RebuildControlAngles();
            
    UpdateWatchlist();
}

void pypilot_pi::OnTimer( wxTimerEvent & )
{
    if(!m_client.connected()) {
        m_client.connect(m_host);
        return;
    }

    wxString name;
    wxJSONValue data;
    while(m_client.receive(name, data)) {
        //wxString value = data["value"].AsString();
        //printf("msg %s %s\n", name.mb_str().data(), value.mb_str().data());

        wxJSONValue val = data["value"];
        if(m_pypilotDialog) {
            m_pypilotDialog->Receive(name, val);
            m_ConfigurationDialog->Receive(name, val);
            m_StatisticsDialog->Receive(name, val);
            m_CalibrationDialog->Receive(name, val);
        }
        Receive(name, val);
    }
}

void pypilot_pi::OnConnected()
{
    m_status = _("Connected") + " " + _("to") + " " + m_host;
    UpdateStatus();
    UpdateWatchlist();
}

void pypilot_pi::OnDisconnected()
{
    m_status = _("Disconnected");
    m_watchlist.clear();
    UpdateStatus();
}

void pypilot_pi::SetNMEASentence(wxString &sentence)
{
}

void pypilot_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    m_lastfix = pfix;
}

void pypilot_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
    // construct the JSON root object
    wxJSONValue  root;
    // construct a JSON parser
    wxJSONReader reader;
    wxString    sLogMessage;
//    bool        bFail = false;
    
    if(message_id == wxS("PYPILOT_PI")) {
        // this message does nothing yet
    } else if(message_id == _T("WMM_VARIATION_BOAT")) {
        if(reader.Parse( message_body, &root ) == 0) {
            root[_T("Decl")].AsString().ToDouble(&m_declination);
            m_declinationTime = wxDateTime::Now();
        }
    }
}

wxString pypilot_pi::StandardPath()
{
    wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
    wxString s = wxFileName::GetPathSeparator();

#if defined(__WXMSW__)
    wxString stdPath  = std_path.GetConfigDir();
#elif defined(__WXGTK__) || defined(__WXQT__)
    wxString stdPath  = std_path.GetUserDataDir();
#elif defined(__WXOSX__)
    wxString stdPath  = (std_path.GetUserConfigDir() + s + _T("opencpn"));
#endif

    stdPath += s + _T("plugins");
    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s + _T("pypilot");

#ifdef __WXOSX__
    // Compatibility with pre-OCPN-4.2; move config dir to
    // ~/Library/Preferences/opencpn if it exists
    wxString oldPath = (std_path.GetUserConfigDir() + s + _T("plugins") + s + _T("weatherfax"));
    if (wxDirExists(oldPath) && !wxDirExists(stdPath)) {
	wxLogMessage("weatherfax_pi: moving config dir %s to %s", oldPath, stdPath);
	wxRenameFile(oldPath, stdPath);
    }
#endif

    if (!wxDirExists(stdPath))
      wxMkdir(stdPath);

    stdPath += s;
    return stdPath;
}

double pypilot_pi::Declination()
{
    if(!m_declinationTime.IsValid() || (wxDateTime::Now() - m_declinationTime).GetSeconds() > 1200) {
        wxJSONWriter w;
        wxString out;
        wxJSONValue v;
        w.Write(v, out);
        SendPluginMessage(wxString(_T("WMM_VARIATION_BOAT_REQUEST")), out);
    }
    return m_declination;
}
