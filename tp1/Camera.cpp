/*
 * Camera.cpp
 *
 *  Created on: 24 sept. 2015
 *      Author: Vincent
 */



#include "Camera.h"
#include <cstdlib>
#include <windows.h>


Camera::Camera(const QVector3D &pos)
{
    _position = pos;
    _target = QVector3D(0,0,0);
    _phi = 0;
    _theta = 0;
    vectorsFromAngles();

    _speed = 1.0f;
    _sensivity = 0.05;
    _mousePositionX = 0.0f;
    _mousePositionY = 0.0f;
    //qDebug()<<"Init camera";
}

void Camera::setSpeed(GLfloat speed)
{
    _speed = speed;
}

void Camera::setSensivity(GLfloat sensivity)
{
    _sensivity = sensivity;
}

void Camera::setPosition(const QVector3D & position)
{
    _position = position;
    _target = _position + _forward;
}


void Camera::onMouseMotion(const QMouseEvent &event)
{
    _theta += (_mousePositionX - event.x())*_sensivity;
    _phi += (_mousePositionY - event.y())*_sensivity;
    _mousePositionX = event.x();
    _mousePositionY = event.y();
    /*
    _theta -= event.globalX()*_sensivity;
    _phi -= event.globalY()*_sensivity;
    */
    vectorsFromAngles();
}

void Camera::onKeyboard(const QKeyEvent &event)
{
    switch(event.key()){
        case KEY_Z:
            //_position.setX(_position.x() + _speed);
            //vectorsFromAngles();
            _position += _forward * _speed;
            //qDebug()<<"J'appuie sur Z";
            break;

        case KEY_S:
            // _position.setX(_position.x() - _speed);
             //vectorsFromAngles();
             _position -= _forward * _speed;
            // qDebug()<<"J'appuie sur S";
            break;

        case KEY_Q:
            // _position.setY(_position.y() - _speed);
             //vectorsFromAngles();
             _position += _left * _speed;
            // qDebug()<<"J'appuie sur Q";
            break;

        case KEY_D:
             //_position.setY(_position.y() + _speed);
             //vectorsFromAngles();
             _position -= _left * _speed;
            // qDebug()<<"J'appuie sur D";
            break;

        default:
         qDebug()<<"Touche invalide";
            break;
    }
}



void Camera::vectorsFromAngles()
{
    static const QVector3D up(0,0,1);
    if (_phi > 89)
        _phi = 89;
    else if (_phi < -89)
        _phi = -89;

    double r_temp = cos(_phi*M_PI/180);
    _forward.setZ(sin(_phi*M_PI/180));
    _forward.setX(r_temp*cos(_theta*M_PI/180));
    _forward.setY(r_temp*sin(_theta*M_PI/180));
    _left = up.crossProduct(up,_forward);
    _left.normalize();
    _target = _position + _forward;
}


void Camera::look(QMatrix4x4 &matrix)
{
    QVector3D up = QVector3D(0,0,1);
    vectorsFromAngles();
    matrix.lookAt(_position, _target, up);
}

Camera::~Camera()
{

}
