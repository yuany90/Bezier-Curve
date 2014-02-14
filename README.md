Bezier-Curve
============

This is a C++ program that generated Bezier Curve and Bezier Surface in two different approaches.


It is a recursive method to evaluate polynomials in Bernstein form or Bézier curves.

http://en.wikipedia.org/wiki/De_Casteljau's_algorithm.

Another way is directly using the Bezier Curve formula

http://en.wikipedia.org/wiki/B%C3%A9zier_curve

In this program, "#define ALGORITHM 0" in bezierCurve.cpp and bezierSurface.cpp decides which
algorithm to use.

User guide:

Input file sample for Bezier Surface:

2 3
1.0 1.0 1.0
2.0 1.2 1.0
3.0 0.8 1.0
4.0 1.0 1.0
1.0 1.0 2.0
2.0 5.0 2.0
3.0 0.8 2.0
4.0 1.0 2.0
1.0 1.0 3.0
2.0 0.8 3.0
3.0 1.2 3.0
4.0 1.0 3.0

The line "2 3" means it is a bezier surface and u = 2+1 = 3, v = 3+1 = 4.
Then follows control points coordinates.
Note v = 1 for Bezier Curve. So input file sample for Bezier Curve is like
3 0
1.0 1.0 1.0
2.0 3.0 1.0
3.0 0.8 1.0
4.0 1.0 1.0

Controls:
z, x: move camera
1,2,3,4,5,6,7,8,9: set precision of Bezier curve and Bezier Surface
c: show control points or not
