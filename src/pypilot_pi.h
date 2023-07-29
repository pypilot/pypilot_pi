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

#ifndef _PYPILOTPI_H_
#define _PYPILOTPI_H_

#include <map>

#include "wx/wx.h"
#include <wx/fileconf.h>

#include "version.h"
#include "wxWTranslateCatalog.h"

#define ABOUT_AUTHOR_URL "http://seandepagnier.users.sourceforge.net"

#define OPC wxS("opencpn-pypilot_pi")

#ifndef WXINTL_NO_GETTEXT_MACRO
#ifdef OPC
#ifdef _
#undef _
#endif // _
#define _(s) wxGetTranslation((s),OPC)
#endif // OPC
#else 
#define _(s) wxGetTranslation((s))
#endif // WXINTL_NO_GETTEXT_MACRO

#include "ocpn_plugin.h"
#include "plugingl/qtstylesheet.h"

#ifdef __MSVC__
#include "msvcdefs.h"
#endif

#include "pypilot_client.h"

//----------------------------------
//    The PlugIn Class Definition
//----------------------------------

#define PYPILOT_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class wxServDisc;

class piDC;
class pypilotDialog;
class GainsDialog;
class ConfigurationDialog;
class StatisticsDialog;
class CalibrationDialog;
class SettingsDialog;
class pypilotClientDialog;


class pypilot_pi;
class pypilotClient_pi : public pypilotClient
{
public:
    pypilotClient_pi( pypilot_pi &_pypilot_pi )
        : pypilotClient(), m_pypilot_pi(_pypilot_pi) {}
    virtual void OnConnected();
    virtual void OnDisconnected();

private:
    pypilot_pi &m_pypilot_pi;
};


class pypilot_pi : public wxEvtHandler, public opencpn_plugin_116
{
public:

    pypilot_pi(void *ppimgr);

      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
  	  wxBitmap m_panelBitmap; 

      int GetToolbarToolCount(void);
      void OnToolbarToolCallback(int id);
      void OnContextMenuItemCallback(int id);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      void Render(piDC &dc, PlugIn_ViewPort &vp);
      void ReadConfig();

      void OnTimer( wxTimerEvent & );

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

//    Other public methods
      static wxString StandardPath();

      void UpdateConfiguration();

      double Declination();
      void OnConnected();
      void OnDisconnected();
      void UpdateWatchlist();
      double HeadingCommand() { return m_ap_heading_command; }

      pypilotClient_pi m_client;

      pypilotDialog  *m_pypilotDialog;
      GainsDialog    *m_GainsDialog;
      ConfigurationDialog *m_ConfigurationDialog;
      StatisticsDialog   *m_StatisticsDialog;
      CalibrationDialog  *m_CalibrationDialog;
      SettingsDialog  *m_SettingsDialog;
      pypilotClientDialog *m_pypilotClientDialog;

      double m_declination;
      wxDateTime m_declinationTime;
      wxString m_mode;
      Json::Value m_modes;

private:
      void SetNMEASentence(wxString &sentence);
      void OnNMEASocketEvent(wxSocketEvent& event);
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
      void SetPluginMessage(wxString &message_id, wxString &message_body);
      void RearrangeWindow();
      double AdjustHeading(double heading);
      void Receive(std::string name, Json::Value &value);
      void UpdateStatus();
      void SetToolbarIcon();

      void StartZeroConfig();
      void StopZeroConfig();
      void onSDNotify(wxCommandEvent& event);

      wxServDisc *m_servscan;
    
      wxDateTime m_declinationRequestTime;
      int               m_leftclick_tool_id;

      wxTimer m_Timer;

      wxString m_status;
      bool m_bHaveNAV;
      wxDateTime m_lastsocketinput;

      wxString m_host;
      bool m_bForwardNMEA, m_bSwitchToNAVMode;
      bool m_bEnableGraphicOverlay;

      PlugIn_Position_Fix_Ex m_lastfix;
      double m_ap_heading, m_ap_heading_command, m_imu_heading;

      double m_filtered_lat, m_filtered_lon, m_filtered_speed, m_filtered_track;

      wxDateTime m_lastMessage;

      bool m_enabled;
      int     m_ReadConfig;
      
      wxSocketClient      m_nmeasocket;
      std::string         m_nmeasock_buffer;

DECLARE_EVENT_TABLE()
};

double heading_resolve(double degrees);
double heading_resolve_pos(double degrees);

wxString jsonformat(const char *format, Json::Value &value);
double jsondouble(Json::Value &value);

#endif
