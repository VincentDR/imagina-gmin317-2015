/*
 * Face.cpp
 *
 *  Created on: 22 sept. 2015
 *      Author: Vincent
 */



#include "Face.h"
#include <cstdlib>
#include <windows.h>




	Face::Face(){
		nbSommets = 0;
		sommets = NULL;
	}

	Face::Face(int n){
		nbSommets = n;
		sommets =  (Point*)malloc(n * sizeof(Point));
	}

	Face::Face(int n, Point * ps){
		nbSommets = 0;
		sommets = ps;
	}

	int Face::getNbSommets(){
		return nbSommets;
	}
	Point Face::getSommetFace(int i){
		return sommets[i];
	}

	Point* Face::getSommetsFace(){
		return sommets;
	}

	void Face::setSommetFace(int i, Point& p){
		sommets[i] = p;
	}
	void Face::setSommetsFace(Point * p){
		sommets = p;
	}


    void Face::setCoords(GLfloat* s){
        coords = (GLfloat *)malloc(sizeof(GLfloat) * 9);
        for(int i = 0; i < 9; i++){
            coords[i] = s[i];
        }
    }

    void Face::setCoords(){
        coords = (GLfloat *)malloc(sizeof(GLfloat) * 9);
        for(int i = 0; i < 3; i++){
            coords[i*3] = sommets[i].getX();
            coords[i*3 + 1] = sommets[i].getY();
            coords[i*3 + 2] = sommets[i].getZ();
        }
    }

    GLfloat* Face::getCoords(){
        return coords;
    }

    GLfloat Face::moyCoord(int x){
        if(x == 0){
            return (coords[0]+coords[3]+coords[6]) /3;
        }
        else if(x == 1){
            return (coords[1]+coords[4]+coords[7]) /3;
        }
        else if(x == 2){
            return (coords[2]+coords[5]+coords[8]) /3;
        }
    }

