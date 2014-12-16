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

// GLFuncs default constructor
// Fullscreen sets to false

GLFuncs::GLFuncs():m_isFullScreen(false)
{
    
}

// Load .bmp texture

GLuint GLFuncs::loadTexture(char *fileName)
{
    unsigned char header[54];
    unsigned int dataPos;
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
    
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    if (imageSize==0)
    {
        imageSize=width*height*3;
    }
    if (dataPos==0)
    {
        dataPos=54;
    }
    
    data = new unsigned char [imageSize];

    fread(data,1,imageSize,f);
    
    fclose(f);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return textureID;
}

// Enable light

void GLFuncs::lightEnable()
{
    glEnable(GL_LIGHT0);
    
    float pos[4] = {0, 30, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    float dir[3] = {0,0,0};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

// Draw rect in Z plane

void GLFuncs::triangleDrawRectXY(double x1, double x2, double y1, double y2, double z)
{
    // Use triangles
    glBegin(GL_TRIANGLES);
    // First triangle vertices
    glVertex3d(x1, y1, z);
    glVertex3d(x2, y2, z);
    glVertex3d(x2, y1, z);
    // Second triangle vertices
    glVertex3d(x2, y2, z);
    glVertex3d(x1, y1, z);
    glVertex3d(x1, y2, z);
    glEnd();
}

// Draw rect in Y plane

void GLFuncs::triangleDrawRectXZ(double x1, double x2, double z1, double z2, double y)
{
    // Use triangles
    glBegin(GL_TRIANGLES);
    // First triangle vertices
    glVertex3d(x1, y, z1);
    glVertex3d(x2, y, z2);
    glVertex3d(x2, y, z1);
    // Second triangle vertices
    glVertex3d(x2, y, z2);
    glVertex3d(x1, y, z1);
    glVertex3d(x1, y, z2);
    glEnd();
}

// Draw rect in Z plane

void GLFuncs::triangleDrawRectYZ(double y1, double y2, double z1, double z2, double x)
{
    // Use triangles
    glBegin(GL_TRIANGLES);
    // First triangle vertices
    glVertex3d(x, y1, z1);
    glVertex3d(x, y2, z2);
    glVertex3d(x, y2, z1);
    // Second triangle vertices
    glVertex3d(x, y2, z2);
    glVertex3d(x, y1, z1);
    glVertex3d(x, y1, z2);
    glEnd();
}

// Draw rect with triangles

void GLFuncs::triangleDrawRectXYZ(double x1, double x2, double y1, double y2, double z1, double z2)
{
    // Use triangles
    glBegin(GL_TRIANGLES);
    // First triangle vertices
    glVertex3d(x1,y1,z1);
    glVertex3d(x1,y1,z2);
    glVertex3d(x2,y2,z1);
    // Second triangle vertices
    glVertex3d(x1,y1,z2);
    glVertex3d(x2,y2,z2);
    glVertex3d(x2,y2,z1);
    glEnd();
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
    // Set camera to new value
    gluLookAt(glCam.get_x(), glCam.get_y(), glCam.get_z(), glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z(), 0, 1, 0);
    
    glMatrixMode(GL_PROJECTION);
    
    // Render house
    glColor3dv(color_white);
    glf.triangleDrawRectXZ(-100, 100, -100, 100, 0);
    
    glColor3dv(color_red);
    GLFuncs::loadTexture("/Users/playingg0d/Documents/cg2/CG2/CG2/biboran.bmp");
    glEnable(GL_TEXTURE_2D);
    glf.triangleDrawRectXY(-10, 10, 0, 10, 0);
    glf.triangleDrawRectXY(-10, 10, 0, 10, 20);
    glf.triangleDrawRectYZ(0, 10, 0, 20, -10);
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
    
    glf.triangleDrawRectXYZ(-10, 0, 10, 15, 0, 20);
    glf.triangleDrawRectXYZ(10, 0, 10, 15, 0, 20);
    
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
    if(key == 'w')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() + 0.5);
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z() + 0.5);
    }
    
    // Go back
    if(key == 's')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() - 0.5);
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z() - 0.5);
    }
    
    // Go left
    if(key == 'a')
    {
        glCam.set_camera(glCam.get_x() - 0.5, glCam.get_y(), glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x() - 0.5, glCam.get_look_y(), glCam.get_look_z());
    }
    
    // Go right
    if(key == 'd')
    {
        glCam.set_camera(glCam.get_x() + 0.5, glCam.get_y(), glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x() + 0.5, glCam.get_look_y(), glCam.get_look_z());
    }
    
    // Go up
    if(key == 'q')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y() + 0.5, glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y() + 0.5, glCam.get_look_z());
    }
    
    // Go down
    if(key == 'e')
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y() - 0.5, glCam.get_z());
        glCam.set_lookPoint(glCam.get_look_x(), glCam.get_look_y() - 0.5, glCam.get_look_z());
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
    
    // Set camera
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glFrustum(-1.0*w/h, 1.0*w/h, -1, 1, 1, 1000);

    gluLookAt(glCam.get_x(), glCam.get_y(), glCam.get_z(), glCam.get_look_x(), glCam.get_look_y(), glCam.get_look_z(), 0, 1, 0);
    
    glOrtho(-2.0*w/h, 2.0*w/h, -2, 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}