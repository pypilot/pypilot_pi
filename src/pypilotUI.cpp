///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 20 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pypilotUI.h"

///////////////////////////////////////////////////////////////////////////

pypilotDialogBase::pypilotDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 100,100 ), wxSize( -1,-1 ) );
	
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
	m_bAP->SetFont( wxFont( 36, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	fgSizer13->Add( m_bAP, 0, wxALL, 5 );
	
	wxArrayString m_cModeChoices;
	m_cMode = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cModeChoices, 0 );
	m_cMode->SetSelection( 0 );
	m_cMode->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer13->Add( m_cMode, 0, wxALL, 5 );
	
	
	fgSizer37->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer38;
	fgSizer38 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer38->AddGrowableCol( 0 );
	fgSizer38->SetFlexibleDirection( wxBOTH );
	fgSizer38->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer39->AddGrowableCol( 0 );
	fgSizer39->AddGrowableCol( 1 );
	fgSizer39->AddGrowableCol( 2 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stStatus = new wxStaticText( this, wxID_ANY, _("Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stStatus->Wrap( 200 );
	m_stStatus->SetMaxSize( wxSize( 200,-1 ) );
	
	fgSizer39->Add( m_stStatus, 0, wxALL, 5 );
	
	m_stServoMode = new wxStaticText( this, wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stServoMode->Wrap( -1 );
	m_stServoMode->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sans") ) );
	
	fgSizer39->Add( m_stServoMode, 0, wxALL, 5 );
	
	m_stServoFlags = new wxStaticText( this, wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stServoFlags->Wrap( 200 );
	m_stServoFlags->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_stServoFlags->SetMaxSize( wxSize( 200,-1 ) );
	
	fgSizer39->Add( m_stServoFlags, 0, wxALL, 5 );
	
	
	fgSizer38->Add( fgSizer39, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stCommand = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stCommand->Wrap( -1 );
	m_stCommand->SetFont( wxFont( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	fgSizer12->Add( m_stCommand, 0, wxALL|wxEXPAND, 5 );
	
	m_stHeading = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stHeading->Wrap( -1 );
	m_stHeading->SetFont( wxFont( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	
	fgSizer12->Add( m_stHeading, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer38->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer29;
	fgSizer29 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer29->SetFlexibleDirection( wxBOTH );
	fgSizer29->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_fgControlAnglesNeg = new wxFlexGridSizer( 0, 2, 0, 0 );
	m_fgControlAnglesNeg->SetFlexibleDirection( wxBOTH );
	m_fgControlAnglesNeg->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer29->Add( m_fgControlAnglesNeg, 1, wxEXPAND, 5 );
	
	m_fgControlAnglesPos = new wxFlexGridSizer( 0, 2, 0, 0 );
	m_fgControlAnglesPos->SetFlexibleDirection( wxBOTH );
	m_fgControlAnglesPos->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer29->Add( m_fgControlAnglesPos, 1, wxEXPAND, 5 );
	
	
	fgSizer38->Add( fgSizer29, 1, wxEXPAND, 5 );
	
	m_fgControlManual = new wxFlexGridSizer( 1, 0, 0, 0 );
	m_fgControlManual->AddGrowableCol( 0 );
	m_fgControlManual->AddGrowableCol( 1 );
	m_fgControlManual->AddGrowableCol( 2 );
	m_fgControlManual->AddGrowableCol( 3 );
	m_fgControlManual->SetFlexibleDirection( wxBOTH );
	m_fgControlManual->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bManualPortLong = new wxButton( this, wxID_ANY, _("<<"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualPortLong->SetMaxSize( wxSize( 40,-1 ) );
	
	m_fgControlManual->Add( m_bManualPortLong, 0, wxALL|wxEXPAND, 5 );
	
	m_bManualPortShort = new wxButton( this, wxID_ANY, _("<"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualPortShort->SetMaxSize( wxSize( 40,-1 ) );
	
	m_fgControlManual->Add( m_bManualPortShort, 0, wxALL|wxEXPAND, 5 );
	
	m_bManualStarboardShort = new wxButton( this, wxID_ANY, _(">"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualStarboardShort->SetMaxSize( wxSize( 40,-1 ) );
	
	m_fgControlManual->Add( m_bManualStarboardShort, 0, wxALL|wxEXPAND, 5 );
	
	m_bManualStarboardLong = new wxButton( this, wxID_ANY, _(">>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualStarboardLong->SetMaxSize( wxSize( 40,-1 ) );
	
	m_fgControlManual->Add( m_bManualStarboardLong, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer38->Add( m_fgControlManual, 1, wxEXPAND, 5 );
	
	
	fgSizer37->Add( fgSizer38, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( fgSizer37, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer71;
	fgSizer71 = new wxFlexGridSizer( 0, 5, 0, 0 );
	fgSizer71->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer71->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bGains = new wxButton( this, wxID_ANY, _("Gains"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bGains->SetMaxSize( wxSize( 60,-1 ) );
	
	fgSizer71->Add( m_bGains, 0, wxALL, 5 );
	
	m_bConfiguration = new wxButton( this, wxID_ANY, _("Config"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bConfiguration, 0, wxALL, 5 );
	
	m_bCalibration = new wxButton( this, wxID_ANY, _("Calibration"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bCalibration, 0, wxALL, 5 );
	
	m_bStatistics = new wxButton( this, wxID_ANY, _("Statistics"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bStatistics, 0, wxALL, 5 );
	
	m_bClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer71->Add( m_bClose, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer71, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer8 );
	this->Layout();
	fgSizer8->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( pypilotDialogBase::OnClose ) );
	m_bAP->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnAP ), NULL, this );
	m_cMode->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( pypilotDialogBase::OnMode ), NULL, this );
	m_bManualPortLong->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualPortLong ), NULL, this );
	m_bManualPortShort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualPortShort ), NULL, this );
	m_bManualStarboardShort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardShort ), NULL, this );
	m_bManualStarboardLong->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardLong ), NULL, this );
	m_bGains->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnGains ), NULL, this );
	m_bConfiguration->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnConfiguration ), NULL, this );
	m_bCalibration->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnCalibration ), NULL, this );
	m_bStatistics->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnStatistics ), NULL, this );
	m_bClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnClose ), NULL, this );
}

pypilotDialogBase::~pypilotDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( pypilotDialogBase::OnClose ) );
	m_bAP->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnAP ), NULL, this );
	m_cMode->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( pypilotDialogBase::OnMode ), NULL, this );
	m_bManualPortLong->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualPortLong ), NULL, this );
	m_bManualPortShort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualPortShort ), NULL, this );
	m_bManualStarboardShort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardShort ), NULL, this );
	m_bManualStarboardLong->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardLong ), NULL, this );
	m_bGains->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnGains ), NULL, this );
	m_bConfiguration->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnConfiguration ), NULL, this );
	m_bCalibration->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnCalibration ), NULL, this );
	m_bStatistics->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnStatistics ), NULL, this );
	m_bClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnClose ), NULL, this );
	
}

GainsDialogBase::GainsDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxSize( -1,-1 ) );
	
	wxFlexGridSizer* fgSizer37;
	fgSizer37 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer37->AddGrowableCol( 0 );
	fgSizer37->AddGrowableRow( 0 );
	fgSizer37->SetFlexibleDirection( wxBOTH );
	fgSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_swGains = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_swGains->SetScrollRate( 5, 5 );
	m_swGains->SetMinSize( wxSize( 300,200 ) );
	
	m_fgGains = new wxFlexGridSizer( 1, 0, 0, 0 );
	m_fgGains->AddGrowableRow( 0 );
	m_fgGains->SetFlexibleDirection( wxBOTH );
	m_fgGains->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	m_swGains->SetSizer( m_fgGains );
	m_swGains->Layout();
	m_fgGains->Fit( m_swGains );
	fgSizer37->Add( m_swGains, 1, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer4 = new wxStdDialogButtonSizer();
	m_sdbSizer4OK = new wxButton( this, wxID_OK );
	m_sdbSizer4->AddButton( m_sdbSizer4OK );
	m_sdbSizer4->Realize();
	
	fgSizer37->Add( m_sdbSizer4, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer37 );
	this->Layout();
	fgSizer37->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GainsDialogBase::OnClose ) );
	m_sdbSizer4OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GainsDialogBase::OnClose ), NULL, this );
}

GainsDialogBase::~GainsDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GainsDialogBase::OnClose ) );
	m_sdbSizer4OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GainsDialogBase::OnClose ), NULL, this );
	
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
	
	m_cHost = new wxComboBox( this, wxID_ANY, _("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_cHost->Append( _("127.0.0.1 (localhost)") );
	m_cHost->Append( _("192.168.14.1 (tinypilot)") );
	m_cHost->Append( _("10.10.10.1 (openplotter)") );
	fgSizer16->Add( m_cHost, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer4->Add( fgSizer16, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer171;
	fgSizer171 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer171->SetFlexibleDirection( wxBOTH );
	fgSizer171->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer24->AddGrowableRow( 1 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("OpenCPN Settings") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_cbForwardnmea = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Forward nmea"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbForwardnmea, 0, wxALL, 5 );
	
	m_bAboutForwardnema = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_bAboutForwardnema, 0, wxALL, 5 );
	
	m_cbEnableGraphicOverlay = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Enable Graphical Overlay"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbEnableGraphicOverlay, 0, wxALL, 5 );
	
	m_bAboutEnableOverlay = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_bAboutEnableOverlay, 0, wxALL, 5 );
	
	m_cbTrueNorthMode = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("True North Mode"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_cbTrueNorthMode, 0, wxALL, 5 );
	
	m_button18 = new wxButton( sbSizer1->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer17->Add( m_button18, 0, wxALL, 5 );
	
	
	sbSizer1->Add( fgSizer17, 1, wxEXPAND, 5 );
	
	
	fgSizer24->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Control Angles") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer25->AddGrowableRow( 0 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer26;
	fgSizer26 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer26->AddGrowableRow( 1 );
	fgSizer26->SetFlexibleDirection( wxBOTH );
	fgSizer26->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_sControlAngle = new wxSpinCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 180, 0 );
	fgSizer26->Add( m_sControlAngle, 0, wxALL, 5 );
	
	m_lControlAngles = new wxListBox( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	fgSizer26->Add( m_lControlAngles, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer25->Add( fgSizer26, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer27;
	fgSizer27 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer27->SetFlexibleDirection( wxBOTH );
	fgSizer27->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bAddControlAngle = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, _("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer27->Add( m_bAddControlAngle, 0, wxALL, 5 );
	
	m_button11 = new wxButton( sbSizer5->GetStaticBox(), wxID_ANY, _("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer27->Add( m_button11, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer33;
	fgSizer33 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer33->SetFlexibleDirection( wxBOTH );
	fgSizer33->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText35 = new wxStaticText( sbSizer5->GetStaticBox(), wxID_ANY, _("Columns"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer33->Add( m_staticText35, 0, wxALL, 5 );
	
	m_sControlColumns = new wxSpinCtrl( sbSizer5->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 9, 2 );
	m_sControlColumns->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer33->Add( m_sControlColumns, 0, wxALL, 5 );
	
	
	fgSizer27->Add( fgSizer33, 1, wxEXPAND, 5 );
	
	
	fgSizer25->Add( fgSizer27, 1, wxEXPAND, 5 );
	
	
	sbSizer5->Add( fgSizer25, 1, wxEXPAND, 5 );
	
	
	fgSizer24->Add( sbSizer5, 1, wxEXPAND, 5 );
	
	
	fgSizer171->Add( fgSizer24, 1, wxEXPAND, 5 );
	
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
	
	m_staticText5 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Servo Period"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer15->Add( m_staticText5, 0, wxALL, 3 );
	
	m_stPeriod = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPeriod->Wrap( -1 );
	fgSizer15->Add( m_stPeriod, 0, wxALL, 3 );
	
	m_sPeriod = new wxSpinButton( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS|wxSP_VERTICAL );
	fgSizer15->Add( m_sPeriod, 0, wxALL, 3 );
	
	m_staticText7 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer15->Add( m_staticText7, 0, wxALL, 3 );
	
	
	fgSizer14->Add( fgSizer15, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer161;
	fgSizer161 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer161->SetFlexibleDirection( wxBOTH );
	fgSizer161->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Max Current"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer161->Add( m_staticText8, 0, wxALL, 3 );
	
	m_stMaxCurrent = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stMaxCurrent->Wrap( -1 );
	fgSizer161->Add( m_stMaxCurrent, 0, wxALL, 3 );
	
	m_sMaxCurrent = new wxSpinButton( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer161->Add( m_sMaxCurrent, 0, wxALL, 3 );
	
	m_staticText9 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Amps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer161->Add( m_staticText9, 0, wxALL, 3 );
	
	
	fgSizer14->Add( fgSizer161, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText10 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Min Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer21->Add( m_staticText10, 0, wxALL, 3 );
	
	m_sMinSpeed = new wxSpinCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	m_sMinSpeed->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer21->Add( m_sMinSpeed, 0, wxALL, 3 );
	
	m_staticText11 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer21->Add( m_staticText11, 0, wxALL, 3 );
	
	m_staticText101 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Max Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	fgSizer21->Add( m_staticText101, 0, wxALL, 3 );
	
	m_sMaxSpeed = new wxSpinCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	m_sMaxSpeed->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer21->Add( m_sMaxSpeed, 0, wxALL, 3 );
	
	m_staticText111 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer21->Add( m_staticText111, 0, wxALL, 3 );
	
	m_staticText30 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Max Controller Temp"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer21->Add( m_staticText30, 0, wxALL, 3 );
	
	m_sMaxControllerTemp = new wxSpinCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 30, 80, 30 );
	m_sMaxControllerTemp->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer21->Add( m_sMaxControllerTemp, 0, wxALL, 3 );
	
	m_staticText31 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer21->Add( m_staticText31, 0, wxALL, 3 );
	
	m_staticText32 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("Max Motor Temp"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer21->Add( m_staticText32, 0, wxALL, 3 );
	
	m_sMaxMotorTemp = new wxSpinCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 30, 80, 30 );
	m_sMaxMotorTemp->SetMaxSize( wxSize( 100,-1 ) );
	
	fgSizer21->Add( m_sMaxMotorTemp, 0, wxALL, 3 );
	
	m_staticText311 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	fgSizer21->Add( m_staticText311, 0, wxALL, 3 );
	
	
	fgSizer14->Add( fgSizer21, 1, wxEXPAND, 5 );
	
	
	sbSizer2->Add( fgSizer14, 1, wxEXPAND, 5 );
	
	
	fgSizer171->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( fgSizer171, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer18->AddGrowableCol( 1 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bInformation = new wxButton( this, wxID_ANY, _("Information"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_bInformation, 0, wxALL, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	
	fgSizer18->Add( m_sdbSizer2, 1, wxEXPAND|wxRIGHT, 5 );
	
	
	fgSizer4->Add( fgSizer18, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConfigurationDialogBase::OnClose ) );
	m_cHost->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ConfigurationDialogBase::OnHost ), NULL, this );
	m_bAboutForwardnema->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutForwardnema ), NULL, this );
	m_bAboutEnableOverlay->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutEnableOverlay ), NULL, this );
	m_button18->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutTrueNorth ), NULL, this );
	m_bAddControlAngle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAddControlAngle ), NULL, this );
	m_button11->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnRemoveControlAngle ), NULL, this );
	m_sPeriod->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( ConfigurationDialogBase::OnPeriod ), NULL, this );
	m_sMaxCurrent->Connect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( ConfigurationDialogBase::OnMaxCurrent ), NULL, this );
	m_bInformation->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnInformation ), NULL, this );
	m_sdbSizer2Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnClose ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnOk ), NULL, this );
}

ConfigurationDialogBase::~ConfigurationDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ConfigurationDialogBase::OnClose ) );
	m_cHost->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( ConfigurationDialogBase::OnHost ), NULL, this );
	m_bAboutForwardnema->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutForwardnema ), NULL, this );
	m_bAboutEnableOverlay->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutEnableOverlay ), NULL, this );
	m_button18->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAboutTrueNorth ), NULL, this );
	m_bAddControlAngle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnAddControlAngle ), NULL, this );
	m_button11->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnRemoveControlAngle ), NULL, this );
	m_sPeriod->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( ConfigurationDialogBase::OnPeriod ), NULL, this );
	m_sMaxCurrent->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxSpinEventHandler( ConfigurationDialogBase::OnMaxCurrent ), NULL, this );
	m_bInformation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnInformation ), NULL, this );
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnClose ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnOk ), NULL, this );
	
}

StatisticsDialogBase::StatisticsDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer34;
	fgSizer34 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer34->AddGrowableCol( 1 );
	fgSizer34->SetFlexibleDirection( wxBOTH );
	fgSizer34->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText39 = new wxStaticText( this, wxID_ANY, _("Uptime"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	fgSizer34->Add( m_staticText39, 0, wxALL, 5 );
	
	m_stUptime = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stUptime->Wrap( -1 );
	fgSizer34->Add( m_stUptime, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText36 = new wxStaticText( this, wxID_ANY, _("Runtime"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer34->Add( m_staticText36, 0, wxALL, 5 );
	
	m_stAPRuntime = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAPRuntime->Wrap( -1 );
	fgSizer34->Add( m_stAPRuntime, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer18->Add( fgSizer34, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, _("Average Power Consumption"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer19->Add( m_staticText18, 0, wxALL, 5 );
	
	m_stWatts = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stWatts->Wrap( -1 );
	fgSizer19->Add( m_stWatts, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, _("Watts"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer19->Add( m_staticText20, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, _("Total amp hours"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer19->Add( m_staticText21, 0, wxALL, 5 );
	
	m_stAmpHours = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAmpHours->Wrap( -1 );
	fgSizer19->Add( m_stAmpHours, 0, wxALL, 5 );
	
	m_bResetAmpHours = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( m_bResetAmpHours, 0, wxALL, 5 );
	
	m_staticText45 = new wxStaticText( this, wxID_ANY, _("Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	fgSizer19->Add( m_staticText45, 0, wxALL, 5 );
	
	m_stVoltage = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stVoltage->Wrap( -1 );
	fgSizer19->Add( m_stVoltage, 0, wxALL, 5 );
	
	m_staticText47 = new wxStaticText( this, wxID_ANY, _("V"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	fgSizer19->Add( m_staticText47, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( this, wxID_ANY, _("Controller Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer19->Add( m_staticText24, 0, wxALL, 5 );
	
	m_stControllerTemp = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stControllerTemp->Wrap( -1 );
	fgSizer19->Add( m_stControllerTemp, 0, wxALL, 5 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer19->Add( m_staticText26, 0, wxALL, 5 );
	
	m_staticText27 = new wxStaticText( this, wxID_ANY, _("Motor Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	fgSizer19->Add( m_staticText27, 0, wxALL, 5 );
	
	m_stMotorTemp = new wxStaticText( this, wxID_ANY, _("-------"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stMotorTemp->Wrap( -1 );
	fgSizer19->Add( m_stMotorTemp, 0, wxALL, 5 );
	
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
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( StatisticsDialogBase::OnClose ) );
	m_bResetAmpHours->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnResetAmpHours ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnClose ), NULL, this );
}

StatisticsDialogBase::~StatisticsDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( StatisticsDialogBase::OnClose ) );
	m_bResetAmpHours->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnResetAmpHours ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StatisticsDialogBase::OnClose ), NULL, this );
	
}

CalibrationDialogBase::CalibrationDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Accel") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer35;
	fgSizer35 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer35->AddGrowableCol( 0 );
	fgSizer35->SetFlexibleDirection( wxBOTH );
	fgSizer35->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stAccelCalibration = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stAccelCalibration->Wrap( 30 );
	fgSizer35->Add( m_stAccelCalibration, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer36;
	fgSizer36 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer36->SetFlexibleDirection( wxBOTH );
	fgSizer36->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText48 = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, _("Age"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	fgSizer36->Add( m_staticText48, 0, wxALL, 5 );
	
	m_stAccelCalibrationAge = new wxStaticText( sbSizer6->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAccelCalibrationAge->Wrap( -1 );
	fgSizer36->Add( m_stAccelCalibrationAge, 0, wxALL, 5 );
	
	m_cbAccelCalibrationLocked = new wxCheckBox( sbSizer6->GetStaticBox(), wxID_ANY, _("Calibration Locked"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer36->Add( m_cbAccelCalibrationLocked, 0, wxALL, 5 );
	
	m_button1711 = new wxButton( sbSizer6->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button1711->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer36->Add( m_button1711, 0, wxALL, 5 );
	
	
	fgSizer35->Add( fgSizer36, 1, wxEXPAND, 5 );
	
	
	sbSizer6->Add( fgSizer35, 1, wxEXPAND, 5 );
	
	
	fgSizer19->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Compass") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer41;
	fgSizer41 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer41->SetFlexibleDirection( wxBOTH );
	fgSizer41->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_stCompassCalibration = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stCompassCalibration->Wrap( 30 );
	fgSizer41->Add( m_stCompassCalibration, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer22->AddGrowableCol( 1 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText30 = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("Age"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer22->Add( m_staticText30, 0, wxALL, 5 );
	
	m_stCompassCalibrationAge = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stCompassCalibrationAge->Wrap( -1 );
	fgSizer22->Add( m_stCompassCalibrationAge, 0, wxALL|wxEXPAND, 5 );
	
	m_cbCompassCalibrationLocked = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, _("Calibration Locked"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer22->Add( m_cbCompassCalibrationLocked, 0, wxALL, 5 );
	
	m_button171 = new wxButton( sbSizer4->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button171->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer22->Add( m_button171, 0, wxALL, 5 );
	
	
	fgSizer41->Add( fgSizer22, 1, wxEXPAND, 5 );
	
	
	sbSizer4->Add( fgSizer41, 1, wxEXPAND, 5 );
	
	
	fgSizer19->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Alignment") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText25 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Pitch / Roll"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer20->Add( m_staticText25, 0, wxALL, 5 );
	
	m_stPitchRoll = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("N/A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stPitchRoll->Wrap( -1 );
	fgSizer20->Add( m_stPitchRoll, 0, wxALL, 5 );
	
	
	sbSizer3->Add( fgSizer20, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer31;
	fgSizer31 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer31->SetFlexibleDirection( wxBOTH );
	fgSizer31->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_gLevel = new wxGauge( sbSizer3->GetStaticBox(), wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gLevel->SetValue( 0 ); 
	fgSizer31->Add( m_gLevel, 0, wxALL, 5 );
	
	m_bLevel = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _("Level"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer31->Add( m_bLevel, 0, wxALL, 5 );
	
	m_button16 = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button16->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer31->Add( m_button16, 0, wxALL, 5 );
	
	m_staticText34 = new wxStaticText( sbSizer3->GetStaticBox(), wxID_ANY, _("Heading Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer31->Add( m_staticText34, 0, wxALL, 5 );
	
	m_sHeadingOffset = new wxSpinCtrl( sbSizer3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -180, 180, 0 );
	m_sHeadingOffset->SetMaxSize( wxSize( 80,-1 ) );
	
	fgSizer31->Add( m_sHeadingOffset, 0, wxALL, 5 );
	
	m_button17 = new wxButton( sbSizer3->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button17->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer31->Add( m_button17, 0, wxALL, 5 );
	
	
	sbSizer3->Add( fgSizer31, 1, wxEXPAND, 5 );
	
	
	fgSizer19->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Rudder Feedback") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer42;
	fgSizer42 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer42->SetFlexibleDirection( wxBOTH );
	fgSizer42->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText49 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Rudder"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer39->Add( m_staticText49, 0, wxALL, 5 );
	
	m_stRudder = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudder->Wrap( -1 );
	fgSizer39->Add( m_stRudder, 0, wxALL, 5 );
	
	
	fgSizer42->Add( fgSizer39, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer40;
	fgSizer40 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer40->SetFlexibleDirection( wxBOTH );
	fgSizer40->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_button22 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("Centered"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button22, 0, wxALL, 5 );
	
	m_button23 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("At Range"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button23, 0, wxALL, 5 );
	
	m_button172 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button172->SetMaxSize( wxSize( 40,-1 ) );
	
	fgSizer40->Add( m_button172, 0, wxALL, 5 );
	
	
	fgSizer42->Add( fgSizer40, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer411;
	fgSizer411 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer411->SetFlexibleDirection( wxBOTH );
	fgSizer411->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText51 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Range"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer411->Add( m_staticText51, 0, wxALL, 5 );
	
	m_sRudderRange = new wxSpinCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 90, 30 );
	fgSizer411->Add( m_sRudderRange, 0, wxALL, 5 );
	
	
	fgSizer42->Add( fgSizer411, 1, wxEXPAND, 5 );
	
	
	sbSizer7->Add( fgSizer42, 1, wxEXPAND, 5 );
	
	
	fgSizer19->Add( sbSizer7, 1, wxEXPAND, 5 );
	
	m_sdbSizer3 = new wxStdDialogButtonSizer();
	m_sdbSizer3OK = new wxButton( this, wxID_OK );
	m_sdbSizer3->AddButton( m_sdbSizer3OK );
	m_sdbSizer3->Realize();
	
	fgSizer19->Add( m_sdbSizer3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer19 );
	this->Layout();
	fgSizer19->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CalibrationDialogBase::OnClose ) );
	m_cbAccelCalibrationLocked->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnCalibrationLocked ), NULL, this );
	m_button1711->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutCalibrationLocked ), NULL, this );
	m_cbCompassCalibrationLocked->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnCalibrationLocked ), NULL, this );
	m_button171->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutCalibrationLocked ), NULL, this );
	m_bLevel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnLevel ), NULL, this );
	m_button16->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutLevel ), NULL, this );
	m_sHeadingOffset->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnHeadingOffset ), NULL, this );
	m_button17->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutHeadingOffset ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderCentered ), NULL, this );
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderAtRange ), NULL, this );
	m_button172->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutRudderCalibration ), NULL, this );
	m_sRudderRange->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnRudderRange ), NULL, this );
	m_sdbSizer3OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnClose ), NULL, this );
}

CalibrationDialogBase::~CalibrationDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( CalibrationDialogBase::OnClose ) );
	m_cbAccelCalibrationLocked->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnCalibrationLocked ), NULL, this );
	m_button1711->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutCalibrationLocked ), NULL, this );
	m_cbCompassCalibrationLocked->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnCalibrationLocked ), NULL, this );
	m_button171->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutCalibrationLocked ), NULL, this );
	m_bLevel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnLevel ), NULL, this );
	m_button16->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutLevel ), NULL, this );
	m_sHeadingOffset->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnHeadingOffset ), NULL, this );
	m_button17->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutHeadingOffset ), NULL, this );
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderCentered ), NULL, this );
	m_button23->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderAtRange ), NULL, this );
	m_button172->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutRudderCalibration ), NULL, this );
	m_sRudderRange->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnRudderRange ), NULL, this );
	m_sdbSizer3OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnClose ), NULL, this );
	
}
