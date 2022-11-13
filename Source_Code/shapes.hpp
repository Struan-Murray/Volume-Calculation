#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <math.h>

const double pi = 3.14159265358979323846264338327950;

double cylinder_vertical(double D, double r){
	return D*pi*r*r;
}
double cylinder_horizontal(double D, double l, double r){
	return l*(r*r*acos((r-D)/r)-(r-D)*sqrt(2*r*D-D*D));
}
double cuboid(double D, double l, double w){
	return l*w*D;
}

/* ---------- Conic Vat ----------
 * Depth (D) of tabling point <<<<<
 * Diameter (d) of conic vat
 * Height (h) of conic vat
 */
double cone(double D, double d, double h){
	d=D/h*d;
	return pi*d*d/4.0/3.0*D;
}

/* ---------- Spherical Vat ----------
 * Depth (D) of tabling point <<<<<
 * Radius (r) of sphere
 */
double sphere(double D, double r) 
{
	if(D>2*r){D=2.0*r;}
	return (pi*D*D*r)-(pi*D*D*D/3.0);
}

/* ---------- Spherical Cap Vat ----------
 * Depth (D) of tabling point <<<<<
 * Height (h) of spherical cap
 * Radius (r) of spherical cap
 * Radius (sr) of sphere (calculated)
 */
double spherical_cap(double D, double h, double r) 
{
	double sr =(r*r + h*h)/(2.0*h);
	if(D>sr){D=sr;}
	return sphere(D,sr);
}

#endif