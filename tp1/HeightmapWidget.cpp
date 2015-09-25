/*
 * HeightmapWidget.cpp
 *
 *  Created on: 24 sept. 2015
 *      Author: Vincent
 */



#include "HeightmapWidget.h"


void HeightmapWidget::initializeGL()
{
    QImage img = QImage(QString(":/heightmap-1.png"));
    vertices_by_x = img.width();
    vertices_by_z = img.height();
    quads_by_x = vertices_by_x - 1;
    quads_by_z = vertices_by_z - 1;
    QVector3D vertice;

    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int x = 0; x < vertices_by_x; ++x)
        {
                   QRgb color = img.pixel(x, z);
                   vertice.setX((240 * x / vertices_by_x) - 240 / 2);
                   vertice.setY(2.0 * qGray(color) / 255);
                   vertice.setZ((240 * z / vertices_by_z) - 240 / 2);

                               m_vertices.push_back(vertice);
                           }
                       }
}
