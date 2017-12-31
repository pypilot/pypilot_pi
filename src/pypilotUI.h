///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  3 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PYPILOTUI_H__
#define __PYPILOTUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/tglbtn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>

#include "wxWTranslateCatalog.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class pypilotDialogBase
///////////////////////////////////////////////////////////////////////////////
class pypilotDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxToggleButton* m_bAP;
		wxChoice* m_cMode;
		wxStaticText* m_stCommand;
		wxStaticText* m_stHeading;
		wxScrolledWindow* m_swGains;
		wxButton* m_bConfiguration;
		wxButton* m_bStatistics;
		wxButton* m_bClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnConfiguration( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStatistics( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxStaticText* m_stStatus;
		
		pypilotDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("pypilot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,300 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL ); 
		~pypilotDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ConfigurationDialogBase
///////////////////////////////////////////////////////////////////////////////
class ConfigurationDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textCtrl2;
		wxCheckBox* m_cbForwardnema;
		wxButton* m_bAboutForwardnema;
		wxCheckBox* m_cbEnableOverlay;
		wxButton* m_bAboutEnableOverlay;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText61;
		wxSpinButton* m_spinBtn2;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_tMaxCurrent;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxSpinCtrl* m_sMinSpeed;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText101;
		wxSpinCtrl* m_sMaxSpeed;
		wxStaticText* m_staticText111;
		wxButton* m_bCalibration;
		wxButton* m_bInformation;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAboutForwardnema( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAboutEnableOverlay( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCalibration( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInformation( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ConfigurationDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("pypilot Configuration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~ConfigurationDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class StatisticsDialogBase
///////////////////////////////////////////////////////////////////////////////
class StatisticsDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText18;
		wxStaticText* m_stWatts;
		wxStaticText* m_staticText20;
		wxStaticText* m_staticText21;
		wxStaticText* m_stAmpHours;
		wxButton* m_bResetAmpHours;
		wxStaticText* m_staticText24;
		wxStaticText* m_staticText25;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText27;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnResetAmpHours( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		StatisticsDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("pypilot stats"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~StatisticsDialogBase();
	
};

#endif //__PYPILOTUI_H__
