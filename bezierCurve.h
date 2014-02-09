#ifndef _BEZIERCURVE_H_
#define _BEZIERCURVE_H_
#include "bezier.h"

class bezierCurve : public bezier{
private:
	int numPoints;
	float **controlPoints;
	float **curvePoints;
	int precision;
	bool showControlPoints;
	void bezierCurve::calCurve();
public:
	bezierCurve(int numPoints, float *points[3], int precision = 20, bool showControlPoints = true);
	void bezierCurve::setShowPoints(bool showControlPoints);
	virtual void draw();
    ~bezierCurve();
};
#endif
