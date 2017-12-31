///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  3 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pypilotUI.h"

///////////////////////////////////////////////////////////////////////////

pypilotDialogBase::pypilotDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->AddGrowableRow( 1 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	wxFlexGridSizer* fgSizer37;
	fgSizer37 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer37->AddGrowableCol( 1 );
	fgSizer37->SetFlexibleDirection( wxBOTH );
	fgSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bAP = new wxToggleButton( this, wxID_ANY, _("AP"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bAP->SetFont( wxFont( 32, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer13->Add( m_bAP, 0, wxALL, 5 );
	
	wxString m_cModeChoices[] = { _("compass"), _("gps"), _("wind"), _("true wind") };
	int m_cModeNChoices = sizeof( m_cModeChoices ) / sizeof( wxString );
	m_cMode = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cModeNChoices, m_cModeChoices, 0 );
	m_cMode->SetSelection( 4 );
	fgSizer13->Add( m_cMode, 0, wxALL, 5 );
	
	
	fgSizer37->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer38;
	fgSizer38 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer38->AddGrowableCol( 0 );
	fgSizer38->SetFlexibleDirection( wxBOTH );
	fgSizer38->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer39->AddGrowableCol( 0 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stStatus = new wxStaticText( this, wxID_ANY, _("Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stStatus->Wrap( -1 );
	fgSizer39->Add( m_stStatus, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer38->Add( fgSizer39, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stCommand = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stCommand->Wrap( -1 );
	m_stCommand->SetFont( wxFont( 24, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer12->Add( m_stCommand, 0, wxALL|wxEXPAND, 5 );
	
	m_stHeading = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stHeading->Wrap( -1 );
	m_stHeading->SetFont( wxFont( 24, 70, 90, 90, false, wxEmptyString ) );
	
	fgSizer12->Add( m_stHeading, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer38->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	
	fgSizer37->Add( fgSizer38, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( fgSizer37, 1, wxEXPAND, 5 );
	
	m_swGains = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swGains->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	m_swGains->SetSizer( fgSizer20 );
	m_swGains->Layout();
	fgSizer20->Fit( m_swGains );
	fgSizer8->Add( m_swGains, 1, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer71;
	fgSizer71 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer71->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer71->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bConfiguration = new wxButton( this, wxID_ANY, _("Configuration"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bConfiguration, 0, wxALL, 5 );
	
	m_bStatistics = new wxButton( this, wxID_ANY, _("Statistics"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bStatistics, 0, wxALL, 5 );
	
	m_bClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bClose, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer71, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer8 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_bConfiguration->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnConfiguration ), NULL, this );
	m_bStatistics->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnStatistics ), NULL, this );
	m_bClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnClose ), NULL, this );
}

pypilotDialogBase::~pypilotDialogBase()
{
	// Disconnect Events
	m_bConfiguration->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnConfiguration ), NULL, this );
	m_bStatistics->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnStatistics ), NULL, this );
	m_bClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnClose ), NULL, this );
	
}

ConfigurationDialogBase::ConfigurationDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer16->AddGrowableCol( 1 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("pypilot host"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer16->Add( m_staticText6, 0, wxALL, 5 );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer16->Add( m_textCtrl2, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer4->Add( fgSizer16, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer171;
	fgSizer171 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer171->SetFlexibleDirection( wxBOTH );
	fgSizer171->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("OpenCPN Settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbForwardnema = new wxCheckBox( this, wxID_ANY, _("Forward nmea"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbForwardnema, 0, wxALL, 5 );
	
	m_bAboutForwardnema = new wxButton( this, wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_bAboutForwardnema, 0, wxALL, 5 );
	
	m_cbEnableOverlay = new wxCheckBox( this, wxID_ANY, _("Enable Graphical Overlay"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbEnableOverlay, 0, wxALL, 5 );
	
	m_bAboutEnableOverlay = new wxButton( this, wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_bAboutEnableOverlay, 0, wxALL, 5 );
	
	
	sbSizer1->Add( fgSizer17, 1, wxEXPAND, 5 );
	
	
	fgSizer171->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("pypilot Servo Settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Servo Period"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer15->Add( m_staticText5, 0, wxALL, 5 );
	
	m_staticText61 = new wxStaticText( this, wxID_ANY, _("--"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer15->Add( m_staticText61, 0, wxALL, 5 );
	
	m_spinBtn2 = new wxSpinButton( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer15->Add( m_spinBtn2, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer15->Add( m_staticText7, 0, wxALL, 5 );
	
	
	fgSizer14->Add( fgSizer15, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer161;
	fgSizer161 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer161->SetFlexibleDirection( wxBOTH );
	fgSizer161->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Max Current"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer161->Add( m_staticText8, 0, wxALL, 5 );
	
	m_tMaxCurrent = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer161->Add( m_tMaxCurrent, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Amps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer161->Add( m_staticText9, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Min Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer161->Add( m_staticText10, 0, wxALL, 5 );
	
	m_sMinSpeed = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	m_sMinSpeed->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer161->Add( m_sMinSpeed, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer161->Add( m_staticText11, 0, wxALL, 5 );
	
	m_staticText101 = new wxStaticText( this, wxID_ANY, _("Max Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	fgSizer161->Add( m_staticText101, 0, wxALL, 5 );
	
	m_sMaxSpeed = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	m_sMaxSpeed->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer161->Add( m_sMaxSpeed, 0, wxALL, 5 );
	
	m_staticText111 = new wxStaticText( this, wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer161->Add( m_staticText111, 0, wxALL, 5 );
	
	
	fgSizer14->Add( fgSizer161, 1, wxEXPAND, 5 );
	
	
	sbSizer2->Add( fgSizer14, 1, wxEXPAND, 5 );
	
	
	fgSizer171->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( fgSizer171, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bCalibration = new wxButton( this, wxID_ANY, _("Calibration"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_bCalibration, 0, wxALL, 5 );
	
	m_bInformation = new wxButton( this, wxID_ANY, _("Information"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_bInformation, 0, wxALL, 5 );
	
	
	fgSizer4->Add( fgSizer18, 1, wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	
	fgSizer4->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_bAboutForwardnema->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutForwardnema ), NULL, this );
	m_bAboutEnableOverlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutEnableOverlay ), NULL, this );
	m_bCalibration->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnCalibration ), NULL, this );
	m_bInformation->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnInformation ), NULL, this );
	m_sdbSizer2Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnCancel ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnOk ), NULL, this );
}

ConfigurationDialogBase::~ConfigurationDialogBase()
{
	// Disconnect Events
	m_bAboutForwardnema->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutForwardnema ), NULL, this );
	m_bAboutEnableOverlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutEnableOverlay ), NULL, this );
	m_bCalibration->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnCalibration ), NULL, this );
	m_bInformation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnInformation ), NULL, this );
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnCancel ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnOk ), NULL, this );
	
}

StatisticsDialogBase::StatisticsDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("Average Power Consumption"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer19->Add( m_staticText18, 0, wxALL, 5 );
	
	m_stWatts = new wxStaticText( this, wxID_ANY, _("---"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stWatts->Wrap( -1 );
	fgSizer19->Add( m_stWatts, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, _("Watts"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer19->Add( m_staticText20, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Total amp hours"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer19->Add( m_staticText21, 0, wxALL, 5 );
	
	m_stAmpHours = new wxStaticText( this, wxID_ANY, _("---"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAmpHours->Wrap( -1 );
	fgSizer19->Add( m_stAmpHours, 0, wxALL, 5 );
	
	m_bResetAmpHours = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( m_bResetAmpHours, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( this, wxID_ANY, _("Controller Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer19->Add( m_staticText24, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, _("---"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer19->Add( m_staticText25, 0, wxALL, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer19->Add( m_staticText26, 0, wxALL, 5 );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Motor Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer19->Add( m_staticText27, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, _("---"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer19->Add( m_staticText28, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer19->Add( m_staticText29, 0, wxALL, 5 );
	
	
	fgSizer18->Add( fgSizer19, 1, wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	
	fgSizer18->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer18 );
	this->Layout();
	fgSizer18->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_bResetAmpHours->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnResetAmpHours ), NULL, this );
}

StatisticsDialogBase::~StatisticsDialogBase()
{
	// Disconnect Events
	m_bResetAmpHours->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnResetAmpHours ), NULL, this );
	
}
