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
    void triangleDrawRectXYZ(double x1, double x2, double y1, double y2, double z1, double z2);
    
    static void lightEnable();
    
    static void loadTexture(char* fileName);
private:
    bool m_isFullScreen;
};

#endif /* defined(__CG2__glfuncs__) */
