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
    static void Resize(int W, int h);
    static void Display();
    static void Keyboard(unsigned char key, int x, int y);
private:
    bool m_isFullScreen;
};

#endif /* defined(__CG2__glfuncs__) */
