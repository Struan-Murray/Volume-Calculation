#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <string>

#include "PrintIntro.h"

#define PI 3.1415926535
#define UNIT "mm"
#define UNITBASE 1000.0

double cylinderSphericalCapVolume(double, double, double, double, double);
double cylinderVolume(double, double);
double rectangularVolume(double, double, double);

void printVatOptions();
std::string printFormattedTime(std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point);

enum Vat_Shapes{BEGIN = 0, CYLINDER, CYLINDERSPHERICALCAP, RECTANGLE, SQUARE, END};

int main()
{
	std::chrono::high_resolution_clock::time_point time_start = std::chrono::high_resolution_clock::now(), time_end = std::chrono::high_resolution_clock::now();

	printIntro("Vat volume calculator",2018,12,12,0);
	std::cout << "Instructions, and the latest version of this program should be available from: " << std::endl;
	std::cout << "https://github.com/Struan-Murray/Volume-Calculation" << std::endl << std::endl;

	std::string companyName{"VatCo"}, vatID{"0"}, vatTitle{"VatCo-0"}, fileName{"VatCo-0.csv"}, vatType{"Magic? Report bug please."};
	std::ofstream vatFile;
	int_fast16_t introLines{0};
	double step{0.0}, depth{0.0}, width{0.0}, breadth{0.0}, side{0.0}, radius{0.0}, bottomH{0.0}, bottomV{0.0};

	std::cout << "Vat Company: ";
	getline(std::cin, companyName); // Allows company names with spaces to be used.
	std::cout << "Vat ID: ";
	getline(std::cin, vatID); // Allows vat ID's with spaces to be used.

	vatTitle = companyName + "-" + vatID; // Title of vat to be processed.
	fileName = vatTitle + ".csv"; // Name of file.

	vatFile.open(fileName, std::ios::trunc); // Open file and truncate contents (erases previous content).

	if(vatFile.is_open())
	{
		vatFile << "Vat:," << vatTitle; introLines++;
		vatFile << std::endl; introLines++;
		vatFile << std::endl; introLines++;

		std::cout << fileName << " succesfully created and open.\n" << std::endl;
	}
	else
	{
		std::cout << "STRUAN: UNABLE TO OPEN FILE. Is the file locked by the OS? (Open) Does it have an illegal character? (?,\\,\" etc)\n";
		perror("OS");
		return -1;
	}

	int vat; // For selecting vat type.
	char ignoreError[20]; // Used to store values for user input re incompatibilities.

	printVatOptions();
	std::cout << std::endl;

	std::cout << "Vat type: ";
	std::cin >> vat;

	vatFile << "Type:,";

	bool needDepth{false}, needWidth{false}, needBreadth{false}, needSide{false}, needRadius{false}, needBottomHV{false};
	bool checkRadius{false};

	switch(vat)
	{
		case CYLINDER:
			vatType = "Flat Based Cylinder";
			needDepth = true;
			needWidth = true;
			break;
		case CYLINDERSPHERICALCAP:
			vatType = "Spherical Cap Based Vat";
			needDepth = true;
			needWidth = true;
			needRadius = true;
			checkRadius = true;
			needBottomHV = true;
			break;
		case RECTANGLE:
			vatType = "Flat Based Rectangle";
			needDepth = true;
			needWidth = true;
			needBreadth = true;
			break;
		case SQUARE:
			vatType = "Flat Based Rectangle";
			needDepth = true;
			needWidth = true;
			break;
		default:
			std::cout << "Incompatible type";
			return -5;
	}

	vatFile << vatType << std::endl; introLines++;
	vatFile << std::endl; introLines++;
	vatFile << "Description,Value,Unit" << std::endl; introLines++;

	if(needDepth)
	{
		std::cout << "Enter vat depth (mm): ";
		std::cin >> depth;
		depth = abs(depth)/1000.0;
		vatFile << "Depth:," << depth*1000.0 << ",mm" << std::endl; introLines++;
	}

	if(needWidth)
	{
		std::cout << "Enter vat width (mm): ";
		std::cin >> width;
		width = abs(width)/1000.0;
		vatFile << "Width:," << width*1000.0 << ",mm" << std::endl; introLines++;
	}

	if(needBreadth)
	{
		std::cout << "Enter vat breadth (mm): ";
		std::cin >> breadth;
		breadth = abs(breadth)/1000.0;
		vatFile << "Breadth:," << breadth*1000.0 << ",mm" << std::endl; introLines++;
	}

	if(needSide)
	{
		std::cout << "Enter vat side (mm): ";
		std::cin >> side;
		side = abs(side)/1000.0;
		vatFile << "Breadth:," << side*1000.0 << ",mm" << std::endl; introLines++;
	}

	if(needRadius)
	{
		std::cout << "Enter vat bottom radius (mm): ";
		std::cin >> radius;
		radius = abs(radius)/1000.0;
		vatFile << "Bottom Radius:," << radius*1000.0 << ",mm" << std::endl; introLines++;
	}

	if(needBottomHV)
	{
		bottomH = radius-sqrt(radius*radius-((width/2)*(width/2)));
		bottomV = (PI * bottomH * bottomH / 3) * (3 * radius - bottomH);
		vatFile << "Base Height:," << bottomH*1000.0 << ",mm" << std::endl; introLines++;
		vatFile << "Base Volume:," << bottomV*1000.0 << ",L" << std::endl; introLines++;
	}

	std::cout << "Enter calculation step (mm): ";
	std::cin >> step;

	step = step/1000.0;

	vatFile << "Step:," << step*1000.0 << ",mm" << std::endl; introLines++;
	vatFile << std::endl << "Fill Level (mm),Total Volume (L)" << std::endl; introLines++;

	intmax_t numberOfValues = (intmax_t)(depth / step + 1.0 + 0.1);
	intmax_t numberOfLines = numberOfValues + introLines;
	std::cout << "Values: " << numberOfValues << std::endl;

	if(checkRadius)
	{
		if(width > 2*radius)
		{
			std::cout << "IMPOSSIBLE RADIUS\n";
			return -2;
		}
	}

	else if(numberOfLines > 1048576)
	{
		std::cout << "Program will output " << numberOfLines <<
		" rows.\nThis will be incompatible with ALL Excel versions.\nDo you wish to continue? (Y/N) ";

		std::cin >> ignoreError;

		if(ignoreError[0] != 'Y' && ignoreError[0] != 'y' && ignoreError[0] != '1')
		{
			std::cout << "Incompatible with ALL Excel versions.";
			return -4;
		}
		else{}
	}
	else if(numberOfLines > 65536)
	{
		std::cout << "Program will output " << numberOfLines <<
		" rows.\nThis will be incompatible with Excel verions before and including 2003.\nDo you wish to continue? (Y/N) ";

		std::cin >> ignoreError;

		if(ignoreError[0] != 'Y' && ignoreError[0] != 'y' && ignoreError[0] != '1')
		{
			std::cout << "Excel Version too old.";
			return -3;
		}
		else{}
	}
	else{}

	double* v = NULL;
	v = new (std::nothrow) double[numberOfValues]; // Assign potentially large amount of memory to heap.
	if(v == NULL)
	{
		std::cout << "Array not created\n";
		return -8;
	}
	else{}

	double h = 0.0;
	intmax_t i = 0;

	time_start = std::chrono::high_resolution_clock::now();

	for(h = 0.0, i = 0; i < numberOfValues; h+= step, i++)
	{
		switch(vat)
		{
			case CYLINDER: v[i] = cylinderVolume(h, width); break;
			case CYLINDERSPHERICALCAP: v[i] = cylinderSphericalCapVolume(h, radius, width, bottomH, bottomV); break;
			case RECTANGLE: v[i] = rectangularVolume(h, width, breadth); break;
			case SQUARE: v[i] = rectangularVolume(h, width, width); break;
			default: return -7;
		}
	}

	time_end = std::chrono::high_resolution_clock::now();

	std::cout << "\n";
	std::cout << "Calculations complete in " << printFormattedTime(time_start, time_end) << std::endl;

	time_start = std::chrono::high_resolution_clock::now();

	for(h = 0.0, i = 0; i < numberOfValues; h+= step, i++)
	{
		vatFile << h*1000.0 << "," << v[i]*1000.0 << "\n";
	}

	time_end = std::chrono::high_resolution_clock::now();

	std::cout << "File writing complete in "<< printFormattedTime(time_start, time_end) << std::endl;

	delete[] v;

	vatFile.close();

	std::cout << "Complete with " << numberOfLines << " lines." << std::endl;

	return 0;
}

void printVatOptions()
{
	std::cout << "Select a vat type:" << std::endl << std::endl;
	std::cout << "Cylinder: " << CYLINDER << std::endl;
	std::cout << "Cylinder with Spherical Cap base: " << CYLINDERSPHERICALCAP << std::endl;
	std::cout << "Rectangular: " << RECTANGLE << std::endl;
	std::cout << "Square: " << SQUARE << std::endl;
}

double cylinderVolume( double height = 1.0, double width = 1.0)
{
	return PI * width * width * height / 4.0;
}

double rectangularVolume(double height = 1.0, double width = 1.0, double breadth = 1.0)
{
	return width * breadth * height;
}

double cylinderSphericalCapVolume(double height = 1.0, double radius = 1.0, double width = 1.0, double bottomH = 0.0/0.0, double bottomV = 0.0/0.0)
{
	if(height < bottomH)
	{
		return ((PI*height*height)/3) * (3*radius-height);
	}
	else
	{
		return cylinderVolume(height-bottomH, width) + bottomV;
	}
}

std::string printFormattedTime(std::chrono::high_resolution_clock::time_point time_start, std::chrono::high_resolution_clock::time_point time_end)
{
	intmax_t a = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end-time_start).count();
	if(a == 0){return "CLOCK ERROR (Reported 0 Nanoseconds)";}
	else if(a == 1){return std::to_string(a) + " Nanosecond";}
	else if(a <= 9999){return std::to_string(a) + " Nanoseconds";}
	else if(a <= 9999999){return std::to_string(a/1000) + " Microseconds";}
	else if(a <= 9999999999){return std::to_string(a/1000000) + " Milliseconds";}
	else{return std::to_string(a/1000000000) + " Seconds";}
	return "That's a nasty error";
}
