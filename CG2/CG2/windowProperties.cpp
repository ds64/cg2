//
//  windowProperties.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 28.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//
//  PURPOSE:
//      * Storing window properties
//

#include "windowProperties.h"

// position class methods

position::position():m_x_position(0),
                     m_y_position(0)
{
    
}

position::position(int x, int y)
{
    this->set_position(x,y);
}

position::~position()
{
    
}

void position::set_position(int x, int y)
{
    m_x_position = x;
    m_y_position = y;
}

int position::get_x()
{
    return m_x_position;
}

int position::get_y()
{
    return m_y_position;
}

// windowsize class methods

windowSize::windowSize():m_width(640),
                         m_height(480)
{
    
}

windowSize::windowSize(int w, int h)
{
    this->set_size(w, h);
}

windowSize::~windowSize()
{
    
}

void windowSize::set_size(int w, int h)
{
    m_width = w;
    m_height = h;
}

int windowSize::get_width()
{
    return m_width;
}

int windowSize::get_height()
{
    return m_height;
}

// windowProperties methods

windowProperties::windowProperties():m_position(),
                                     m_window_size(),
                                     m_fullscreen(false)
{
    
}

windowProperties::windowProperties(bool fullscreen):m_position(),
                                                    m_window_size()
{
    this->set_fullscreen(fullscreen);
}

windowProperties::windowProperties(int posx, int posy, int w, int h):m_position(),
                                                                     m_window_size(),
                                                                     m_fullscreen(false)
{
    this->set_position(posx, posy);
    this->set_size(w, h);
}

windowProperties::windowProperties(bool fullscreen, int posx, int posy, int w, int h):m_position(),
                                                                                      m_window_size()
{
    this->set_fullscreen(fullscreen);
    this->set_position(posx, posy);
    this->set_size(w, h);
}

windowProperties::~windowProperties()
{
    
}

void windowProperties::set_fullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
}

void windowProperties::set_position(int x, int y)
{
    m_position.set_position(x, y);
}

void windowProperties::set_size(int w, int h)
{
    m_window_size.set_size(w, h);
}

bool windowProperties::get_fullscreen()
{
    return m_fullscreen;
}

position windowProperties::get_position()
{
    return m_position;
}

windowSize windowProperties::get_window_size()
{
    return m_window_size;
}