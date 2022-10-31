#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <math.h>

const double pi = 3.14159265358979323846264338327950;

double cylinder_vertical(double D, double r);
double cylinder_horizontal(double D, double l, double r);
double cube(double D, double l, double w = 1.0);
double cuboid(double D, double l, double w);

double cylinder_vertical(double D, double r){
	return D*pi*r*r;
}
double cylinder_horizontal(double D, double l, double r){
	return l*(r*r*acos((r-D)/r)-(r-D)*sqrt(2*r*D-D*D));
}
double cube(double D, double l){
	return cuboid(D,l,l);
}
double cuboid(double D, double l, double w){
	return l*w*D;
}

#endif
