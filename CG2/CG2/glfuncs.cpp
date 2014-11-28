//
//  glfuncs.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#include <GLUT/GLUT.h>
#include "glfuncs.h"

bool isFullScreen = false;

GLFuncs::GLFuncs():m_isFullScreen(false)
{
    
}

void GLFuncs::Idle()
{
    
}

void GLFuncs::Display()
{
    
}

void GLFuncs::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'f')
    {
        if(isFullScreen == false)
        {
            glutFullScreen();
            isFullScreen = true;
        }
        else
        {
            glutReshapeWindow(640, 480);
            glutPositionWindow(0,0);
            isFullScreen = false;
        }
    }
}

void GLFuncs::Resize(int W, int h)
{
    
}