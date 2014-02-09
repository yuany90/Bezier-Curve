#include <iostream>
#include <math.h>
#include "bezierSurface.h"
#include "bezierMath.h"
#include <GL\glut.h>
#define ALGORITHM 0

bezierSurface::bezierSurface(int uPoints, int vPoints, float **points[3], int precision, bool showControlPoints){
	this->uPoints = uPoints;
	this->vPoints = vPoints;
	controlPoints = points;
	if(precision < 2){
		precision = 2;
	}
	this->precision = precision;
	this->showControlPoints = showControlPoints;
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
    float red[] = {1.0, 0.0, 0.0};
	float white[] = {0.0, 0.0, 0.0};
	glColor3fv(red);
    for(int ui = 0; ui < precision; ui++) {
		glBegin(GL_LINES);
        for(int vi = 0; vi <= precision; vi++) {
            if(color) {
			//	glColor3fv(black);
			//	color = false;
			} else {
            //    glColor3fv(red);
            //    color = true;
            }
			float * p1 = curvePoints[ui][vi];
            float * p2 = curvePoints[ui+1][vi];
            glVertex3fv(p1);
            glVertex3fv(p2);
        }
        glEnd();
    }
	glColor3fv(white);
	if(showControlPoints){
		glBegin(GL_LINES);
		for(int m = 0; m <= uPoints; m++){
			for(int n=0; n<vPoints; n++){
				
				float * p1 = controlPoints[m][n];
				float * p2 = controlPoints[m][n+1];
				glVertex3fv(p1);
				glVertex3fv(p2);
				
			}
		}
		glEnd();
	}
	glPopMatrix();
}
