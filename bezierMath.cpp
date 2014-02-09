#include <iostream>
#include <math.h>

int factorial(int n){
        int r = 1;
        for(int i = n; i>0; i--){
                r *= i;
        }
        return r;
}

float bernstein(int i, int n, float t){
        float r = (float) factorial(n) / (float) (factorial(i) * factorial(n - i));
        r *= pow(t,i);
        r *= pow(1-t,n-i);
        return r;
}

float *deCasteljau(float **points, int degree, float t){
		float *pointsQ = new float[(degree + 1) * 3]; // same as pointsQ[numPoints + 1][3]
		int Qwidth = 3;
		for(int j = 0; j <= degree; j++){
			pointsQ[j*Qwidth + 0] = points[j][0];
			pointsQ[j*Qwidth + 1] = points[j][1];
			pointsQ[j*Qwidth + 2] = points[j][2];
		}
		for(int k = 1; k <= degree; k++){
			for(int j = 0; j<= degree - k; j++){
				pointsQ[j*Qwidth+0] = (1-t) * pointsQ[j*Qwidth+0] + t * pointsQ[(j+1)*Qwidth+0];
				pointsQ[j*Qwidth+1] = (1-t) * pointsQ[j*Qwidth+1] + t * pointsQ[(j+1)*Qwidth+1];
				pointsQ[j*Qwidth+2] = (1-t) * pointsQ[j*Qwidth+2] + t * pointsQ[(j+1)*Qwidth+2];
			}
		}
		float *result = new float[3];
		result[0] = pointsQ[0];
		result[1] = pointsQ[1];
		result[2] = pointsQ[2];
		delete[] pointsQ;
		return result;
}
