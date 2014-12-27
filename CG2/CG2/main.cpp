//
//  main.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//
//  PURPOSE:
//      * OpenGL initialisation and entering main OpenGL loop
//

#if defined (__APPLE__)
	#include <GLUT/GLUT.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif defined (_WIN32)
	#include <Windows.h>
	#include <glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#include <iostream>
#include "glfuncs.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                      // GLUT initialisation with command line arguments
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);   // Set OpenGL Display Mode
                                                                // RGB color
                                                                // Double buffer
                                                                // Z buffer (depth)
    glutInitWindowPosition(0, 0);                               // Initial position set to 0,0
    glutInitWindowSize(640, 480);                               // Default resolution 640x480
    glutCreateWindow("Bogdanov Andrey 4105");                   // Window title
    
    glutDisplayFunc(GLFuncs::Display);                          // OpenGL Display handler set
    glutKeyboardFunc(GLFuncs::Keyboard);                        // OpenGL Keyboard handler set
    glutReshapeFunc(GLFuncs::Resize);                           // OpenGL Resize handler set
    glutIdleFunc(GLFuncs::Idle);                                // OpenGL Idle handler set
    glutSpecialFunc(GLFuncs::Special);                          // OpenGL Special Keyboard handler
    
    glClearColor(0.3, 0.3, 0.5, 1);                             // Set background color
    glClear(GL_COLOR_BUFFER_BIT);                               // Clear OpenGL window buffer
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLFuncs::lightEnable();
    GLFuncs::fogEnable();
#if defined (__APPLE__)
    GLFuncs::loadTexture("/Users/playingg0d/Documents/Projects/cg2/CG2/CG2/Wood.bmp");
#elif defined (_WIN32)
	GLFuncs::loadTexture("./Wood.bmp");
#endif
    
    glutSwapBuffers();                                          // Swap buffers for double buffering
    
    glutMainLoop();                                             // Enter OpenGL main loop
    
    return 0;
}
