///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 18 2019)
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
	fgSizer37 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer37->AddGrowableCol( 1 );
	fgSizer37->SetFlexibleDirection( wxBOTH );
	fgSizer37->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_bAP = new wxToggleButton( this, wxID_ANY, _("AP"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bAP->SetFont( wxFont( 36, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sawasdee") ) );

	fgSizer13->Add( m_bAP, 0, wxALL, 5 );

	wxString m_cModeChoices[] = { _("N/A") };
	int m_cModeNChoices = sizeof( m_cModeChoices ) / sizeof( wxString );
	m_cMode = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cModeNChoices, m_cModeChoices, 0 );
	m_cMode->SetSelection( 0 );
	m_cMode->SetMaxSize( wxSize( 100,-1 ) );

	fgSizer13->Add( m_cMode, 0, wxALL|wxEXPAND, 5 );


	fgSizer37->Add( fgSizer13, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer38;
	fgSizer38 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer38->AddGrowableCol( 0 );
	fgSizer38->SetFlexibleDirection( wxBOTH );
	fgSizer38->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer39->AddGrowableCol( 2 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_stStatus = new wxStaticText( this, wxID_ANY, _("Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stStatus->Wrap( 200 );
	m_stStatus->SetMaxSize( wxSize( 200,-1 ) );

	fgSizer39->Add( m_stStatus, 0, wxALL, 5 );

	m_stServoState = new wxStaticText( this, wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stServoState->Wrap( -1 );
	m_stServoState->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sans") ) );

	fgSizer39->Add( m_stServoState, 0, wxALL, 5 );

	m_stServoFlags = new wxStaticText( this, wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stServoFlags->Wrap( 30 );
	m_stServoFlags->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_stServoFlags->SetMaxSize( wxSize( 200,-1 ) );

	fgSizer39->Add( m_stServoFlags, 0, wxALL|wxEXPAND, 5 );

	m_stRudder = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudder->Wrap( -1 );
	fgSizer39->Add( m_stRudder, 0, wxALL|wxEXPAND, 5 );


	fgSizer38->Add( fgSizer39, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_stCommand = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,30 ), 0 );
	m_stCommand->Wrap( -1 );
	m_stCommand->SetFont( wxFont( 26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sawasdee") ) );

	fgSizer12->Add( m_stCommand, 0, wxALL|wxEXPAND, 5 );

	m_stHeading = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stHeading->Wrap( -1 );
	m_stHeading->SetFont( wxFont( 26, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Sawasdee") ) );

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

	m_bCenter = new wxButton( this, wxID_ANY, _("C"), wxDefaultPosition, wxSize( 40,-1 ), 0 );
	m_fgControlManual->Add( m_bCenter, 0, wxALL, 5 );

	m_bManualStarboardShort = new wxButton( this, wxID_ANY, _(">"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualStarboardShort->SetMaxSize( wxSize( 40,-1 ) );

	m_fgControlManual->Add( m_bManualStarboardShort, 0, wxALL|wxEXPAND, 5 );

	m_bManualStarboardLong = new wxButton( this, wxID_ANY, _(">>"), wxDefaultPosition, wxDefaultSize, 0 );
	m_bManualStarboardLong->SetMaxSize( wxSize( 40,-1 ) );

	m_fgControlManual->Add( m_bManualStarboardLong, 0, wxALL|wxEXPAND, 5 );


	fgSizer38->Add( m_fgControlManual, 1, wxEXPAND, 5 );


	fgSizer37->Add( fgSizer38, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer43;
	fgSizer43 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer43->SetFlexibleDirection( wxBOTH );
	fgSizer43->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_stTackState = new wxStaticText( this, wxID_ANY, _("tack"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stTackState->Wrap( -1 );
	fgSizer43->Add( m_stTackState, 0, wxALL|wxEXPAND, 5 );

	m_bTack = new wxButton( this, wxID_ANY, _("Tack"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	fgSizer43->Add( m_bTack, 0, wxALL, 5 );

	wxString m_cTackDirectionChoices[] = { _("--> Starboard"), _("<-- Port") };
	int m_cTackDirectionNChoices = sizeof( m_cTackDirectionChoices ) / sizeof( wxString );
	m_cTackDirection = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 80,-1 ), m_cTackDirectionNChoices, m_cTackDirectionChoices, 0 );
	m_cTackDirection->SetSelection( 0 );
	fgSizer43->Add( m_cTackDirection, 0, wxALL, 5 );


	fgSizer37->Add( fgSizer43, 1, wxEXPAND, 5 );


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
	m_bCenter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualCenter ), NULL, this );
	m_bManualStarboardShort->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardShort ), NULL, this );
	m_bManualStarboardLong->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardLong ), NULL, this );
	m_bTack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnTack ), NULL, this );
	m_cTackDirection->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( pypilotDialogBase::OnTackDirection ), NULL, this );
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
	m_bCenter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualCenter ), NULL, this );
	m_bManualStarboardShort->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardShort ), NULL, this );
	m_bManualStarboardLong->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnManualStarboardLong ), NULL, this );
	m_bTack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( pypilotDialogBase::OnTack ), NULL, this );
	m_cTackDirection->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( pypilotDialogBase::OnTackDirection ), NULL, this );
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

	m_swGains = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxSize( 300,200 ), wxHSCROLL|wxVSCROLL );
	m_swGains->SetScrollRate( 5, 5 );
	m_swGains->SetMinSize( wxSize( 300,200 ) );

	m_fgGains = new wxFlexGridSizer( 1, 0, 0, 0 );
	m_fgGains->AddGrowableRow( 0 );
	m_fgGains->SetFlexibleDirection( wxBOTH );
	m_fgGains->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	m_swGains->SetSizer( m_fgGains );
	m_swGains->Layout();
	fgSizer37->Add( m_swGains, 1, wxEXPAND | wxALL, 5 );

	wxFlexGridSizer* fgSizer42;
	fgSizer42 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer42->SetFlexibleDirection( wxBOTH );
	fgSizer42->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText52 = new wxStaticText( this, wxID_ANY, _("Pilot"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	fgSizer42->Add( m_staticText52, 0, wxALL, 5 );

	wxString m_cPilotChoices[] = { _("N/A") };
	int m_cPilotNChoices = sizeof( m_cPilotChoices ) / sizeof( wxString );
	m_cPilot = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cPilotNChoices, m_cPilotChoices, 0 );
	m_cPilot->SetSelection( 0 );
	fgSizer42->Add( m_cPilot, 0, wxALL, 5 );

	m_sdbSizer4 = new wxStdDialogButtonSizer();
	m_sdbSizer4OK = new wxButton( this, wxID_OK );
	m_sdbSizer4->AddButton( m_sdbSizer4OK );
	m_sdbSizer4->Realize();

	fgSizer42->Add( m_sdbSizer4, 1, wxALIGN_RIGHT|wxEXPAND, 5 );


	fgSizer37->Add( fgSizer42, 1, 0, 5 );


	this->SetSizer( fgSizer37 );
	this->Layout();
	fgSizer37->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GainsDialogBase::OnClose ) );
	m_cPilot->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GainsDialogBase::OnPilot ), NULL, this );
	m_sdbSizer4OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GainsDialogBase::OnClose ), NULL, this );
}

GainsDialogBase::~GainsDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GainsDialogBase::OnClose ) );
	m_cPilot->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GainsDialogBase::OnPilot ), NULL, this );
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

	m_staticText6 = new wxStaticText( this, wxID_ANY, _("pass"), wxDefaultPosition, wxDefaultSize, 0 );
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
	m_lControlAngles->SetMinSize( wxSize( -1,10 ) );

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

	wxFlexGridSizer* fgSizer46;
	fgSizer46 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer46->SetFlexibleDirection( wxBOTH );
	fgSizer46->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_sbSizerServo = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Servo") ), wxVERTICAL );


	fgSizer46->Add( m_sbSizerServo, 1, wxEXPAND, 5 );

	m_sbSizerTacking = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Tacking") ), wxVERTICAL );


	fgSizer46->Add( m_sbSizerTacking, 1, wxEXPAND, 5 );

	m_bSignalKClient = new wxButton( this, wxID_ANY, _("SignalK Client"), wxDefaultPosition, wxSize( 180,-1 ), 0 );
	fgSizer46->Add( m_bSignalKClient, 0, wxALL, 5 );


	fgSizer171->Add( fgSizer46, 1, wxEXPAND, 5 );


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
	m_bSignalKClient->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnSignalKClient ), NULL, this );
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
	m_bSignalKClient->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnSignalKClient ), NULL, this );
	m_bInformation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnInformation ), NULL, this );
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnClose ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConfigurationDialogBase::OnOk ), NULL, this );

}

SignalKClientDialogBase::SignalKClientDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 240,200 ), wxDefaultSize );

	wxFlexGridSizer* fgSizer45;
	fgSizer45 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer45->AddGrowableCol( 0 );
	fgSizer45->AddGrowableRow( 0 );
	fgSizer45->SetFlexibleDirection( wxBOTH );
	fgSizer45->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 5, 5 );
	m_fgSizer = new wxFlexGridSizer( 0, 3, 0, 0 );
	m_fgSizer->AddGrowableCol( 1 );
	m_fgSizer->SetFlexibleDirection( wxBOTH );
	m_fgSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	m_scrolledWindow->SetSizer( m_fgSizer );
	m_scrolledWindow->Layout();
	m_fgSizer->Fit( m_scrolledWindow );
	fgSizer45->Add( m_scrolledWindow, 1, wxEXPAND | wxALL, 5 );

	m_sdbSizer5 = new wxStdDialogButtonSizer();
	m_sdbSizer5OK = new wxButton( this, wxID_OK );
	m_sdbSizer5->AddButton( m_sdbSizer5OK );
	m_sdbSizer5->Realize();

	fgSizer45->Add( m_sdbSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( fgSizer45 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_sdbSizer5OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SignalKClientDialogBase::OnOK ), NULL, this );
}

SignalKClientDialogBase::~SignalKClientDialogBase()
{
	// Disconnect Events
	m_sdbSizer5OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SignalKClientDialogBase::OnOK ), NULL, this );

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
	fgSizer19 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer19->AddGrowableCol( 0 );
	fgSizer19->AddGrowableRow( 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_MULTILINE );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, _("Accel") ), wxVERTICAL );

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


	m_panel1->SetSizer( sbSizer6 );
	m_panel1->Layout();
	sbSizer6->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, _("Accelerometers"), true );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, _("Compass") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer41;
	fgSizer41 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer41->SetFlexibleDirection( wxBOTH );
	fgSizer41->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_stCompassCalibration = new wxStaticText( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_stCompassCalibration->Wrap( 30 );
	fgSizer41->Add( m_stCompassCalibration, 0, wxALL|wxEXPAND, 5 );

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


	m_panel2->SetSizer( sbSizer4 );
	m_panel2->Layout();
	sbSizer4->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, _("Compass"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel3, wxID_ANY, _("Alignment") ), wxVERTICAL );

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


	m_panel3->SetSizer( sbSizer3 );
	m_panel3->Layout();
	sbSizer3->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, _("Alignment"), false );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( m_panel4, wxID_ANY, _("Rudder") ), wxVERTICAL );

	wxFlexGridSizer* fgSizer42;
	fgSizer42 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer42->SetFlexibleDirection( wxBOTH );
	fgSizer42->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer39;
	fgSizer39 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer39->SetFlexibleDirection( wxBOTH );
	fgSizer39->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText49 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Angle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText49->Wrap( -1 );
	fgSizer39->Add( m_staticText49, 0, wxALL, 5 );

	m_stRudderAngle = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudderAngle->Wrap( -1 );
	fgSizer39->Add( m_stRudderAngle, 0, wxALL, 5 );

	m_staticText42 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	fgSizer39->Add( m_staticText42, 0, wxALL, 5 );

	m_stRudderOffset = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudderOffset->Wrap( -1 );
	fgSizer39->Add( m_stRudderOffset, 0, wxALL, 5 );

	m_staticText44 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Scale"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	fgSizer39->Add( m_staticText44, 0, wxALL, 5 );

	m_stRudderScale = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudderScale->Wrap( -1 );
	fgSizer39->Add( m_stRudderScale, 0, wxALL, 5 );

	m_staticText46 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Non Linearity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	fgSizer39->Add( m_staticText46, 0, wxALL, 5 );

	m_stRudderNonlinearity = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("-----"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stRudderNonlinearity->Wrap( -1 );
	fgSizer39->Add( m_stRudderNonlinearity, 0, wxALL, 5 );


	fgSizer42->Add( fgSizer39, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer40;
	fgSizer40 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer40->SetFlexibleDirection( wxBOTH );
	fgSizer40->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_button22 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("Centered"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button22, 0, wxALL, 5 );

	m_button29 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("Reset Calibration"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button29, 0, wxALL, 5 );

	m_button23 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("Starboard Range"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button23, 0, wxALL, 5 );

	m_button28 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("Port Range"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer40->Add( m_button28, 0, wxALL, 5 );


	fgSizer42->Add( fgSizer40, 1, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer411;
	fgSizer411 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer411->SetFlexibleDirection( wxBOTH );
	fgSizer411->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText51 = new wxStaticText( sbSizer7->GetStaticBox(), wxID_ANY, _("Range"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer411->Add( m_staticText51, 0, wxALL, 5 );

	m_sRudderRange = new wxSpinCtrl( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 10, 90, 30 );
	fgSizer411->Add( m_sRudderRange, 0, wxALL, 5 );

	m_button172 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, _("?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button172->SetMaxSize( wxSize( 40,-1 ) );

	fgSizer411->Add( m_button172, 0, wxALL, 5 );


	fgSizer42->Add( fgSizer411, 1, wxEXPAND, 5 );


	sbSizer7->Add( fgSizer42, 1, wxEXPAND, 5 );


	m_panel4->SetSizer( sbSizer7 );
	m_panel4->Layout();
	sbSizer7->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, _("Rudder"), false );

	fgSizer19->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );

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
	m_button29->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderResetCalibration ), NULL, this );
	m_button23->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderStarboardRange ), NULL, this );
	m_button28->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderPortRange ), NULL, this );
	m_sRudderRange->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnRudderRange ), NULL, this );
	m_button172->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutRudderCalibration ), NULL, this );
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
	m_button29->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderResetCalibration ), NULL, this );
	m_button23->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderStarboardRange ), NULL, this );
	m_button28->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnRudderPortRange ), NULL, this );
	m_sRudderRange->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( CalibrationDialogBase::OnRudderRange ), NULL, this );
	m_button172->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnAboutRudderCalibration ), NULL, this );
	m_sdbSizer3OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CalibrationDialogBase::OnClose ), NULL, this );

}
