/*
 * Camera.h
 *
 *  Created on: 24 sept. 2015
 *      Author: Vincent
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

#include <QMouseEvent>
#include <QKeyEvent>

#include <stdint.h>

#define KEY_Q 81
#define KEY_Z 90
#define KEY_D 68
#define KEY_S 83


class Camera
{
public:
    Camera(const QVector3D & position = QVector3D(0,0,0));

    virtual void onMouseMotion(const QMouseEvent & event);
    virtual void onKeyboard(const QKeyEvent & event);

    virtual void setSpeed(GLfloat speed);
    virtual void setSensivity(GLfloat sensivity);

    virtual void setPosition(const QVector3D & position);

    virtual void look(QMatrix4x4 &matrix);

    virtual ~Camera();

protected:
    GLfloat _speed;
    GLfloat _sensivity;

    QVector3D _position;
    QVector3D _target;
    QVector3D _forward;
    QVector3D _left;
    GLfloat _theta;
    GLfloat _phi;

    GLfloat _mousePositionX;
    GLfloat _mousePositionY;

    void vectorsFromAngles();
};


#endif /* Camera_H_ */
