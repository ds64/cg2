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

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
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
    
    GLFuncs::lightEnable();
    GLFuncs::fogEnable();
    GLFuncs::loadTexture("/Users/playingg0d/Documents/Projects/cg2/CG2/CG2/Wood.bmp");
    
    glutSwapBuffers();                                          // Swap buffers for double buffering
    
    glutMainLoop();                                             // Enter OpenGL main loop
    
    return 0;
}
