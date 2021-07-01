#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <math.h>

const double pi = 3.14159265358979323846264338327950;

enum Shape {CYLINDER_VERTICAL, CYLINDER_HORIZONTAL, CUBOID, CUBE};

void shape_options(){
	std::cout << "Vertical Cylinder   - " << CYLINDER_VERTICAL << "\n";
	std::cout << "Horizontal Cylinder - " << CYLINDER_HORIZONTAL << "\n";
	std::cout << "Cuboid              - " << CUBOID << "\n";
	std::cout << "Cube                - " << CUBE << "\n";
}

// l, w, h, r, D

double cylinder_vertical(double D, double l, double r);
double cylinder_horizontal(double D, double l, double r);
double cube(double D, double l, double w = 1.0);
double cuboid(double D, double l, double w);

double cylinder_vertical(double D, double l, double r){
	return D*pi*r*r;
}
double cylinder_horizontal(double D, double l, double r){
	return l*(r*r*acos((r-D)/r)-(r-D)*sqrt(2*r*D-D*D));
}
double cube(double D, double l, double w){
	return cuboid(D,l,w);
}
double cuboid(double D, double l, double w){
	return l*w*D;
}

#endif
