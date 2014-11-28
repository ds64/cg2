//
//  glfuncs.h
//  CG2
//
//  Created by Andrey Bogdanov on 27.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#ifndef __CG2__glfuncs__
#define __CG2__glfuncs__

#include <stdio.h>

class GLFuncs
{
public:
    GLFuncs();
    
    static void Idle();
    static void Resize(int w, int h);
    static void Display();
    static void Keyboard(unsigned char key, int x, int y);
    
    void triangleDrawRectXY(double x1, double x2, double y1, double y2, double z);
    void triangleDrawRectXZ(double x1, double x2, double z1, double z2, double y);
    void triangleDrawRectYZ(double y1, double y2, double z1, double z2, double x);
private:
    bool m_isFullScreen;
};

double color_red[3] = {1.0f, 0.0f, 0.0f};
double color_green[3] = {0.0f, 1.0f, 0.0f};
double color_blue[3] = {0.0f, 0.0f, 1.0f};

double color_black[3] = {0.0f, 0.0f, 0.0f};
double color_white[3] = {1.0f, 1.0f, 1.0f};

#endif /* defined(__CG2__glfuncs__) */
