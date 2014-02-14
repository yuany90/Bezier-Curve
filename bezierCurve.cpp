#include <iostream>
#include <math.h>
#include "bezierCurve.h"
#include "bezierMath.h"
#include <GL\glut.h>
#define ALGORITHM 0
using namespace std;

bezierCurve::bezierCurve(int numPoints, float *points[3]):bezier(){
	this->numPoints = numPoints;
	controlPoints = points;
	if(precision < 2){
		precision = 2;
	}
}

void bezierCurve::setShowPoints(bool showControlPoints){
	this->showControlPoints = showControlPoints;
}

void bezierCurve::calCurve(){
	std::cout<< "newLine" << endl;
	for(int j=0; j<= numPoints;j++){
				std:cout<<controlPoints[j][0]<<','<<controlPoints[j][1]<<','<<controlPoints[j][2]<<endl;
	}
	curvePoints = new float*[precision+1];
	if(ALGORITHM == 0){
		// de Casteljau's Algorithm
		// Input: array P[0:n] of n+1 points and real number u in [0,1]
		// Output: point on curve, C(u)
		// Working: point array Q[0:n]
		// for i := 0 to n do
		// Q[i] := P[i]; // save input
		// for k := 1 to n do
		// for i := 0 to n - k do
        // Q[i] := (1 - u)Q[i] + u Q[i + 1]; 
		// return Q[0];
        for(int i = 0; i <= precision; i++) {
			float u = float(i)/float(precision);
			/*
			float *pointsQ = new float[(numPoints + 1) * 3]; // same as pointsQ[numPoints + 1][3]
			int Qwidth = 3;
			for(int j = 0; j <= numPoints; j++){
				pointsQ[j*Qwidth + 0] = controlPoints[j][0];
				pointsQ[j*Qwidth + 1] = controlPoints[j][1];
				pointsQ[j*Qwidth + 2] = controlPoints[j][2];
			}
			for(int k = 1; k <= numPoints; k++){
				for(int j = 0; j<= numPoints - k; j++){
					pointsQ[j*Qwidth+0] = (1-u) * pointsQ[j*Qwidth+0] + u * pointsQ[(j+1)*Qwidth+0];
					pointsQ[j*Qwidth+1] = (1-u) * pointsQ[j*Qwidth+1] + u * pointsQ[(j+1)*Qwidth+1];
					pointsQ[j*Qwidth+2] = (1-u) * pointsQ[j*Qwidth+2] + u * pointsQ[(j+1)*Qwidth+2];
				}
			}
			curvePoints[i] = new float[3];
			*/
			curvePoints[i] = deCasteljau(controlPoints, numPoints, u);
		}
	} else {
		for(int i = 0; i <= precision; i++){
			float u = float(i)/float(precision);
			float *point = new float[3];
			point[0] = 0;
			point[1] = 0;
			point[2] = 0;
			for(int m = 0; m <= numPoints; m++){
				float bm = bernstein(m, numPoints, u);
				point[0] += bm * controlPoints[m][0];
				point[1] += bm * controlPoints[m][1];
				point[2] += bm * controlPoints[m][2];
			}
			curvePoints[i] = point;
		}
		// by formula of Bezier curve

	}
}

void bezierCurve::draw(){
	std::cout<<"Curve Points"<<endl;
	this->calCurve();
	float black[] = {0.0, 0.0, 0.0};
    float red[] = {1.0, 0.0, 0.0};
	glPushMatrix();
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	glColor3fv(black);
	for(int i = 0; i<=precision; i++){
		GLfloat * v = curvePoints[i];
		std:cout<<curvePoints[i][0]<<','<<curvePoints[i][1]<<','<<curvePoints[i][2]<<endl;
		glVertex3fv(v);
	}
	glEnd();
	glColor3fv(red);
	if(showControlPoints){
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i<=numPoints; i++){
			GLfloat * v = controlPoints[i];
			glVertex3fv(v);
		}
		glEnd();
	}
	glPopMatrix();
}

