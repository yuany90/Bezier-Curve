#ifndef _BEZIERSURFACE_H_
#define _BEZIERSURFACE_H_
#include "bezier.h"

class bezierSurface : public bezier{
private:
	int uPoints;
	int vPoints;
	float ***controlPoints;
	float ***curvePoints;
	bool showControlPoints;
	void bezierSurface::calSurface();
public:
	bezierSurface(int uPoints, int vPoints, float **points[3], int precision = 20, bool showControlPoints = true);
	void bezierSurface::setShowPoints(bool showControlPoints);
	virtual void draw();
    ~bezierSurface();
};
#endif
