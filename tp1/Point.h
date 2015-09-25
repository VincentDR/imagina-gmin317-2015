/*
 * Point.h
 *
 *  Created on: 22 sept. 2015
 *      Author: Vincent
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <math.h>

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>


class Point
{
private :
    GLfloat* vertices;

public:
    Point();

    void setCoords(GLfloat, GLfloat, GLfloat);
    GLfloat* getCoords();
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();

};


#endif /* POINT_H_ */
