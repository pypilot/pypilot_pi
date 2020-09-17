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

#include <wx/wx.h>

#include "CalibrationPlot.h"

bool json_to_float(Json::Value &value, float p[], unsigned int count)
{
    if(!value.isArray() || value.size() < count)
        return false;
    for(unsigned int i=0; i<count; i++) {
        if(!value[i].isNumeric())
           return false;
        p[i] = value[i].asFloat();
    }
    return true;
}

void json_to_float_3_array(Json::Value &value, std::vector<point> &points)
{
    points.clear();
    if(!value.isArray())
        return;
    for(unsigned int i=0; i<value.size(); i++) {
        point p;
        if(json_to_float(value[i], p.p, 3))
            points.push_back(p);
    }
}

void TranslateAfter(float x, float y, float z)
{
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    glLoadIdentity();
    glTranslatef(x, y, z);
    glMultMatrixf(m);
}

void RotateAfter(float ang, float x, float y, float z)
{
    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    glLoadIdentity();
    glRotatef(ang, x, y, z);
    glMultMatrixf(m);
}

void rotate_mouse(float dx, float dy)
{
    if(dx || dy)
        RotateAfter(powf(dx*dx + dy*dy, .2f), dy, dx, 0);
}

int attribs[] =  {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, WX_GL_STENCIL_SIZE, 8, 0};
CalibrationPlot::CalibrationPlot(wxWindow *parent, wxString name)
    : wxGLCanvas(parent, wxID_ANY, attribs),
      m_glContext(this),
      m_name(name),
      m_userscale(.5),
      m_cal{0, 0, 0, 1, 0}
{

    std::vector<point> points;
    int lats = 16, lons = 32;
    for(int lat=1; lat<lats; lat++) {
        float flat = M_PI*(float(lat)/(lats-1)-.5);
        for(int lon=0; lon<lons; lon++) {
            float flon = 2*M_PI*(float(lon)/(lons-1));
            point p;
            p.p[0] = cos(flat) * cos(flon);
            p.p[1] = cos(flat) * sin(flon);
            p.p[2] = sin(flat);

            points.push_back(p);
        }
    }

    for(int lon=1; lon<lons/2; lon++) {
        float flon = 2*M_PI*(float(lon)/(lons-1));
        for(int lat=0; lat<=lats*2; lat++) {
            float flat = M_PI*(float(lat)/(lats)+.5);
            point p;
            p.p[0] = cos(flat) * cos(flon);
            p.p[1] = cos(flat) * sin(flon);
            p.p[2] = sin(flat);

            points.push_back(p);
        }
    }
    
    

    m_spherepoints = points.size();
    m_sphere = new GLfloat[m_spherepoints*3];
    for(int i=0; i<m_spherepoints; i++)
        for(int j=0; j<3; j++)
            m_sphere[i*3+j] = points[i].p[j];
}

CalibrationPlot::~CalibrationPlot()
{
    delete [] m_sphere;
}

void CalibrationPlot::Receive(std::string name, Json::Value &value)
{
//    if(name == "imu.fusionQPose")
//        json_to_float(value, m_fusionQPose, 4);
//    else if(name == "imu.alignmentQ")
//        json_to_float(value, m_alignmentQ, 4);
    if(name == "imu."+m_name) {
        point p;
        while(m_recentpoints.size() >= 20) {
            for(int i=0; i<19; i++)
                m_recentpoints[i] = m_recentpoints[i+1];
            m_recentpoints.pop_back();
        }
        if(json_to_float(value, p.p, 3))
            m_recentpoints.push_back(p);
    } else if(name == "imu."+m_name+".calibration.sigmapoints")
        json_to_float_3_array(value, m_sigmapoints);
    else if(name == "imu."+m_name+".calibration.points")
        json_to_float_3_array(value, m_points);
    else if(name == "imu."+m_name+".calibration") {
        if(value.isArray() && value.size() > 0)
            json_to_float(value[0], m_cal, m_name == "accel" ? 4 : 5);
    }
}

void CalibrationPlot::OnPaint()
{
    SetCurrent( m_glContext );
    wxPaintDC dc( this );

    int w, h;
    GetClientSize( &w, &h );
    glViewport( 0, 0, (GLint) w, (GLint) h );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ar = float(w) / float(h);
    float fac = .05f;
    glFrustum( -fac*ar, fac*ar, -fac, fac, .1, 15 );
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    float s = m_userscale;
    if(m_name == "compass")
        s*=.016f;
    glScalef(s, s, s);
    TranslateAfter( 0, 0, -1 );

    //glPolygonMode(GL_FRONT_AND_BACK, self.mode)
    glLineWidth(1);

    //q = quaternion.multiply(self.fusionQPose, self.alignmentQ)
    //down = quaternion.rotvecquat([0, 0, 1], quaternion.conjugate(q))
    //glRotatef(-math.degrees(quaternion.angle(q)), *q[1:])

    glColor3f(0.0f, .3f, .8f);
    glPointSize(1);
    glPushMatrix();
    s = m_cal[3];
    glScalef(s, s, s);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m_sphere);
    glDrawArrays(GL_LINE_STRIP, 0, m_spherepoints);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();

    glTranslatef(-m_cal[0], -m_cal[1], -m_cal[2]);
                
    glColor3f(1, 1, 0);
    glPointSize(4);
    glBegin(GL_POINTS);
    for(unsigned int i=0; i<m_sigmapoints.size(); i++)
        glVertex3fv(m_sigmapoints[i].p);
    glEnd();

    glColor3f(0, 1, 1);
    glPointSize(4);
    glBegin(GL_POINTS);
    for(unsigned int i=0; i<m_points.size(); i++)
        glVertex3fv(m_points[i].p);
    glEnd();

    glPointSize(2);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for(unsigned int i=0; i<m_recentpoints.size(); i++) {
        glVertex3fv(m_recentpoints[i].p);
    }
    glEnd();
    
    glPopMatrix();
    SwapBuffers();
}

void CalibrationPlot::OnMouseEvents( wxMouseEvent& event )
{
    wxPoint pos = event.GetPosition();
    if(event.LeftDown())
        m_lastmouse = pos;

    if(event.Dragging()) {
        Refresh(); // to set gl context
        rotate_mouse(pos.x - m_lastmouse.x,
                     pos.y - m_lastmouse.y);
        m_lastmouse = pos;
    }

    float rotation = event.GetWheelRotation() / 60.0;
    if(rotation) {
        while(rotation > 0 && m_userscale < 1) {
            m_userscale /= .9f;
            rotation--;
        }
        while(rotation < 0 && m_userscale > .1)  {
            m_userscale *= .9f;
            rotation++;
        }
        Refresh();
    }
}
