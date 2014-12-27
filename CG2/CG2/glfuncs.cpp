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

#include "glfuncs.h"
#include "windowProperties.h"
#include "camera.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

#if defined (_WIN32)
	#define _CRT_SECURE_NO_WARNINGS
#endif

#define DEBUG_MODE 1

// Predefined colors

double color_red[3] = {1.0f, 0.0f, 0.0f};
double color_green[3] = {0.0f, 1.0f, 0.0f};
double color_blue[3] = {0.0f, 0.0f, 1.0f};

double color_black[3] = {0.0f, 0.0f, 0.0f};
double color_white[3] = {1.0f, 1.0f, 1.0f};

int atime = 0;
double colortime = 0.0;

// windowProperties, glCamera, GLFuncs classes init

windowProperties wp = *new windowProperties(false, 0, 0, 640, 480);
glCamera glCam = *new glCamera();
GLFuncs glf = *new GLFuncs();

float x_angle = 0, y_angle = 0;

float x_restrict_1 = -10, x_restrict_2 = 10;
float z_restrict_1 = 10, z_restrict_2 = 30;

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
    
	FILE * f;
	fopen_s(&f, fileName, "rb");
    if(!f)
    {
#ifdef DEBUG_MODE
        std::cout << "File can not be opened" << std::endl;
#endif
        return 0;
    }
    
    if(fread(header, 1, 54, f)!=54)
    {
#ifdef DEBUG_MODE
        std::cout << "Not a .bmp file" << std::endl;
#endif
        return 0;
    }
    
    if ( header[0]!='B' || header[1]!='M' )
    {
#ifdef DEBUG_MODE
        std::cout << "Incorrect .bmp file" << std::endl;
#endif
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
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return textureID;
}

// Enable light

void GLFuncs::lightEnable()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    
    glEnable(GL_NORMALIZE);
    
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    
    glEnable(GL_COLOR_MATERIAL);
}

// Enable fog

void GLFuncs::fogEnable()
{
    float fog[4] = {0.1, 0.5, 0.7, 1};
    
    glEnable(GL_FOG);
    
    glFogf(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0);
    glFogf(GL_FOG_END, 70);
    glFogfv(GL_FOG_COLOR, fog);
}

// Check if collision hit

bool GLFuncs::collisionDetect(int type)
{
    if(type == GLFuncs::FORWARD)
    {
        if(glCam.get_z() < z_restrict_1 - 0.5)
            return false;
        else if(glCam.get_z() == z_restrict_1 - 0.5 && door == true)
            return false;
        else if(glCam.get_z() > z_restrict_1 - 0.5 && glCam.get_z() < z_restrict_2)
            return false;
        else if(glCam.get_z() > z_restrict_2)
            return false;
    }
    if(type == GLFuncs::BACK)
    {
        if(glCam.get_z() > z_restrict_1 + 0.5)
            return false;
        else if(glCam.get_z() == z_restrict_1 + 0.5 && door == true)
            return false;
        else if(glCam.get_z() < z_restrict_2 && glCam.get_z() > z_restrict_1 + 0.5)
            return false;
        else if(glCam.get_z() < z_restrict_1 + 0.5)
            return false;
    }
    if(type == GLFuncs::LEFT)
    {
        return false;
    }
    if(type == GLFuncs::RIGHT)
    {
        return false;
    }
    return true;
}

// Idle function

void GLFuncs::Idle()
{ 
    glutPostRedisplay();            // Redisplay buffer
}

// Display function

void GLFuncs::Display()
{    
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear color and depth buffers
    
    GLfloat mat_dif[] = {0.3,0.3,0.3,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
    
    glTranslated(glCam.get_x(), glCam.get_y(), glCam.get_z());
   
#ifdef DEBUG_MODE
    std::cout << "Current position: [" << glCam.get_x() << ";" <<
              glCam.get_y() << ";" << glCam.get_z() << "]" << std::endl;
#endif
    
    glRotatef(360.0f - y_angle, 0, 1.0f,0);
    glRotatef(360.0f - x_angle, 1.0f, 0,0);

    // Render plane
    glColor3dv(color_white);
    for(float i = -60; i < 60; i+=0.5)
    {
        for(float j = -60; j < 60; j+=0.5)
        {
            glBegin(GL_QUADS);
            glNormal3d(0,1,0);
            glTexCoord2d(0, 0);
            glVertex3d(i,-4,j);
            glTexCoord2d(0, 50);
            glVertex3d(i, -4, j+1);
            glTexCoord2d(50, 50);
            glVertex3d(i+1,-4,j+1);
            glTexCoord2d(50, 0);
            glVertex3d(i+1, -4, j);
            glEnd();
        }
    }
    
    // Render house
    glBegin(GL_QUADS);
    glVertex3d(-10,10,-10);
    glVertex3d(0,15,-10);
    glVertex3d(0,15,-30);
    glVertex3d(-10,10,-30);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex3d(10,10,-10);
    glVertex3d(0,15,-10);
    glVertex3d(0,15,-30);
    glVertex3d(10,10,-30);
    glEnd();
    
    glColor3d(0.7, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,-30);
    glVertex3d(10,10,-30);
    glVertex3d(0,15,-30);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-10,10,-10);
    glVertex3d(10,10,-10);
    glVertex3d(0,15,-10);
    glEnd();
    
    glColor3dv(color_white);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, -4, -30);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, -30);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,-30);
    glTexCoord2d(1, 0);
    glVertex3d(10, -4, -30);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, -4, -10);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, -10);
    glTexCoord2d(1, 1);
    glVertex3d(-10,10,-30);
    glTexCoord2d(1, 0);
    glVertex3d(-10, -4, -30);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(10, -4, -10);
    glTexCoord2d(0, 1);
    glVertex3d(10, 10, -10);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,-30);
    glTexCoord2d(1, 0);
    glVertex3d(10, -4, -30);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-10, -4, -10);
    glTexCoord2d(0, 1);
    glVertex3d(-10, 10, -10);
    glTexCoord2d(1, 1);
    glVertex3d(-2,10,-10);
    glTexCoord2d(1, 0);
    glVertex3d(-2, -4, -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(2, -4, -10);
    glTexCoord2d(0, 1);
    glVertex3d(2, 10, -10);
    glTexCoord2d(1, 1);
    glVertex3d(10,10,-10);
    glTexCoord2d(1, 0);
    glVertex3d(10, -4, -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0);
    glVertex3d(-2, 6, -10);
    glTexCoord2d(0, 0.5);
    glVertex3d(-2, 10, -10);
    glTexCoord2d(0.5, 0.5);
    glVertex3d(2,10,-10);
    glTexCoord2d(0.5, 0);
    glVertex3d(2, 6, -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    // Render door
    if(door == false)
    {
        glColor3d(0,0.5,0);
        glBegin(GL_QUADS);
        glVertex3d(-2, -4, -10);
        glVertex3d(-2, 6, -10);
        glVertex3d(2, 6,-10);
        glVertex3d(2, -4, -10);
        glEnd();
    }
    else
    {
        glColor3d(0,0.5,0);
        glBegin(GL_QUADS);
        glVertex3d(-2, -4, -10);
        glVertex3d(-2, 6, -10);
        glVertex3d(-2, 6, -6);
        glVertex3d(-2, -4, -6);
        glEnd();
    }
    
    if(door == true)
    {
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
    else
    {
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
    }
    
    glPushMatrix();
    
    glRotatef(atime, atime, atime, 1);
    glTranslated(0, -4, 0);
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 0, -10);
    glVertex3d(-20, 0, -20);
    glVertex3d(-25,9,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 0, -10);
    glVertex3d(-30, 0, -10);
    glVertex3d(-25,9,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 0, -20);
    glVertex3d(-30, 0, -20);
    glVertex3d(-25,9,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-30, 0, -10);
    glVertex3d(-30, 0, -20);
    glVertex3d(-25,9,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 8, -10);
    glVertex3d(-20, 8, -20);
    glVertex3d(-25,7,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 8, -10);
    glVertex3d(-30, 8, -10);
    glVertex3d(-25,17,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 8, -20);
    glVertex3d(-30, 8, -20);
    glVertex3d(-25,17,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-30, 8, -10);
    glVertex3d(-30, 8, -20);
    glVertex3d(-25,17,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 16, -10);
    glVertex3d(-20, 16, -20);
    glVertex3d(-25,25,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 16, -10);
    glVertex3d(-30, 16, -10);
    glVertex3d(-25,25,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-20, 16, -20);
    glVertex3d(-30, 16, -20);
    glVertex3d(-25,25,-15);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex3d(-30, 16, -10);
    glVertex3d(-30, 16, -20);
    glVertex3d(-25,25,-15);
    glEnd();
    
    glPopMatrix();
    
    GLfloat light0_diffuse[3] = {1.0, static_cast<GLfloat>(colortime), static_cast<GLfloat>(1 - colortime)};
    GLfloat light0_position[4] = {0, 3, -10.0, 1.0};
    GLfloat light0_spot_direction[3] = {0, -1, static_cast<GLfloat>(-1.0*sin(atime/5))};
    GLfloat light0_spot_cutoff = 20.0f;
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light0_spot_cutoff);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direction);
    
    GLfloat light1_specular[3] = {0.7, 0.5, 0.0};
    GLfloat light1_position[4] = {0, 5, 0.0, 1.0};
    GLfloat light1_spot_direction[3] = {0.0, -1, 0.0};
    GLfloat light1_spot_cutoff = 90.0f;
    
    atime++;
    colortime += 0.01;
    
    if(atime == 90)
    {
        atime = 0;
    }
    
    if(colortime == 1)
    {
        colortime = 0.0;
    }
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, light1_spot_cutoff);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_direction);
    
    glFlush();
    
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
    
    // Go back
    if(key == 's' && collisionDetect(GLFuncs::BACK) == false)
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() - 0.5);
    }
    
    // Go forward
    if(key == 'w' && collisionDetect(GLFuncs::FORWARD) == false)
    {
        glCam.set_camera(glCam.get_x(), glCam.get_y(), glCam.get_z() + 0.5);
    }
    
    // Open door
    if(key == 'e')
    {
        door = !door;
    }
    
    // Go right
    if(key == 'd' && collisionDetect(GLFuncs::LEFT) == false)
    {
        glCam.set_camera(glCam.get_x() - 0.5, glCam.get_y(), glCam.get_z());
    }
    
    // Go left
    if(key == 'a' && collisionDetect(GLFuncs::RIGHT) == false)
    {
        glCam.set_camera(glCam.get_x() + 0.5, glCam.get_y(), glCam.get_z());
    }
}

void GLFuncs::Special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)
    {
        y_angle += 2.0f;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        y_angle -= 2.0f;
    }
    
    if(key == GLUT_KEY_UP && x_angle < 30.0f)
    {
        x_angle += 2.0f;
    }
    if(key == GLUT_KEY_DOWN && x_angle > -30.0f)
    {
        x_angle -= 2.0f;
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
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)w/(GLdouble)h,0.5,1000.0);
    glMatrixMode(GL_MODELVIEW);
    
    glViewport(0, 0, w, h);
}