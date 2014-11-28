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

windowProperties wp = new windowProperties(false, 0, 0, 640, 480);

GLFuncs::GLFuncs():m_isFullScreen(false)
{
    
}

void GLFuncs::Idle()
{
    glutPostRedisplay();
}

void GLFuncs::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
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
    
    gluLookAt(2.5, 0.5, 2.5, 0, 0, 0, 0, 1, 0);
    
    glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}