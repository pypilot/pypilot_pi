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
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers


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
#include "pypilotClientDialog.h"

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

BEGIN_EVENT_TABLE(pypilot_pi, wxEvtHandler)
    EVT_SOCKET(-1, pypilot_pi::OnNMEASocketEvent)
END_EVENT_TABLE()

void pypilotClient_pi::OnConnected() { m_pypilot_pi.OnConnected(); }
void pypilotClient_pi::OnDisconnected() { m_pypilot_pi.OnDisconnected(); }

pypilot_pi::pypilot_pi(void *ppimgr)
    : opencpn_plugin_116(ppimgr), m_client(*this)
{
    // Create the PlugIn icons
    initialize_images();
    m_declination = NAN;
    m_imu_heading = NAN;
    m_lastfix.nSats = 0;


    m_nmeasocket.SetEventHandler(*this);
    m_nmeasocket.SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    m_nmeasocket.Notify(true);
    m_nmeasocket.SetTimeout(1);
    
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

/*   OLD _img code
    m_leftclick_tool_id  = InsertPlugInTool
        (_T(""), _img_pypilot_grey, _img_pypilot_grey, wxITEM_NORMAL,
         _("pypilot"), _T(""), NULL, PYPILOT_TOOL_POSITION, 0, this);
*/

// See line 265 for various colored icons for Mode - sail, compass, etc.
#ifdef PLUGIN_USE_SVG
    m_leftclick_tool_id = InsertPlugInToolSVG( _T( "Pypilot" ), _svg_pypilot, _svg_pypilot_rollover, _svg_pypilot_toggled, wxITEM_CHECK, _( "Pypilot" ), _T( "" ), NULL, PYPILOT_TOOL_POSITION, 0, this);
#else
    m_leftclick_tool_id  = InsertPlugInTool
        (_T(""), _img_plots, _img_plots, wxITEM_NORMAL,
         _("Plots"), _T(""), NULL, PYPILOT_TOOL_POSITION, 0, this);
#endif


    
    m_Timer.Connect(wxEVT_TIMER, wxTimerEventHandler
                    ( pypilot_pi::OnTimer ), NULL, this);
    m_Timer.Start(1000);
            
    m_pypilotDialog = NULL;
    m_GainsDialog = NULL;
    m_ConfigurationDialog = NULL;
    m_StatisticsDialog = NULL;
    m_CalibrationDialog = NULL;
    m_pypilotClientDialog = NULL;

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
    delete m_pypilotClientDialog;

    RemovePlugInTool(m_leftclick_tool_id);

    return true;
}

int pypilot_pi::GetAPIVersionMajor()
{
    return OCPN_API_VERSION_MAJOR;
}

int pypilot_pi::GetAPIVersionMinor()
{
    return OCPN_API_VERSION_MINOR;
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
//    return _("pypilot");
    return _T(PLUGIN_COMMON_NAME);
}

wxString pypilot_pi::GetShortDescription()
{
//    return _("pypilot PlugIn for OpenCPN");
    return _T(PLUGIN_COMMON_NAME);	
}

wxString pypilot_pi::GetLongDescription()
{
    return _(PLUGIN_LONG_DESCRIPTION);

/*    return _("Control the free software autopilot pypilot.\n  \
See http://pypilot.org for more details.\n\n\
The plugin connects to pypilot directly implementing a control\n\
interface to configure, calibrate and command pypilot from opencpn.\n\n\
For more control and tuning route-following logic,\n\
consider the autopilot route plugin."); */

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
        m_pypilotDialog->SetLabel(m_status);
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

static void MergeWatchlist(std::map<std::string, double> &watchlist, const char **list)
{
    for(const char **w = list; *w; w++)
        watchlist[*w] = 0;
}

static void MergeWatchlist(std::map<std::string, double> &watchlist, std::list<std::string> &list)
{
    for(std::list<std::string>::iterator i = list.begin(); i != list.end(); i++)
        watchlist[*i] = 0;
}

static void MergeWatchlist(std::map<std::string, double> &watchlist, std::map<std::string, double> &list)
{
    for(std::map<std::string, double>::iterator i = list.begin(); i != list.end(); i++)
        if(watchlist.find(i->first) == watchlist.end())
            watchlist[i->first] = i->second;
        else
            watchlist[i->first] = fmin(watchlist[i->first], i->second);
}

void pypilot_pi::UpdateWatchlist()
{
    if(!m_client.connected())
        return;

    std::map<std::string, double> watchlist;
    if(m_pypilotDialog) {
        // map allows watchlists to overlap if needed
        if(m_pypilotDialog->IsShown())
            MergeWatchlist(watchlist, m_pypilotDialog->GetWatchlist());
        
        if(m_GainsDialog->IsShown())
            MergeWatchlist(watchlist, m_GainsDialog->GetWatchlist());
        
        if(m_StatisticsDialog->IsShown())
            MergeWatchlist(watchlist, m_StatisticsDialog->GetWatchlist());
        
        if(m_CalibrationDialog->IsShown())
            MergeWatchlist(watchlist, m_CalibrationDialog->GetWatchlist());

        if(m_pypilotClientDialog->IsShown())
            MergeWatchlist(watchlist, m_pypilotClientDialog->GetWatchlist());
    }

    if(m_bEnableGraphicOverlay) {
        static const char *wl[] = {"ap.heading", "ap.heading_command", 0};
        MergeWatchlist(watchlist, wl);
        if(m_mode == "wind" || m_mode == "true wind")
            watchlist["imu.heading"] = 0.5;
    } else
        watchlist["imu.uptime"] = true; // use as heartbeat to time out connection

    static const char *wl[] = {"ap.mode", "ap.enabled", 0};
    MergeWatchlist(watchlist, wl);

    m_client.update_watchlist(watchlist);
}

void pypilot_pi::OnToolbarToolCallback(int id)
{
    if(!m_pypilotDialog)
    {
        m_ConfigurationDialog = new ConfigurationDialog(*this, GetOCPNCanvasWindow());
        m_pypilotDialog = new pypilotDialog(*this, GetOCPNCanvasWindow());
        UpdateStatus();
        
        m_StatisticsDialog = new StatisticsDialog(*this, GetOCPNCanvasWindow());
        m_CalibrationDialog = new CalibrationDialog(*this, GetOCPNCanvasWindow());
        m_pypilotClientDialog = new pypilotClientDialog(*this, GetOCPNCanvasWindow());
        m_GainsDialog = new GainsDialog(*this, GetOCPNCanvasWindow());

        wxIcon icon;
        icon.CopyFromBitmap(*_img_pypilot_grey);
        m_pypilotDialog->SetIcon(icon);
        m_GainsDialog->SetIcon(icon);
        m_ConfigurationDialog->SetIcon(icon);
        m_StatisticsDialog->SetIcon(icon);
        m_CalibrationDialog->SetIcon(icon);
        m_pypilotClientDialog->SetIcon(icon);
    }

    bool show = !m_pypilotDialog->IsShown();
    m_pypilotDialog->Show(show);
    
    if(!show) {
        m_GainsDialog->Show(false);
        m_ConfigurationDialog->Show(false);
        m_StatisticsDialog->Show(false);
        m_CalibrationDialog->Show(false);
        m_pypilotClientDialog->Show(false);
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

    double dist = 1; // 1nm
    double dlat, dlon;
    wxPoint p;

    PositionBearingDistanceMercator_Plugin(m_lastfix.Lat, m_lastfix.Lon, m_ap_heading, dist, &dlat, &dlon);
    GetCanvasPixLL(&vp, &p, dlat, dlon);
    dc.SetPen(wxPen(*wxRED, 3));
    dc.DrawLine(boat.x, boat.y, p.x, p.y);
    dc.DrawCircle(p.x, p.y, 5);

    PositionBearingDistanceMercator_Plugin(m_lastfix.Lat, m_lastfix.Lon, m_ap_heading_command, dist, &dlat, &dlon);
    dc.SetPen(wxPen(*wxGREEN, 3));
    dc.DrawLine(boat.x, boat.y, p.x, p.y);
    dc.DrawCircle(p.x, p.y, 5);
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
    Json::Value val;
    wxDateTime now = wxDateTime::Now();
     while(m_client.receive(name, val)) {
         //printf("msg %s %s\n", name.c_str(), val.asString().c_str());

         try {
             Receive(name, val);
             if(m_pypilotDialog) {
                 m_pypilotDialog->Receive(name, val);
                 m_GainsDialog->Receive(name, val);
                 m_StatisticsDialog->Receive(name, val);
                 m_CalibrationDialog->Receive(name, val);
                 m_pypilotClientDialog->Receive(name, val);
             }
         } catch(std::exception e) {
             printf("exception!!! %s: %s\n", name.c_str(), e.what());
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
    m_Timer.Start(100); // 400 ?

    SendPluginMessage(wxString("PYPILOT_HOST"), m_host);
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
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( "/Settings/pypilot" );

    if(!pConf->Read ( "ForwardNMEA" , 0L ))
        return;

    if(!m_nmeasocket.IsConnected()) {
        wxString host = pConf->Read ( "Host", "192.168.14.1" );
        wxIPV4address addr;
        addr.Hostname(host);
        addr.Service(20220);
        m_nmeasocket.Connect(addr, false);
    }
        
    if(m_nmeasocket.IsConnected())
        m_nmeasocket.Write(sentence.c_str(), sentence.size());
}

void pypilot_pi::OnNMEASocketEvent(wxSocketEvent& event)
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( "/Settings/pypilot" );

    if(!pConf->Read ( "ForwardNMEA" , 0L )) {
        m_nmeasocket.Close();
        return;
    }
        
    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
            break;

        case wxSOCKET_LOST:
            m_nmeasocket.Close();
            break;

        case wxSOCKET_INPUT:
        {
    #define RD_BUF_SIZE    65536
            std::vector<char> data(RD_BUF_SIZE+1);
            event.GetSocket()->Read(&data.front(), RD_BUF_SIZE);
            if(!event.GetSocket()->Error()) {
                size_t count = event.GetSocket()->LastCount();
                if(count) {
                    data[count]=0;
                    m_nmeasock_buffer += (&data.front());
                }

                // overflow and reset connection at 640k in buffer
                if(m_nmeasock_buffer.size() >= 1024*640) {
                    wxLogMessage( "nmea input buffer overflow!\n" );
                    m_nmeasocket.Close();
                    break;
                }
            }

            for(;;) {
                int line_end = m_nmeasock_buffer.find_first_of("\n");
                if(line_end <= 0)
                    break;
                std::string nmea_line = m_nmeasock_buffer.substr(0, line_end);
                if(line_end < 1024) // discard nmea lines longer than 1024
                    PushNMEABuffer(nmea_line);

                if(line_end > (int)m_nmeasock_buffer.size())
                    m_nmeasock_buffer.clear();
                else
                    m_nmeasock_buffer = m_nmeasock_buffer.substr(line_end+1);
            }
        } break;
    default:;
    }
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
    
    if(message_id == wxS("PYPILOT_HOST_REQUEST")) {
        SendPluginMessage(wxString("PYPILOT_HOST"), m_host);
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
