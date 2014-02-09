#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "bezierCurve.h"

#define STREAM_SIZE 256
using namespace std;

bezier * readFile(char * filename)
{
        ifstream input(filename);
        char line[STREAM_SIZE];
        int numbezier_curves;
        if(input) {
                input.getline(line, STREAM_SIZE);
                sscanf(line, "%d", &numbezier_curves);
        }

        std::vector<bezierCurve *> * rbezier_curves = new std::vector<bezierCurve *>();

        for(int bezier_curveCounter = 0; bezier_curveCounter < numbezier_curves; bezier_curveCounter++) {
                input.getline(line, STREAM_SIZE);
                int uDegree, vDegree;
                sscanf(line, "%d %d", &uDegree, &vDegree);

                const int MATRIX_SIZE = 4;
                float * transform = new float[MATRIX_SIZE * MATRIX_SIZE];
                for(int transformCounter = 0; transformCounter < MATRIX_SIZE; transformCounter++) {
                        input.getline(line, STREAM_SIZE);
                        sscanf(line, "%f %f %f %f", &(transform[transformCounter]),
                                                                                &(transform[1 * MATRIX_SIZE + transformCounter]),
                                                                                &(transform[2 * MATRIX_SIZE + transformCounter]),
                                                                                &(transform[3 * MATRIX_SIZE + transformCounter]));
                }

                float ** coordinates = NULL;
                if(0 == vDegree) {
                        coordinates = new float*[uDegree + 1];
                        for(int pointCounter = 0; pointCounter < (uDegree + 1); pointCounter++) {
                                input.getline(line, STREAM_SIZE);
                                float * coordinate = new float[3];
                                sscanf(line, "%f %f %f", &(coordinate[0]),
                                                                                 &(coordinate[1]),
                                                                                 &(coordinate[2]));
                                coordinates[pointCounter] = coordinate;
                        }

                }
                else {
                        coordinates = new float*[vDegree + 1];
                        for(int i = 0; i <= vDegree; i++) {
                                coordinates[i] = new float[3*(uDegree+1)];
                        }
                        /* Just get them in here so we can start working */

                        for(int row = 0; row <= vDegree; row++) {
                                std::vector<std::string> strs;
                                input.getline(line, STREAM_SIZE);
                                boost::split(strs, line, boost::is_space());
                                for(int i = 0; i < 3*(uDegree+1); i++) {
                                        string d = strs.at(i);
                                        sscanf(d.c_str(),"%f",&(coordinates[row][i]));
                                }
                        }
                        /*Now my floats are upside down. Don't you hate it when your floats are upside down? */
                }
                bezierCurve * c = new bezierCurve(uDegree, vDegree, transform, coordinates, 1);
                rbezier_curves->push_back(c);
        }
        return rbezier_curves;
}

