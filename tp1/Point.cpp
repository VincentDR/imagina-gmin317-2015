/*
 * Point.cpp
 *
 *  Created on: 22 sept. 2015
 *      Author: Vincent
 */


#include "Point.h"

#include <windows.h>

Point::Point(){
    vertices = (GLfloat *)malloc(sizeof(GLfloat) * 3);
}

void Point::setCoords(GLfloat x, GLfloat y, GLfloat z){
    vertices[0] = x;
    vertices[1] = y;
    vertices[2] = z;
}

GLfloat * Point::getCoords(){
    return vertices;
}

GLfloat Point::getX(){
    return vertices[0];
}

GLfloat Point::getY(){
    return vertices[1];
}

GLfloat Point::getZ(){
    return vertices[2];
}



