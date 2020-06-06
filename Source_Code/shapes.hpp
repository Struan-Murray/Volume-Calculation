#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <math.h>

const double pi = 3.14159265358979323846264338327950;

enum Shape {CYLINDER_VERTICAL, CYLINDER_HORIZONTAL, CUBOID_VERTICAL, CUBOID_HORIZONTAL};

void shape_options(){
	std::cout << "Vertical Cylinder   - " << CYLINDER_VERTICAL << "\n";
	std::cout << "Horizontal Cylinder - " << CYLINDER_HORIZONTAL << "\n";
	std::cout << "Vertical Cuboid     - " << CUBOID_VERTICAL << "\n";
	std::cout << "Horizontal Cuboid   - " << CUBOID_HORIZONTAL << "\n";
}

double cylinder_vertical(double l, double r, double d){
	return d*pi*r*r;
}
double cylinder_horizontal(double l, double r, double d){
	return l*(r*r*acos((r-d)/r)-(r-d)*sqrt(2*r*d-d*d));
}

double cuboid_vertical(double l, double w, double d){
	return l*w*d;
}
double cuboid_horizontal(double l, double w, double d){
	return cuboid_vertical(l,w,d);
}

#endif
