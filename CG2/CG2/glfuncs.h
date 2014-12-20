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
    static void Special(int key, int x, int y);
    
    static void lightEnable();
    static void fogEnable();
    
    static bool collisionDetect(int type);
    static GLuint loadTexture(const char* fileName);
private:
    bool m_isFullScreen;
    
    enum{
        FORWARD,
        BACK,
        LEFT,
        RIGHT
    };
};

#endif /* defined(__CG2__glfuncs__) */
