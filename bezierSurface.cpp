#include <iostream>
#include <math.h>
#include "bezierSurface.h"
#include "bezierMath.h"
#include <GL\glut.h>
#define ALGORITHM 0

bezierSurface::bezierSurface(int uPoints, int vPoints, float **points[3]):bezier(){
	this->uPoints = uPoints;
	this->vPoints = vPoints;
	controlPoints = points;
}

void bezierSurface::setShowPoints(bool showControlPoints){
	this->showControlPoints = showControlPoints;
}

void bezierSurface::calSurface(){
	curvePoints = new float**[precision+1];
	for (int i = 0; i <= precision; i++){
		curvePoints[i] = new float*[precision+1];
	}
	if(ALGORITHM == 0){
		// de Casteljau's Algorithm
		for(int ui = 0; ui <= precision; ui++) {
			float u = float(ui)/float(precision);
			for(int vi = 0; vi <= precision; vi++) {
				float v = float(vi)/float(precision);
				float **qPoints = new float*[uPoints+1];
				for(int i=0; i <= uPoints; i++){
					qPoints[i] = deCasteljau(controlPoints[i], vPoints, v);
				}
				curvePoints[ui][vi] = deCasteljau(qPoints, uPoints, u);
			}
		}
	} else {
		// by formula of Bezier curve
		for(int ui = 0; ui <= precision; ui++){
			float u = float(ui)/float(precision);
			for(int vi = 0; vi <= precision; vi++){
				float v = float(vi)/float(precision);
				float *point = new float[3];
				point[0] = 0;
				point[1] = 0;
				point[2] = 0;
				for(int m = 0; m <= uPoints; m++){
					for(int n =0; n<= vPoints; n++){
						float bm = bernstein(m, uPoints, u);
						float bn = bernstein(n, vPoints, v);
						float b = bm * bn;
						point[0] += b * controlPoints[m][n][0];
						point[1] += b * controlPoints[m][n][1];
						point[2] += b * controlPoints[m][n][2];
					}
				}
				curvePoints[ui][vi] = point;
			}
		}
	}
}

void bezierSurface::draw(){
	this->calSurface();
	glPushMatrix();
    bool color = false;
    float black[] = {0.0, 0.0, 0.0};
    float white[] = {1.0, 1.0, 1.0};
	float red[] = {1.0, 0.0, 0.0};
	glColor3fv(black);
    for(int ui = 0; ui < precision; ui++) {
		glBegin(GL_TRIANGLE_STRIP);
        for(int vi = 0; vi <= precision; vi++) {
            if(color) {
				glColor3fv(white);
			} else {
                glColor3fv(black);
            }
			float * p1 = curvePoints[ui][vi];
            float * p2 = curvePoints[ui+1][vi];
            glVertex3fv(p1);
            glVertex3fv(p2);
			color = !color;
        }
		if(precision%2 == 1){
			color = !color;
		}
        glEnd();
    }
	glLineWidth(2.0);
	glColor3fv(red);
	if(showControlPoints){
		for(int m = 0; m <= uPoints; m++){
			glBegin(GL_LINE_STRIP);
			for(int n=0; n<=vPoints; n++){
				float * p = controlPoints[m][n];
				glVertex3fv(p);	
			}
			glEnd();
		}
		for(int n=0; n<=vPoints; n++){
			glBegin(GL_LINE_STRIP);
			for(int m = 0; m <= uPoints; m++){
				float * p = controlPoints[m][n];
				glVertex3fv(p);	
			}
			glEnd();
		}
	}
	glPopMatrix();
}
