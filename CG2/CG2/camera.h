//
//  camera.h
//  CG2
//
//  Created by Andrey Bogdanov on 28.11.14.
//  Copyright (c) 2014 Andrey Bogdanov. All rights reserved.
//

#ifndef __CG2__camera__
#define __CG2__camera__

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

class glCamera
{
public:
    glCamera();
    glCamera(GLdouble x, GLdouble y, GLdouble z);
    ~glCamera();
    
    void set_camera(GLdouble x, GLdouble y, GLdouble z);
    void set_lookPoint(GLdouble x, GLdouble y, GLdouble z);
    GLdouble get_x();
    GLdouble get_y();
    GLdouble get_z();
    
    GLdouble get_look_x();
    GLdouble get_look_y();
    GLdouble get_look_z();
private:
    GLdouble m_x_position;
    GLdouble m_y_position;
    GLdouble m_z_position;
    
    GLdouble m_x_lookPoint;
    GLdouble m_y_lookPoint;
    GLdouble m_z_lookPoint;
};

#endif /* defined(__CG2__camera__) */
