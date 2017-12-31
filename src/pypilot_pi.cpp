/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  pypilot Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Sean D'Epagnier                                 *
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

#include "wxJSON/jsonreader.h"
#include "wxJSON/jsonwriter.h"

#include "pydc.h"

#include "pypilot_pi.h"
#include "pypilotDialog.h"
#include "icons.h"


double heading_resolve(double degrees)
{
    while(degrees < -180)
        degrees += 360;
    while(degrees >= 180)
        degrees -= 360;
    return degrees;
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
    m_Timer.Start(3000);
    
    m_pypilotDialog = new pypilotDialog(*this, GetOCPNCanvasWindow());
        
    wxIcon icon;
    icon.CopyFromBitmap(*_img_pypilot);
    m_pypilotDialog->SetIcon(icon);

    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_TOOLBAR_CALLBACK    |
            WANTS_NMEA_SENTENCES      |
            WANTS_NMEA_EVENTS         |
            WANTS_PLUGIN_MESSAGING);
}

bool pypilot_pi::DeInit(void)
{
    //    Record the dialog position
    if (m_pypilotDialog)
    {
        m_pypilotDialog->Close();
        delete m_pypilotDialog;
        m_pypilotDialog = NULL;
    }
    
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
    if (NULL == m_pypilotDialog)
        return;

    DimeWindow(m_pypilotDialog);
}

void pypilot_pi::RearrangeWindow()
{
    if (NULL == m_pypilotDialog)
        return;

    SetColorScheme(PI_ColorScheme());
    
    m_pypilotDialog->Fit();
}

void pypilot_pi::OnToolbarToolCallback(int id)
{
    if(!m_pypilotDialog)
    {
        m_pypilotDialog = new pypilotDialog(*this, GetOCPNCanvasWindow());

        wxIcon icon;
        icon.CopyFromBitmap(*_img_pypilot);
        m_pypilotDialog->SetIcon(icon);
    }

    m_pypilotDialog->Show(!m_pypilotDialog->IsShown());

    wxPoint p = m_pypilotDialog->GetPosition();
    m_pypilotDialog->Move(0, 0);        // workaround for gtk autocentre dialog behavior
    m_pypilotDialog->Move(p);
}

void pypilot_pi::OnContextMenuItemCallback(int id)
{
}

bool pypilot_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    pyDC odc(dc);
    Render(odc, *vp);
    return true;
}

bool pypilot_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    pyDC odc;
    glEnable( GL_BLEND );
    Render(odc, *vp);
    glDisable( GL_BLEND );
    return true;
}

void pypilot_pi::Render(pyDC &dc, PlugIn_ViewPort &vp)
{
}

void pypilot_pi::OnTimer( wxTimerEvent & )
{
    if(!m_client.connected()) {
        m_client.connect("");
        return;
    }

    wxJSONValue msg;
    while(m_client.receive(msg))
        printf("msg %s %s", msg["name"].AsCString(), msg["value"].AsCString());
}

void pypilot_pi::OnConnected()
{
    m_pypilotDialog->m_stStatus->SetLabel(_("Connected"));
}

void pypilot_pi::OnDisconnected()
{
    m_pypilotDialog->m_stStatus->SetLabel(_("Disconnected"));
}

void pypilot_pi::SetNMEASentence(wxString &sentence)
{
}

void pypilot_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
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
