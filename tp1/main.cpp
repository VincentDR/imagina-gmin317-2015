/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

#include <iostream>
#include "Point.h"
#include "Face.h"
#include "Camera.h"



//Pour l'exo1, la dimension est le nombre de pixel par côté
//Le reste me sert pour déterminer les tailles de mes tableaux, ecartsPoints pour représenter l'écart entre deux points (eh oui)
int dimension = 5;
int nbSommets = dimension * dimension;
int nbFaces = sqrt(nbSommets - 1) * sqrt(nbSommets - 1) * 2;
Face * faces;
GLfloat ecartPoints = 1.0f;

Camera * cam;

QMouseEvent *souris;
QKeyEvent *clavier;

//! [1]
class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();
    void keyPressEvent(QKeyEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void heightMap();
    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
{
}
//! [1]
void exo1(){
    //Ajouts
    //Tableau de Points (classe perso) permettant par la suite de remplir un tableau
    Point * points = (Point *) malloc(sizeof(Point) * nbSommets);

    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    GLfloat z = 0.0f;
    for(int i = 0; i < nbSommets; i++){
        if(i%(int)sqrt(nbSommets) == 0 && i!=0){
            x = 0.0f;
            y -= ecartPoints;
        }
        GLfloat r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        z = r/100;

        points[i] = Point();
        points[i].setCoords(x,y,z);
        //qDebug()<<"Point "<<i<<" : "<<x<<" "<<y<<" "<<z;

        x += ecartPoints;

    }


    //Tableau de triangle
    faces = (Face *)malloc(sizeof(Face) * nbFaces);
    for(int i = 0; i < nbFaces; i++){
        faces[i] = Face(3);
    }
    //Ces indices représentent chaque carré que l'on va traiter à la suite
    int un = 0;
    int deux = 1;
    int trois = (int)sqrt(nbSommets);
    int quatre = trois + 1;

    //On ne traite que les carrés, donc deux triangles à la fois
    for(int i = 0; i < ((int)sqrt(nbSommets) - 1)*((int)sqrt(nbSommets) - 1); i++){
        if(i%((int)sqrt(nbSommets) - 1) == 0 && i!=0){//On descend d'une ligne
            un++;
            deux++;
            trois++;
            quatre++;
        }

        faces[i*2].setSommetFace(0, points[un]);
        faces[i*2].setSommetFace(1, points[deux]);
        faces[i*2].setSommetFace(2, points[trois]);
        faces[i*2].setCoords();//Pour récuperer un GLfloat*
        //qDebug()<<"Triangle "<<i*2<<" : "<<un<<" "<<deux<<" "<<trois<<" "<<quatre;
        faces[i*2 + 1].setSommetFace(0, points[deux]);
        faces[i*2 + 1].setSommetFace(1, points[quatre]);
        faces[i*2 + 1].setSommetFace(2, points[trois]);
        faces[i*2 + 1].setCoords();

        un++;
        deux++;
        trois++;
        quatre++;
    }
    //Fin Ajouts
}


//! [2]
int main(int argc, char **argv)
{

    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    cam = new Camera({-6,0,2});

    //exo1();

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.heightMap();

    window.setAnimating(true);

    return app.exec();
}
//! [2]


//! [3]
static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";
//! [3]

//! [4]
GLuint TriangleWindow::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}
//! [4]

//Ajouts
//TEST EVENTS
void TriangleWindow::keyPressEvent(QKeyEvent * event){
    cam->onKeyboard(*event);
}
void TriangleWindow::mouseMoveEvent(QMouseEvent * event){
    cam->onMouseMotion(*event);
}


//TEST MAP
void TriangleWindow::heightMap(){
    QImage map = QImage("heightmap-1.png");

    int dimX = map.width();
    int dimZ = map.height();
    int tailleMap = dimZ * dimX;


    Point * points = (Point *) malloc(sizeof(Point) * tailleMap);
    ecartPoints = 5.0f;
    for(int z = 0; z < dimZ; z++)
    {
        for(int x = 0; x < dimX; x++)
        {
            QRgb color = map.pixel(x, z);

            GLfloat tempX = (ecartPoints * x / dimX) - ecartPoints / 2;
            GLfloat tempZ =  2.0 * qGray(color) / 255;
            GLfloat tempY = (ecartPoints * z / dimZ) - ecartPoints / 2;
            //qDebug()<<"Je suis à "<<z + dimZ * x<<" et qGray(color) "<<qGray(color);
            points[z + dimZ * x] = Point();
            points[z + dimZ * x].setCoords(tempX, tempY, tempZ);
           }
    }

    //Tableau de triangle
    nbSommets = tailleMap;
    nbFaces = sqrt(nbSommets - 1) * sqrt(nbSommets - 1) * 2;

    //qDebug()<<"Le nombre de face est de "<<nbFaces;


    faces = (Face *)malloc(sizeof(Face) * nbFaces);
    for(int i = 0; i < nbFaces; i++){
        faces[i] = Face(3);
    }

    int un = 0;
    int deux = 1;
    int trois = (int)sqrt(nbSommets);
    int quatre = trois + 1;

    //On ne traite que les carrés, donc deux triangles à la fois
    for(int i = 0; i < ((int)sqrt(nbSommets) - 1)*((int)sqrt(nbSommets) - 1); i++){
        if(i%((int)sqrt(nbSommets) - 1) == 0 && i!=0){//On descend d'une ligne
            un++;
            deux++;
            trois++;
            quatre++;
        }

        faces[i*2].setSommetFace(0, points[un]);
        faces[i*2].setSommetFace(1, points[deux]);
        faces[i*2].setSommetFace(2, points[trois]);
        faces[i*2].setCoords();//Pour récuperer un GLfloat*
        //qDebug()<<"Triangle "<<i*2<<" : "<<un<<" "<<deux<<" "<<trois<<" "<<quatre;
        faces[i*2 + 1].setSommetFace(0, points[deux]);
        faces[i*2 + 1].setSommetFace(1, points[quatre]);
        faces[i*2 + 1].setSommetFace(2, points[trois]);
        faces[i*2 + 1].setCoords();

        un++;
        deux++;
        trois++;
        quatre++;
    }
}//Fin Ajouts

//! [5]
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    //matrix.translate(0, 0, -2);
   // matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    cam->look(matrix);

    m_program->setUniformValue(m_matrixUniform, matrix);

/*
    GLfloat vertices[] = {
        0.707f, 0.0f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f
    };*/

    //On récupére le min et max des hauteurs pour la montagne
    GLfloat min = 30000.0f;
    GLfloat max = -30000.0f;
    for(int i = 0 ; i < nbFaces; i++){
        if(faces[i].moyCoord(2)> max){
            max = faces[i].moyCoord(2);
        }else if(faces[i].moyCoord(2)< min){
            min = faces[i].moyCoord(2);
        }
    }


    for(int i = 0 ; i < nbFaces; i++){
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, faces[i].getCoords());
        GLfloat col = faces[i].moyCoord(2) / max;
        GLfloat colors[] = {
                col, col, col,
                col, col, col,
                col, col, col
            };
        glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }

    m_program->release();

    ++m_frame;
}
//! [5]
