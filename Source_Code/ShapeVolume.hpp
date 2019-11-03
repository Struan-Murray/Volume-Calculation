#ifndef SHAPEVOLUME_HPP
#define SHAPEVOLUME_HPP

#define PI 3.1415926535

double coneVolume(double height, double width, double h);

double cylinderVolume(double height, double width, double h);
double cylinder_SphericalCapVolume(double height, double width, double sphereH, double h);
double cylinder_ConeVolume(double height, double width, double coneH, double h);

double rectangularVolume(double height, double width, double breadth, double h);

double sphericalCapVolume(double height, double width, double h);


double coneVolume(double height, double width, double h)
{
	double w = h / height * width;
	return PI * h * (w * w) / 12.0;
}


double cylinderVolume(double height, double width, double h)//G
{
	return PI * width * width * h / 4.0;
}
double cylinder_SphericalCapVolume(double height, double width, double sphereH, double h)//G
{
	if(h < sphereH)
	{
		return sphericalCapVolume(sphereH, width, h);
	}
	else
	{
		return cylinderVolume(height - sphereH, width, h - sphereH) + sphericalCapVolume(sphereH, width, sphereH);
	}
}
double cylinder_ConeVolume(double height, double width, double coneH, double h)
{
	if(h < coneH)
	{
		return coneVolume(coneH, width, h);
	}
	else
	{
		return cylinderVolume(height - coneH, width, h - coneH) + coneVolume(coneH, width, coneH);
	}
}

double rectangularVolume(double height, double width, double breadth, double h)//G
{
	return breadth * height * h;
}

double sphericalCapVolume(double height, double width, double h)//G
{
	double r =(width*width/4.0 + height*height)/(2*height);
	return PI*h*h*(3.0*r-h)/3.0;
}



#endif
