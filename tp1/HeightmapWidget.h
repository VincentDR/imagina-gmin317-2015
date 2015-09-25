/*
 * HeightmapWidget.h
 *
 *  Created on: 24 sept. 2015
 *      Author: Vincent
 */

#ifndef HEIGHTMAPWIDGET_H_
#define HEIGHTMAPWIDGET_H_

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <QRgb>

#include <QMouseEvent>
#include <QKeyEvent>

#include <stdint.h>

class HeightmapWidget
{

public:
    HeightmapWidget(QWidget * parent = 0);
    ~HeightmapWidget();

    void initializeGL();
    void paintGL();
    void resizeGL();

private:
    QVector<QVector3D>  m_vertices;
    int vertices_by_x;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_z;
};

#endif /* HeightmapWidget_H_ */
