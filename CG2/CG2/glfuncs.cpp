//
//  glfuncs.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include "glfuncs.h"
#include "windowProperties.h"
#include "camera.h"

windowProperties wp = *new windowProperties(false, 0, 0, 640, 480);
glCamera glCam = *new glCamera();

GLFuncs glf = *new GLFuncs();

GLFuncs::GLFuncs():m_isFullScreen(false)
{
    
}

void GLFuncs::triangleDrawRectXY(double x1, double x2, double y1, double y2, double z)
{
    glBegin(GL_TRIANGLES);
    glVertex3d(x1, y1, z);
    glVertex3d(x2, y2, z);
    glVertex3d(x2, y1, z);
    glVertex3d(x2, y2, z);
    glVertex3d(x1, y1, z);
    glVertex3d(x1, y2, z);
    glEnd();
}

void GLFuncs::triangleDrawRectXZ(double x1, double x2, double z1, double z2, double y)
{
    glBegin(GL_TRIANGLES);
    glVertex3d(x1, y, z1);
    glVertex3d(x2, y, z2);
    glVertex3d(x2, y, z1);
    glVertex3d(x2, y, z2);
    glVertex3d(x1, y, z1);
    glVertex3d(x1, y, z2);
    glEnd();
}

void GLFuncs::triangleDrawRectYZ(double y1, double y2, double z1, double z2, double x)
{
    glBegin(GL_TRIANGLES);
    glVertex3d(x, y1, z1);
    glVertex3d(x, y2, z2);
    glVertex3d(x, y2, z1);
    glVertex3d(x, y2, z2);
    glVertex3d(x, y1, z1);
    glVertex3d(x, y1, z2);
    glEnd();
}

void GLFuncs::Idle()
{
    glutPostRedisplay();
}

void GLFuncs::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glCam.get_x(), glCam.get_y(), glCam.get_z(), glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z(), 0, 1, 0);
    
    glMatrixMode(GL_PROJECTION);
    
    glColor3dv(color_white);
    glf.triangleDrawRectXZ(-100, 100, -100, 100, 0);
    
    glColor3dv(color_red);
    glf.triangleDrawRectXY(-10, 10, 0, 10, 0);
    glColor3dv(color_red);
    glf.triangleDrawRectXY(-10, 10, 0, 10, 20);
    glColor3dv(color_red);
    glf.triangleDrawRectYZ(0, 10, 0, 20, -10);
    glColor3dv(color_red);
    glf.triangleDrawRectYZ(0, 10, 0, 20, 10);
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,0);
    glVertex3d(10,10,0);
    glVertex3d(0,15,0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,20);
    glVertex3d(10,10,20);
    glVertex3d(0,15,20);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,0);
    glVertex3d(-10,10,20);
    glVertex3d(0,15,0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,20);
    glVertex3d(0,15,20);
    glVertex3d(0,15,0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(10,10,0);
    glVertex3d(10,10,20);
    glVertex3d(0,15,0);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(10,10,20);
    glVertex3d(0,15,20);
    glVertex3d(0,15,0);
    glEnd();
    
    glFinish();
    
    glutSwapBuffers();
}

void GLFuncs::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'f')
    {
        if(wp.get_fullscreen() == false)
        {
            wp.set_position(glutGet((GLenum)GLUT_WINDOW_X), glutGet((GLenum)GLUT_WINDOW_Y));
            glutFullScreen();
            wp.set_fullscreen(true);
        }
        else
        {
            glutReshapeWindow(wp.get_window_size().get_width(), wp.get_window_size().get_height());
            glutPositionWindow(wp.get_position().get_x(),wp.get_position().get_y());
            wp.set_fullscreen(false);
        }
    }
    
    if(key == 'w')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() + 0.5);
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z() + 0.5);
    }
    
    if(key == 's')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() - 0.5);
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z() - 0.5);
    }
    
    if(key == 'a')
    {
        glCam.set_camera(glCam.get_x() - 0.5, glCam.get_y(), glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x() - 0.5, glCam.get_look_y(), glCam.get_look_z());
    }
    
    if(key == 'd')
    {
        glCam.set_camera(glCam.get_x() + 0.5, glCam.get_y(), glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x() + 0.5, glCam.get_look_y(), glCam.get_look_z());
    }
    
    if(key == 'q')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y() + 0.5, glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y() + 0.5, glCam.get_look_z());
    }
    
    if(key == 'e')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y() - 0.5, glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y() - 0.5, glCam.get_look_z());
    }
}

void GLFuncs::Resize(int w, int h)
{
    if(wp.get_fullscreen() != true)
    {
        wp.set_size(w, h);
    }
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glFrustum(-1.0*w/h, 1.0*w/h, -1, 1, 1, 1000);

    gluLookAt(glCam.get_x(), glCam.get_y(), glCam.get_z(), glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z(), 0, 1, 0);
    
    glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}