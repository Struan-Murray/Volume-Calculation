#include "PrintIntro.hpp"
#include "Confirm.hpp"
#include "ShapeVolume.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <string>
#include <iomanip> // For Setprecision

#define PI 3.1415926535
#define DUNIT "mm"
#define DUNITBASE 1000.0
#define VUNIT "L"
#define VUNITBASE 1000.0
#define RESTRICTED 0
#define UNIT "mm"
#define UNITBASE 1000.0
#define VOLUME

void printVatOptions();

int volumeProgram();

std::string printFormattedTime(std::chrono::high_resolution_clock::time_point, std::chrono::high_resolution_clock::time_point);

enum Vat_Shapes{BEGIN = 0, CONE, CYLINDER, CYLINDER_SPHERICALCAP, CUBOID, CUBE, END};

int main()
{
	printIntro("Vat Volume Calculator","SOURCE(UNRESTRICTED)",2019,10,30);
	std::cout << "Instructions, and the latest version of this program's source-code should be available from:\n";
	std::cout << "https://github.com/Struan-Murray/Volume-Calculation\n\n";

	return volumeProgram();
}

void printVatOptions()
{
	std::cout << "Select a vat type:" << std::endl << std::endl;
	std::cout << "Cone: " << CONE << std::endl;
	std::cout << "Cylinder with Flat Base: " << CYLINDER << std::endl;
	std::cout << "Cylinder with Spherical Cap base: " << CYLINDER_SPHERICALCAP << std::endl;
	std::cout << "Cuboid with Flat Base: " << CUBOID << std::endl;
	std::cout << "Cube with Flat Base: " << CUBE << std::endl;
}

int volumeProgram()
{
	std::chrono::high_resolution_clock::time_point time_start = std::chrono::high_resolution_clock::now(), time_end = std::chrono::high_resolution_clock::now();
	std::string companyName{"VatCo"}, vatID{"0"}, vatTitle{"VatCo-0"}, fileName{"VatCo-0.csv"}, advC{"n"}, vatType{"Magic? Report bug please."};
	std::ofstream vatFile;
	int_fast16_t introLines{0};
	double step{0.0}, depth{0.0}, width{0.0}, breadth{0.0}, side{0.0}, baseH{0.0};

	std::cout << "Enter Advanced Settings? ";
	if(confirm())
	{
		std::cout << "\nADVANCED SETTINGS\n";
		std::cout << "Dimensions: " << "Cur(" << DUNIT << ") m(1) dm(2) cm(3) mm(4): ";
		std::cout << "\n";
		std::cout << "Volume:     " << "Cur(" << VUNIT << ") m3(1) L(2) cm3(3) mm3(4): ";
		std::cout << "\n\n";
	}
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

	bool needDepth{false}, needWidth{false}, needBreadth{false}, needSide{false}, needBaseH{false};

	switch(vat)
	{
		case CONE:
			vatType = "Cone";
			needDepth = true;
			needWidth = true;
			break;
		case CYLINDER:
			vatType = "Flat-Based Cylinder";
			needDepth = true;
			needWidth = true;
			break;
		case CYLINDER_SPHERICALCAP:
			vatType = "Spherical-Cap-Based Cylinder";
			needDepth = true;
			needWidth = true;
			needBaseH = true;
			break;
		case CUBOID:
			vatType = "Flat-Based Cuboid";
			needDepth = true;
			needWidth = true;
			needBreadth = true;
			break;
		case CUBE:
			vatType = "Flat-Based Cube";
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
		std::cout << "Enter vat depth (" << UNIT << "): ";
		std::cin >> depth;
		depth = abs(depth) / UNITBASE;
		vatFile << "Depth:," << depth * UNITBASE << "," << UNIT << std::endl; introLines++;
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

	if(needBaseH)
	{
		std::cout << "Enter vat base height (mm): ";
		std::cin >> baseH;
		baseH = abs(baseH)/1000.0;
		vatFile << "Base Height:," << baseH*1000.0 << ",mm" << std::endl; introLines++;
	}

	std::cout << "Enter calculation step (mm): ";
	std::cin >> step;

	step = step/1000.0;

	vatFile << "Step:," << step*1000.0 << ",mm" << std::endl; introLines++;
	vatFile << std::endl << "Fill Level (mm),Total Volume (L)" << std::endl; introLines++;

	intmax_t numberOfValues = (intmax_t)(depth / step + 1.0 + 0.1);
	intmax_t numberOfLines = numberOfValues + introLines;
	std::cout << "Values: " << numberOfValues << std::endl;

	if(numberOfLines > 1048576)
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
			case CONE: v[i] = coneVolume(depth, width, h); break;
			case CYLINDER: v[i] = cylinderVolume(depth, width, h); break;
			case CYLINDER_SPHERICALCAP: v[i] = cylinder_SphericalCapVolume(depth, width, baseH, h); break;
			case CUBOID: v[i] = rectangularVolume(depth, width, breadth, h); break;
			case CUBE: v[i] = rectangularVolume(depth, width, width, h); break;
			default: return -7;
		}
	}

	time_end = std::chrono::high_resolution_clock::now();

	std::cout << "\n";
	std::cout << "Calculations complete in " << printFormattedTime(time_start, time_end) << std::endl;

	time_start = std::chrono::high_resolution_clock::now();

	for(h = 0.0, i = 0; i < numberOfValues; h+= step, i++)
	{
		vatFile << std::scientific << std::setprecision(3) << h*1000.0 << ",";
		vatFile << std::fixed << std::setprecision(3) << v[i]*1000.0 << "\n";
	}

	std::cout << std::scientific << std::setprecision(9);

	time_end = std::chrono::high_resolution_clock::now();

	std::cout << "File writing complete in "<< printFormattedTime(time_start, time_end) << std::endl;

	delete[] v;

	vatFile.close();

	std::cout << "Complete with " << numberOfLines << " lines." << std::endl;

	return 0;
}

/* Timing Stuff */

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
