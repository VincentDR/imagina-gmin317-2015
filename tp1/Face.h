/*
 * Face.h
 *
 *  Created on: 22 sept. 2015
 *      Author: Vincent
 */

#include "Point.h"

#ifndef FACE_H_
#define FACE_H_



class Face
{
	public:
		Face();
		Face(int);
		Face(int,Point*);
		Face(const Face&);

		int getNbSommets();

		Point getSommetFace(int);
		Point* getSommetsFace();
        GLfloat* getCoords();

		void setSommetFace(int, Point&);
		void setSommetsFace(Point *);
        void setCoords(GLfloat*);
        void setCoords();

        GLfloat moyCoord(int);//int 0 pour x, 1 pour y...
	private:
		int nbSommets;
		Point * sommets;
        GLfloat * coords;
};



#endif /* FACE_H_ */
