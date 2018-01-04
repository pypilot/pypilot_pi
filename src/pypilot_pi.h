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

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    10

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

#ifdef __MSVC__
#include "msvcdefs.h"
#endif

#include "pypilot_signalk_client.h"

//----------------------------------
//    The PlugIn Class Definition
//----------------------------------

#define PYPILOT_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class pyDC;
class pypilotDialog;
class ConfigurationDialog;
class StatisticsDialog;
class CalibrationDialog;

class pypilot_pi : public wxEvtHandler, public opencpn_plugin_110
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

      int GetToolbarToolCount(void);
      void OnToolbarToolCallback(int id);
      void OnContextMenuItemCallback(int id);

      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      void Render(pyDC &dc, PlugIn_ViewPort &vp);
      void ReadConfig();

      void OnTimer( wxTimerEvent & );

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);

//    Other public methods
      void ShowConfigurationDialog( wxWindow* );
      static wxString StandardPath();

      void UpdateConfiguration();

      double Declination();
      void OnConnected();
      void OnDisconnected();
      void UpdateWatchlist();

      pypilot_SignalKClient m_client;

      pypilotDialog  *m_pypilotDialog;
      ConfigurationDialog *m_ConfigurationDialog;
      StatisticsDialog   *m_StatisticsDialog;
      CalibrationDialog  *m_CalibrationDialog;
      
private:
      void SetNMEASentence(wxString &sentence);
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
      void SetPluginMessage(wxString &message_id, wxString &message_body);
      void              RearrangeWindow();
      void Receive(wxString &name, wxJSONValue &value);
      void UpdateStatus();

      int               m_leftclick_tool_id;

      wxTimer m_Timer;

      double m_declination;
      wxDateTime m_declinationTime;

      std::map<wxString, bool> m_watchlist;

      wxString m_status;

      wxString m_host;
      bool m_bForwardnmea;
      bool m_bEnableGraphicOverlay;

      PlugIn_Position_Fix_Ex m_lastfix;
      double m_ap_heading, m_ap_heading_command;
};

wxString jsonformat(const char *format, wxJSONValue &value);
double jsondouble(wxJSONValue &value);

#endif
