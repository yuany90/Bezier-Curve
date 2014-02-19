Bezier-Curve
============

Algorithm
------------
This is a C++ program generated Bezier Curve and Bezier Surface in two different approaches.

- One approach implements "De Casteljau's algorithm". It is a recursive method to evaluate polynomials in Bernstein form or Bézier curves. Please see http://en.wikipedia.org/wiki/De_Casteljau's_algorithm.
- Another way is directly using the Bezier Curve formula. Please see http://en.wikipedia.org/wiki/B%C3%A9zier_curve

In this program, "#define ALGORITHM 0" in bezierCurve.cpp and bezierSurface.cpp decides which
algorithm to use.

User guide:
------------
- Input file sample for Bezier Surface: **surfaceDemo**. The first line "2 3" means it is a bezier surface and u = 2+1 = 3, v = 3+1 = 4.Then follows control points coordinates.
- Input file sample for Bezier Curve is like: **curveDemo**. Note that v = 1 for Bezier Curve. So first line should be "3 0".

Controls:
------------
- z, x: move camera
- 1,2,3,4,5,6,7,8,9: set precision of Bezier curve and Bezier Surface
- c: show control points and vice versa
