//
//  windowProperties.h
//  CG2
//
//  Created by Andrey Bogdanov on 28.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#ifndef __CG2__windowProperties__
#define __CG2__windowProperties__

#include <stdio.h>

class position
{
public:
    position();
    position(int x, int y);
    ~position();
    
    void set_position(int x, int y);
    int get_x();
    int get_y();
private:
    int m_x_position;
    int m_y_position;
};

class windowSize
{
public:
    windowSize();
    windowSize(int w, int h);
    ~windowSize();
    
    void set_size(int w, int h);
    int get_width();
    int get_height();
private:
    int m_width;
    int m_height;
};

class windowProperties
{
public:
    windowProperties();
    windowProperties(bool fullscreen);
    windowProperties(int posx, int posy, int w, int h);
    windowProperties(bool fullscreen, int posx, int posy, int w, int h);
    ~windowProperties();
    
    void set_fullscreen(bool fullscreen);
    void set_position(int x, int y);
    void set_size(int w, int h);
    
    bool get_fullscreen();
    position get_position();
    windowSize get_window_size();
private:
    bool m_fullscreen;
    position m_position;
    windowSize m_window_size;
};

#endif /* defined(__CG2__windowProperties__) */
