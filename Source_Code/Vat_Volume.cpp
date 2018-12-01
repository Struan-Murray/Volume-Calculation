#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.1415926535
#define UNIT "mm"
#define UNITBASE 1000.0

double getVolume(double, double, double, double, double);
double cylinderVolume(double, double);
void printVatOptions();

enum Vat_Shapes{BEGIN = 0, CYLINDER, CYLINDERSPHERICALCAP, END};

int main()
{
	std::string companyName, vatID, vatTitle, fileName, vatType{"clever, report the bug please"};
	std::ofstream vatFile;
	int_fast16_t introLines{0};
	double depth{0}, width{0}, breadth{0}, side{0}, radius{0};

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
		std::cout << "STRUAN: UNABLE TO OPEN FILE\n";
		perror("OS");
		return -1;
	}

	int vat; // For selecting vat type.
	char ignoreError[20]; // Used to store values for user input re incompatibilities.

	printVatOptions();

	std::cout << "Vat type: ";
	std::cin >> vat;

	vatFile << "Type:,";

	bool needDepth{false}, needWidth{false}, needBreadth{false}, needSide{false}, needRadius{false};
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
			break;
		case 11:
			vatType = "Truncated Spherical Cap Based Vat";
			break;
		case 20:
			vatType = "Cone Based Vat";
			break;
		case 21:
			vatType = "Truncated Cone Based Vat";
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

	double accuracy;
	std::cout << "Enter calculation step (mm): ";
	std::cin >> accuracy;
	accuracy = abs(accuracy)/1000.0;
	vatFile << "Accuracy:," << accuracy*1000.0 << ",mm" << std::endl; introLines++;

	double bottomH = radius-sqrt(radius*radius-((width/2)*(width/2)));
	vatFile << "Base Height:," << bottomH*1000.0 << ",mm" << std::endl; introLines++;

	double bottomV = (PI * bottomH * bottomH / 3) * (3 * radius - bottomH);
	vatFile << "Base Volume:," << bottomV*1000.0 << ",L" << std::endl; introLines++;

	vatFile << std::endl << "Fill Level (mm),Total Volume (L)" << std::endl; introLines++;

	intmax_t numberOfValues = depth / accuracy;

	if(checkRadius)
	{
		if(width > 2*radius)
		{
			std::cout << "IMPOSSIBLE RADIUS";
			return -2;
		}
	}

	else if(numberOfValues > 1048576 - introLines)
	{
		std::cout << "C++ will calculate " << depth << "/" << accuracy << " = " << numberOfValues <<
		" rows.\nThis will be incompatible with ALL Excel versions.\nDo you wish to continue? (Y/N) ";

		std::cin >> ignoreError;

		if(ignoreError[0] != 'Y' && ignoreError[0] != 'y' && ignoreError[0] != '1')
		{
			std::cout << "Incompatible with ALL Excel versions.";
			return -4;
		}
		else{}
	}
	else if(numberOfValues > 65536 - introLines)
	{
		std::cout << "C++ will calculate " << depth << "/" << accuracy << " = " << numberOfValues <<
		" rows.\nThis may be incompatible with Excel verions before and including 2003.\nDo you wish to continue? (Y/N) ";

		std::cin >> ignoreError;

		if(ignoreError[0] != 'Y' && ignoreError[0] != 'y' && ignoreError[0] != '1')
		{
			std::cout << "Excel Version too old.";
			return -3;
		}
		else{}
	}
	else{}


	for(double h = 0, v = 0; h <= depth; h += accuracy)
	{
		switch(vat)
		{
			case CYLINDER: v = cylinderVolume(width, h); break;
			case CYLINDERSPHERICALCAP: v = getVolume(radius, width, h, bottomH, bottomV); break;
			default: v = 0; break;
		}
		vatFile << h*1000.0 << "," << v*1000.0 << "\n";
	}

	vatFile.close();

	std::cout << "Complete " << std::endl;

	return 0;
}

void printVatOptions()
{
	std::cout << "Cylinder: " << CYLINDER << std::endl;
	std::cout << "Cylinder with Spherical Cap base: " << CYLINDERSPHERICALCAP << std::endl;
}

double getVolume(double radius, double width, double height, double bottomH, double bottomV)
{
	if(height < bottomH)
	{
		return ((PI*height*height)/3) * (3*radius-height);
	}
	else
	{
		return cylinderVolume(width, height-bottomH) + bottomV;
	}
}

double cylinderVolume(double width, double height)
{
	return PI * width * width * height / 4.0;
}
