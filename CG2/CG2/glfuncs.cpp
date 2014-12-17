//
//  glfuncs.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//
//  PURPOSE:
//      * OpenGL handlers
//      * Main display function
//      * Rendering
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#include "glfuncs.h"
#include "windowProperties.h"
#include "camera.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

// Predefined colors

double color_red[3] = {1.0f, 0.0f, 0.0f};
double color_green[3] = {0.0f, 1.0f, 0.0f};
double color_blue[3] = {0.0f, 0.0f, 1.0f};

double color_black[3] = {0.0f, 0.0f, 0.0f};
double color_white[3] = {1.0f, 1.0f, 1.0f};

// windowProperties, glCamera, GLFuncs classes init

windowProperties wp = *new windowProperties(false, 0, 0, 640, 480);
glCamera glCam = *new glCamera();
GLFuncs glf = *new GLFuncs();

float x_angle = 0, y_angle = 0;

float x_restrict_1 = 12, x_restrict2 = -12;
float z_restrict_1 = -12, z_restrict2 = -32;

bool door = false;

// GLFuncs default constructor
// Fullscreen sets to false

GLFuncs::GLFuncs():m_isFullScreen(false)
{
    
}

// Load .bmp texture

GLuint GLFuncs::loadTexture(const char *fileName)
{
    unsigned char header[54];
    unsigned width, height;
    unsigned int imageSize;
    
    unsigned char *data;
    
    FILE * f = fopen(fileName, "rb");
    if(!f)
    {
        std::cout << "File can not be opened" << std::endl;
        return false;
    }
    
    if(fread(header, 1, 54, f)!=54)
    {
        std::cout << "Not a .bmp file" << std::endl;
        return false;
    }
    
    if ( header[0]!='B' || header[1]!='M' )
    {
        std::cout << "Incorrect .bmp file" << std::endl;
        return 0;
    }
    
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    if (imageSize==0)
    {
        imageSize=width*height*3;
    }
    
    data = new unsigned char [imageSize];

    fread(data,1,imageSize,f);
    
    fclose(f);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return textureID;
}

// Enable light

void GLFuncs::lightEnable()
{
    glEnable(GL_LIGHT0);
    
    float pos[4] = {0, 15, 20, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    float dir[3] = {0,0,0};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

// Enable fog

void GLFuncs::fogEnable()
{
    float fog[4] = {0.1, 0.5, 0.7, 1};
    
    glEnable(GL_FOG);
    
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, 50);
    glFogfv(GL_FOG_COLOR, fog);
}

// Idle function

void GLFuncs::Idle()
{ 
    glutPostRedisplay();            // Redisplay buffer
}

// Display function

void GLFuncs::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear color and depth buffers
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 0.5, 1000);
    
    gluLookAt(0, 5, 3, 0, 5, 0, 0, 1, 0);
    
    glOrtho(-1.0, 1.0, -1, 1, -1, 1);
    
    glTranslated(glCam.get_x(), glCam.get_y(), glCam.get_z());
    glRotated(x_angle,0,1,0);
    glRotated(y_angle,1,0,0);
    
    glMatrixMode(GL_PROJECTION);
    
    // Render house
    glColor3dv(color_white);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-100,0,-100);
    glTexCoord2d(0, 50);
    glVertex3d(-100, 0, 100);
    glTexCoord2d(50, 50);
    glVertex3d(100,0,100);
    glTexCoord2d(50, 0);
    glVertex3d(100, 0, -100);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3d(-10,10,10);
    glVertex3d(0,15,10);
    glVertex3d(0,15,30);
    glVertex3d(-10,10,30);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3d(10,10,10);
    glVertex3d(0,15,10);
    glVertex3d(0,15,30);
    glVertex3d(10,10,30);
    glEnd();
    
    glColor3d(0.7, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,30);
    glVertex3d(10,10,30);
    glVertex3d(0,15,30);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,10);
    glVertex3d(10,10,10);
    glVertex3d(0,15,10);
    glEnd();
    
    glColor3dv(color_white);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, 0, 30);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, 30);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,30);
    glTexCoord2d(1, 0);
    glVertex3d(10, 0, 30);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, 0, 10);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, 10);
    glTexCoord2d(1, 1);
    glVertex3d(-10,10,30);
    glTexCoord2d(1, 0);
    glVertex3d(-10, 0, 30);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(10, 0, 10);
    glTexCoord2d(0, 1);
    glVertex3d(10, 10, 10);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,30);
    glTexCoord2d(1, 0);
    glVertex3d(10, 0, 30);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, 0, 10);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, 10);
    glTexCoord2d(1, 1);
    glVertex3d(-2,10,10);
    glTexCoord2d(1, 0);
    glVertex3d(-2, 0, 10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(2, 0, 10);
    glTexCoord2d(0, 1);
    glVertex3d(2, 10, 10);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,10);
    glTexCoord2d(1, 0);
    glVertex3d(10, 0, 10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-2, 6, 10);
    glTexCoord2d(0, 0.5);
    glVertex3d(-2, 10, 10);
    glTexCoord2d(0.5, 0.5);
    glVertex3d(2,10,10);
    glTexCoord2d(0.5, 0);
    glVertex3d(2, 6, 10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    if(door == false)
    {
        glColor3d(0,0.5,0);
        glBegin(GL_QUADS);
        glVertex3d(-2, 0, 10);
        glVertex3d(-2, 6, 10);
        glVertex3d(2, 6,10);
        glVertex3d(2, 0, 10);
        glEnd();
    }
    else
    {
        glColor3d(0,0.5,0);
        glBegin(GL_QUADS);
        glVertex3d(-2, 0, 10);
        glVertex3d(-2, 6, 10);
        glVertex3d(-2, 6, 6);
        glVertex3d(-2, 0, 6);
        glEnd();
    }
 
    glFinish();
    
    glutSwapBuffers();          // Swap buffers
}

// Keyboard handler

void GLFuncs::Keyboard(unsigned char key, int x, int y)
{
    // Go fullscreen or exit fullscreen
    if(key == 'f')
    {
        // Set fullscreen
        if(wp.get_fullscreen() == false)
        {
            // Set new position to windowProperties class
            wp.set_position(glutGet((GLenum)GLUT_WINDOW_X), glutGet((GLenum)GLUT_WINDOW_Y));
            glutFullScreen();           // Enter fullscreen
            wp.set_fullscreen(true);    // Save fullscreen property
        }
        // Exit fullscreen
        else
        {
            // Exit fullscreen by reshaping
            glutReshapeWindow(wp.get_window_size().get_width(), wp.get_window_size().get_height());
            glutPositionWindow(wp.get_position().get_x(),wp.get_position().get_y());
            wp.set_fullscreen(false);
        }
    }
    
    // Go forward
    if((key == 'w') && ((glCam.get_z() > z_restrict_1) || door != true))
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() - 0.5);
    }
    else
    {
        door = true;
    }
    
    // Go back
    if(key == 's')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() + 0.5);
    }
    
    // Go left
    if(key == 'a' && (glCam.get_x() < x_restrict_1))
    {
        glCam.set_camera(glCam.get_x() + 0.5, glCam.get_y(), glCam.get_z());
    }
    
    // Go right
    if(key == 'd' && (glCam.get_x() > x_restrict2))
    {
        glCam.set_camera(glCam.get_x() - 0.5, glCam.get_y(), glCam.get_z());
    }
}

void GLFuncs::Special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT && x_angle < 45.0f)
    {
        x_angle += 5.0f;
    }
    if(key == GLUT_KEY_RIGHT && x_angle > -45.0f)
    {
        x_angle -= 5.0f;
    }
    
    if(key == GLUT_KEY_UP && y_angle < 45.0f)
    {
        y_angle += 5.0f;
    }
    if(key == GLUT_KEY_DOWN && y_angle >= 0.0f)
    {
        y_angle -= 5.0f;
    }
}

// Resize handler
void GLFuncs::Resize(int w, int h)
{
    // If not fullscreen save current size
    if(wp.get_fullscreen() != true)
    {
        wp.set_size(w, h);
    }
    
    glViewport(0, 0, w, h);
}