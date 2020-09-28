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

#include <vector>

#include <wx/glcanvas.h>
#include <json/json.h>

struct point {
    float p[3];
};

class CalibrationPlot : public wxGLCanvas
{
public:
    CalibrationPlot(wxWindow *parent, wxString name);
    ~CalibrationPlot();
    void Receive(std::string name, Json::Value &value);
    void OnPaint();
    void OnMouseEvents( wxMouseEvent& event );

private:
    std::vector<point> m_recentpoints, m_sigmapoints, m_points;
    float m_fusionQPose[4], m_alignmentQ[4];
    wxGLContext m_glContext;
    wxString m_name;
    float m_userscale;

    wxPoint m_lastmouse;
    float m_cal[5];

    int m_spherepoints;
    GLfloat *m_sphere;
};
