//
//  camera.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 28.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#include "camera.h"

glCamera::glCamera():m_x_position(0),
                     m_y_position(1),
                     m_z_position(-3),
                     m_x_lookPoint(0),
                     m_y_lookPoint(1),
                     m_z_lookPoint(0)
{
    
}

glCamera::glCamera(GLdouble x, GLdouble y, GLdouble z)
{
    set_camera(x, y, z);
    set_lookPoint(0, 0, 0);
}

glCamera::~glCamera()
{
    
}

void glCamera::set_camera(GLdouble x, GLdouble y, GLdouble z)
{
    m_x_position = x;
    m_y_position = y;
    m_z_position = z;
}

void glCamera::set_lookPoint(GLdouble x, GLdouble y, GLdouble z)
{
    m_x_lookPoint = x;
    m_y_lookPoint = y;
    m_z_lookPoint = z;
}

GLdouble glCamera::get_x()
{
    return m_x_position;
}

GLdouble glCamera::get_y()
{
    return m_y_position;
}

GLdouble glCamera::get_z()
{
    return m_z_position;
}

GLdouble glCamera::get_look_x()
{
    return m_x_lookPoint;
}

GLdouble glCamera::get_look_y()
{
    return m_y_lookPoint;
}

GLdouble glCamera::get_look_z()
{
    return m_z_lookPoint;
}