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


#include "plugingl/pidc.h"
#include "pypilot_pi.h"

#include "pypilotDialog.h"
#include "GainsDialog.h"
#include "ConfigurationDialog.h"
#include "StatisticsDialog.h"
#include "CalibrationDialog.h"
#include "SignalKClientDialog.h"

#include "icons.h"

inline double deg2rad(double degrees) { return M_PI * degrees / 180.0; }

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
    : opencpn_plugin_111(ppimgr), m_client(*this)
{
    // Create the PlugIn icons
    initialize_images();
    m_declination = NAN;
    m_imu_heading = NAN;
    m_lastfix.nSats = 0;

    m_enabled = false;
    m_mode = "";
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
        (_T(""), _img_pypilot_grey, _img_pypilot_grey, wxITEM_NORMAL,
         _("pypilot"), _T(""), NULL, PYPILOT_TOOL_POSITION, 0, this);
    
    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( pypilot_pi::OnTimer ), NULL, this);
    m_Timer.Start(1000);
            
    m_pypilotDialog = NULL;
    m_GainsDialog = NULL;
    m_ConfigurationDialog = NULL;
    m_StatisticsDialog = NULL;
    m_CalibrationDialog = NULL;
    m_SignalKClientDialog = NULL;

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
    m_client.disconnect();

    m_Timer.Stop();
    m_Timer.Disconnect(wxEVT_TIMER, wxTimerEventHandler( pypilot_pi::OnTimer ), NULL, this);

    delete m_pypilotDialog;
    delete m_GainsDialog;
    delete m_ConfigurationDialog;
    delete m_StatisticsDialog;
    delete m_CalibrationDialog;
    delete m_SignalKClientDialog;

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
    return new wxBitmap(_img_pypilot_grey->ConvertToImage().Copy());
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
    return _("Control the free software autopilot pypilot.\n\
See http://pypilot.org for more details.\n\n\
The plugin connects to the autopilot server via signalk implementing\n\
a control interface to configure, calibrate and command the autopilot.\n\n\
For more control and tuning route-following logic,\n\
consider the autopilot route plugin.");
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

double pypilot_pi::AdjustHeading(double heading)
{
    if(m_mode == "compass")
        return heading - m_declination;
    if(m_mode == "gps")
        return heading;
    // otherwise wind or true wind
    return m_imu_heading + m_declination + heading;
}

void pypilot_pi::Receive(std::string name, Json::Value &value)
{
    if(name == "ap.enabled") {
        m_enabled = value.asBool();
        SetToolbarIcon();
    } else if(name == "ap.mode") {
        wxString oldmode = m_mode;
        m_mode = value.asString();
        if(m_bEnableGraphicOverlay && m_mode != oldmode)
            UpdateWatchlist();
        SetToolbarIcon();
    } else if(name == "ap.heading")
        m_ap_heading = AdjustHeading(value.asDouble());
    else if(name == "ap.heading_command")
        m_ap_heading_command = AdjustHeading(value.asDouble());
    else if(name == "imu.heading")
        m_imu_heading = value.asDouble();
}

void pypilot_pi::UpdateStatus()
{
    if(m_pypilotDialog)
        m_pypilotDialog->m_stStatus->SetLabel(m_status);
}

void pypilot_pi::SetToolbarIcon()
{
    wxBitmap *bitmap = _img_pypilot_red;
    if(m_enabled) {
        if(m_mode == "compass")
            bitmap = _img_pypilot_green;
        else if(m_mode == "gps")
            bitmap = _img_pypilot_yellow;
        else if(m_mode == "wind")
            bitmap = _img_pypilot_blue;
        else if(m_mode == "true wind")
            bitmap = _img_pypilot_cyan;
    }
    SetToolbarToolBitmaps(m_leftclick_tool_id, bitmap, bitmap);
}

static void MergeWatchlist(std::map<std::string, bool> &watchlist, const char **list)
{
    for(const char **w = list; *w; w++)
        watchlist[*w] = true;
}

static void MergeWatchlist(std::map<std::string, bool> &watchlist, std::list<std::string> &list)
{
    for(std::list<std::string>::iterator i = list.begin(); i != list.end(); i++)
        watchlist[*i] = true;
}

void pypilot_pi::UpdateWatchlist()
{
    if(!m_client.connected())
        return;

    std::map<std::string, bool> watchlist;
    if(m_pypilotDialog) {
        // map allows watchlists to overlap if needed
        if(m_pypilotDialog->IsShown())
            MergeWatchlist(watchlist, m_pypilotDialog->GetWatchlist());
        
        if(m_GainsDialog->IsShown())
            MergeWatchlist(watchlist, m_GainsDialog->GetWatchlist());
        
        if(m_ConfigurationDialog->IsShown())
            MergeWatchlist(watchlist, m_ConfigurationDialog->GetWatchlist());
        
        if(m_StatisticsDialog->IsShown())
            MergeWatchlist(watchlist, m_StatisticsDialog->GetWatchlist());
        
        if(m_CalibrationDialog->IsShown())
            MergeWatchlist(watchlist, m_CalibrationDialog->GetWatchlist());

        if(m_SignalKClientDialog->IsShown())
            MergeWatchlist(watchlist, m_SignalKClientDialog->GetWatchlist());
    }

    if(m_bEnableGraphicOverlay) {
        static const char *wl[] = {"ap.heading", "ap.heading_command", 0};
        MergeWatchlist(watchlist, wl);
        if(m_mode == "wind" || m_mode == "true wind")
            watchlist["imu.heading"] = true;
    } else
        watchlist["imu.uptime"] = true; // use as heartbeat to time out connection

    static const char *wl[] = {"ap.mode", "ap.enabled", 0};
    MergeWatchlist(watchlist, wl);

    m_client.update_watchlist(watchlist, true);
}

void pypilot_pi::OnToolbarToolCallback(int id)
{
    if(!m_pypilotDialog)
    {
        m_pypilotDialog = new pypilotDialog(*this, GetOCPNCanvasWindow());
        UpdateStatus();
                
        m_GainsDialog = new GainsDialog(*this, GetOCPNCanvasWindow());
        m_ConfigurationDialog = new ConfigurationDialog(*this, GetOCPNCanvasWindow());
        m_StatisticsDialog = new StatisticsDialog(*this, GetOCPNCanvasWindow());
        m_CalibrationDialog = new CalibrationDialog(*this, GetOCPNCanvasWindow());
        m_SignalKClientDialog = new SignalKClientDialog(*this, GetOCPNCanvasWindow());

        wxIcon icon;
        icon.CopyFromBitmap(*_img_pypilot_grey);
        m_pypilotDialog->SetIcon(icon);
        m_GainsDialog->SetIcon(icon);
        m_ConfigurationDialog->SetIcon(icon);
        m_StatisticsDialog->SetIcon(icon);
        m_CalibrationDialog->SetIcon(icon);
        m_SignalKClientDialog->SetIcon(icon);
    }

    bool show = !m_pypilotDialog->IsShown();
    m_pypilotDialog->Show(show);
    if(!show) {
        m_GainsDialog->Show(false);
        m_ConfigurationDialog->Show(false);
        m_StatisticsDialog->Show(false);
        m_CalibrationDialog->Show(false);
        m_SignalKClientDialog->Show(false);
    }
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
    piDC odc(dc);
    Render(odc, *vp);
    return true;
}

bool pypilot_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    if(!m_bEnableGraphicOverlay)
        return false;
    piDC odc;
    glEnable( GL_BLEND );
    Render(odc, *vp);
    glDisable( GL_BLEND );
    return true;
}

void pypilot_pi::Render(piDC &dc, PlugIn_ViewPort &vp)
{
    if(m_lastfix.nSats == 0)
        return;
    if(!m_enabled)
        return;

    wxPoint boat;
    GetCanvasPixLL(&vp, &boat, m_lastfix.Lat, m_lastfix.Lon);

    double r = wxMin(vp.pix_width, vp.pix_height)/4;
    wxPoint p1(boat.x + r*sin(deg2rad(m_ap_heading)),
               boat.y - r*cos(deg2rad(m_ap_heading)));
    dc.SetPen(wxPen(*wxRED, 3));
    dc.DrawLine(boat.x, boat.y, p1.x, p1.y);
    dc.DrawCircle(p1.x, p1.y, 5);

    wxPoint p2(boat.x + r*sin(deg2rad(m_ap_heading_command)),
               boat.y - r*cos(deg2rad(m_ap_heading_command)));
    dc.SetPen(wxPen(*wxGREEN, 3));
    dc.DrawLine(boat.x, boat.y, p2.x, p2.y);
    dc.DrawCircle(p2.x, p2.y, 5);
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
    m_bForwardnmea = (bool)pConf->Read ( _T ( "Forwardnema" ), 0L);
    m_bEnableGraphicOverlay = (bool)pConf->Read ( _T ( "EnableGraphicOverlay" ), 0L);
    if(m_pypilotDialog)
        m_pypilotDialog->RebuildControlAngles();
            
    UpdateWatchlist();
}

void pypilot_pi::OnTimer( wxTimerEvent & )
{
    Declination();

    if(!m_client.connected()) {
        m_client.connect(m_host);
        m_lastMessage = wxDateTime(); // invalidate
        m_Timer.Start(2000);
        return;
    }

    std::string name;
    Json::Value data;
    wxDateTime now = wxDateTime::Now();
     while(m_client.receive(name, data)) {
        //wxString value = data["value"].AsString();
        //printf("msg %s %s\n", name.mb_str().data(), value.mb_str().data());

         try
         {
        Json::Value &val = data["value"];
        if(m_pypilotDialog) {
            m_pypilotDialog->Receive(name, val);
            m_GainsDialog->Receive(name, val);
            m_ConfigurationDialog->Receive(name, val);
            m_StatisticsDialog->Receive(name, val);
            m_CalibrationDialog->Receive(name, val);
            m_SignalKClientDialog->Receive(name, val);
        }
        Receive(name, val);
         }     catch(std::exception e)
         {
             printf("exception!!! %s\n", name.c_str());
         }

        m_lastMessage = now;
    }

    if(m_lastMessage.IsValid() && (now-m_lastMessage).GetSeconds() > 5)
        m_client.disconnect();
}

void pypilot_pi::OnConnected()
{
    m_status = _("Connected") + " " + _("to") + " " + m_host;
    UpdateStatus();
    UpdateWatchlist();
    SetToolbarIcon();
    m_lastMessage = wxDateTime::Now();
    m_Timer.Start(400);
}

void pypilot_pi::OnDisconnected()
{
    m_status = _("Disconnected");
    if(m_pypilotDialog)
        m_pypilotDialog->Disconnected();
    SetToolbarToolBitmaps(m_leftclick_tool_id, _img_pypilot_grey, _img_pypilot_grey);
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
    // construct the Json::Value root object
    // construct a Json::Value parser
    wxString    sLogMessage;
//    bool        bFail = false;
    
    if(message_id == wxS("PYPILOT_PI")) {
        // this message does nothing yet
    } else if(message_id == _T("WMM_VARIATION_BOAT")) {
        Json::Value root;
        Json::Reader reader;
        if(reader.parse(std::string(message_body), root)) {
            m_declination = jsondouble(root["Decl"]);
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
    if(m_declinationRequestTime.IsValid() &&
       (wxDateTime::Now() - m_declinationRequestTime).GetSeconds() < 6)
        return m_declination;
    m_declinationRequestTime = wxDateTime::Now();

    if(!m_declinationTime.IsValid() || (wxDateTime::Now() - m_declinationTime).GetSeconds() > 1200) {
        SendPluginMessage(wxString(_T("WMM_VARIATION_BOAT_REQUEST")), "");
    }
    return m_declination;
}

double heading_resolve(double degrees)
{
    while(degrees < -180)
        degrees += 360;
    while(degrees >= 180)
        degrees -= 360;
    return degrees;
}

double heading_resolve_pos(double degrees)
{
    while(degrees < 0)
        degrees += 360;
    while(degrees >= 360)
        degrees -= 360;
    return degrees;
}

double jsondouble(Json::Value &value)
{
    if(value.isDouble())
        return value.asDouble();
    double d;
    wxString str = value.asString();
    if(str.ToDouble(&d))
        return d;
    return NAN;
}

wxString jsonformat(const char *format, Json::Value &value)
{
    return wxString::Format(format, jsondouble(value));
}
