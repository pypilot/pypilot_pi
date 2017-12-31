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

#include "pypilotUI.h"
#include "ConfigurationDialog.h"

ConfigurationDialog::ConfigurationDialog(wxWindow* parent) :
    ConfigurationDialogBase(parent)
{
}

void ConfigurationDialog::Open()
{
}

void ConfigurationDialog::OnAboutForwardnema( wxCommandEvent& event )
{
}

void ConfigurationDialog::OnAboutEnableOverlay( wxCommandEvent& event )
{
}

void ConfigurationDialog::OnCalibration( wxCommandEvent& event )
{
}

void ConfigurationDialog::OnInformation( wxCommandEvent& event )
{
}

void ConfigurationDialog::OnCancel( wxCommandEvent& event )
{
    Hide();
}

void ConfigurationDialog::OnOk( wxCommandEvent& event )
{
   
}
