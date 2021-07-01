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

enum Vat_Shapes{FLAT = 0        , CONE         , SPHERICALCAP         , TRUNCATEDCONE         , TRUNCATEDSPHERICALCAP         ,
                CYLINDER = 10   , CYLINDER_CONE, CYLINDER_SPHERICALCAP, CYLINDER_TRUNCATEDCONE, CYLINDER_TRUNCATEDSPHERICALCAP, CYLINDER_HOR,
                RECTANGULAR = 20,
                END};

int main()
{
	std::cout << "Vat Volume Calculator, User: SOURCE(UNRESTRICTED)\n";
	std::cout << "Instructions, and the latest version of this program's source-code should be available from:\n";
	std::cout << "https://github.com/Struan-Murray/Volume-Calculation\n\n";

	return volumeProgram();
}

void printVatOptions()
{
	//std::cout << "Flat: "                                       << FLAT                           << "\n";
	//std::cout << "Cone: "                                       << CONE                           << "\n";
	//std::cout << "Spherical Cap: "                              << SPHERICALCAP                   << "\n";
	//std::cout << "Truncated Cone: "                             << TRUNCATEDCONE                  << "\n";
	//std::cout << "Truncated Spherical Cap: "                    << TRUNCATEDSPHERICALCAP          << "\n";
	std::cout << "Cylinder with flat base: "                      << CYLINDER                       << "\n";
	std::cout << "Cylinder with cone base: "                      << CYLINDER_CONE                  << "\n";
	std::cout << "Cylinder with spherical cap base: "             << CYLINDER_SPHERICALCAP          << "\n";
	//std::cout << "Cylinder with truncated cone base: "          << CYLINDER_TRUNCATEDCONE         << "\n";
	std::cout << "Cylinder Hor "                                  << CYLINDER_HOR << "\n";
	//std::cout << "Cylinder with truncated spherical cap base: " << CYLINDER_TRUNCATEDSPHERICALCAP << "\n";
	//std::cout << "Rectangular with flat base: "                 << RECTANGULAR                    << "\n";
}

int volumeProgram()
{
	// ------------------------ Setup Variables ------------------------

	std::chrono::high_resolution_clock::time_point time_start = std::chrono::high_resolution_clock::now(), time_end = std::chrono::high_resolution_clock::now();

	std::string advC{"n"}, vatType{"Magic? Report bug please. See \"Error.txt\""};

	double step{0.0}, depth{0.0}, width{0.0}, breadth{0.0}, side{0.0}, baseH{0.0};

	char ignoreError[20]; // Used to store values for user input re incompatibilities

	// ------------------------ Obtaining Names ------------------------

	std::string companyName("VatCo"), vatID("0"), vatTitle("VatCo-0"), fileName("VatCo-0.csv");

	std::cout << "Vat Company: ";
	getline(std::cin, companyName);
	std::cout << "Vat ID: ";
	getline(std::cin, vatID); // Vat's number (ie 27 or 381)
	vatTitle = companyName + "-" + vatID;
	fileName = vatTitle + ".csv";

	// ------------------------ Opening File ------------------------

	std::ofstream vatFile; // The vat file object

	vatFile.open(fileName, std::ios::trunc); // Open file and truncate contents (erases previous content)
	if(vatFile.is_open()){
		std::cout << fileName << " succesfully created and open.\n" << std::endl;
	}
	else{
		std::cout << "STRUAN: UNABLE TO OPEN FILE. Is the file locked by the OS? (Open) Does it have an illegal character? (?,\\,\" etc)\n";
		perror("OS");
		return -1;
	}

	// ------------------------ Obtaining Vat Type ------------------------

	int vat; // For selecting vat type.

	std::cout << "Select a vat type:\n\n";
	printVatOptions();
	std::cout << "\n";
	std::cout << "Vat type: ";
	std::cin >> vat;

	// ------------------------ Registering Required Variables ------------------------

	bool needDepth{false}, needWidth{false}, needBreadth{false}, needSide{false}, needBaseH{false};

	switch(vat)
	{
		/*case CONE:
			vatType = "Cone";
			needDepth = true;
			needWidth = true;
			break;*/
		case CYLINDER:
			vatType = "Flat-Based Cylinder";
			needDepth = true;
			needWidth = true;
			break;
		case CYLINDER_CONE:
			vatType = "Cone-Based Cylinder";
			needDepth = true;
			needWidth = true;
			needBaseH = true;
			break;
		case CYLINDER_SPHERICALCAP:
			vatType = "Spherical-Cap-Based Cylinder";
			needDepth = true;
			needWidth = true;
			needBaseH = true;
			break;
		case CYLINDER_HOR:
			vatType = "Spherical-Cap-Based Cylinder";
			needDepth = true;
			needWidth = true;
			break;
		/*case CUBOID:
			vatType = "Flat-Based Cuboid";
			needDepth = true;
			needWidth = true;
			needBreadth = true;
			break;
		case CUBE:
			vatType = "Flat-Based Cube";
			needDepth = true;
			needWidth = true;
			break;*/
		default:
			std::cout << "Incompatible type";
			return -5;
	}

	// ------------------------ Writing File Frontmatter ------------------------

	int introLines{0}; // For counting the number of lines in the vat file

	vatFile << "Type:," << vatType  << "\n"; introLines++;
	vatFile << "Vat:,"  << vatTitle << "\n"; introLines++;
	vatFile << "\n";                         introLines++;
	vatFile << "Description,Value,Unit\n";   introLines++;

 	// ------------------------ Obtaining Required Variables ------------------------

	if(needDepth)
	{
		std::cout << "Enter vat depth (" << UNIT << "): ";
		std::cin >> depth;
		depth = abs(depth) / UNITBASE;
		vatFile << "Depth:," << depth * UNITBASE << "," << UNIT << "\n"; introLines++;
	}

	if(needWidth)
	{
		std::cout << "Enter vat width (mm): ";
		std::cin >> width;
		width = abs(width)/1000.0;
		vatFile << "Width:," << width*1000.0 << ",mm" << "\n"; introLines++;
	}

	if(needBreadth)
	{
		std::cout << "Enter vat breadth (mm): ";
		std::cin >> breadth;
		breadth = abs(breadth)/1000.0;
		vatFile << "Breadth:," << breadth*1000.0 << ",mm" << "\n"; introLines++;
	}

	if(needSide)
	{
		std::cout << "Enter vat side (mm): ";
		std::cin >> side;
		side = abs(side)/1000.0;
		vatFile << "Breadth:," << side*1000.0 << ",mm" << "\n"; introLines++;
	}

	if(needBaseH)
	{
		std::cout << "Enter vat base height (mm): ";
		std::cin >> baseH;
		baseH = abs(baseH)/1000.0;
		vatFile << "Base Height:," << baseH*1000.0 << ",mm" << "\n"; introLines++;
	}

	std::cout << "Enter calculation step (mm): ";
	std::cin >> step;

	step = step/1000.0;

	vatFile << "Step:," << step*1000.0 << ",mm\n"; introLines++;
	vatFile << std::endl << "Fill Level (mm),Total Volume (L)\n"; introLines++;

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
			case CYLINDER_CONE: v[i] = cylinder_ConeVolume(depth, width, baseH, h); break;
			case CYLINDER_SPHERICALCAP: v[i] = cylinder_SphericalCapVolume(depth, width, baseH, h); break;
			case CYLINDER_HOR: v[i] = cylinder_horizontal(h, width, depth); break;
			//case CUBOID: v[i] = rectangularVolume(depth, width, breadth, h); break;
			//case CUBE: v[i] = rectangularVolume(depth, width, width, h); break;
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

	std::cout << "File writing complete in "<< printFormattedTime(time_start, time_end) << "\n";

	delete[] v;

	vatFile.close();

	std::cout << "Complete with " << numberOfLines << " lines.\n";

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
