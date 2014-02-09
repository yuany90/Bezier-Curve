#include <iostream>
#include <fstream>
#include "bezier.h"
#include "bezierCurve.h"
#include "bezierSurface.h"

#define LINE_LENGTH 200
using namespace std;

bezier *readBezierFile(char *filename)
{
        ifstream fin;
		fin.open(filename, ios::in);
		char s[LINE_LENGTH];
		fin.getline(s, LINE_LENGTH);
		int uPoints;
		int vPoints;
		sscanf_s(s, "%d %d", &uPoints, &vPoints);
		int i = 0;
		int length = vPoints>0 ? (uPoints+1)*(vPoints+1) : uPoints+1;
		float **points = new float*[uPoints + 1];
		bezier *bc;
		while(fin.getline(s, LINE_LENGTH)){
			float *point = new float[3];
			if (s[0] == '#') continue; //comment line
			sscanf_s(s, "%f %f %f", &point[0], &point[1], &point[2]);
		//	std::cout<<point[0]<<','<<point[1]<<','<<point[2]<<endl;
			points[i++] = point;
		}
		if(i < length){
			std::cout << "Need more points" << endl;
			exit(0);
		}
		if(vPoints == 0){
		//	uPoints = i-1;		
		//	std::cout<< "newLine" << endl;
			bc = new bezierCurve(uPoints, points);
		} else {
			float ***points2d;
			points2d = new float **[uPoints];
			for(int m = 0; m <= uPoints; m++){
				float **points1d = new float*[vPoints];
				int width = vPoints+1;
				for(int n = 0; n <= vPoints; n++){
					points1d[n] = points[m*width + n];
					std::cout<<points[m*width + n][0]<<','<<points[m*width + n][1]<<','<<points[m*width + n][2]<<endl;
				}
				points2d[m] = points1d;
			}
			bc = new bezierSurface(uPoints, vPoints, points2d);
		}
		return bc;
}
