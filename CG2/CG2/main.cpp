//
//  main.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "glfuncs.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("ANSHA ABDUL");
    
    glutDisplayFunc(GLFuncs::Display);
    glutKeyboardFunc(GLFuncs::Keyboard);
    glutReshapeFunc(GLFuncs::Resize);
    glutIdleFunc(GLFuncs::Idle);
    
    glClearColor(0.3, 0.3, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glutSwapBuffers();
    
    glutMainLoop();
    
    return 0;
}
