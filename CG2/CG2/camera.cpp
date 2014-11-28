//
//  camera.cpp
//  CG2
//
//  Created by Andrey Bogdanov on 28.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#include "camera.h"

glCamera::glCamera():m_x_position(0),
                     m_y_position(0),
                     m_z_position(-3)
{
    
}

glCamera::glCamera(GLdouble x, GLdouble y, GLdouble z)
{
    set_camera(x, y, z);
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