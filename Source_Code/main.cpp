#include "files_setup.hpp"
#include "confirm.hpp"
#include "shapes.hpp"
#include "time.hpp"

#include <cmath>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>

#define USER "DEV"
#define VERSION "UNCERTIFIED"

int intro();
int volumeProgram();

int main()
{
	int ret = 0; // Error return variable

	ret = intro(); // Prints intro lines (Title, Version, User)
	if(ret <= 0){return ret;}

	ret = files_setup(); // Set-up folders and directories
	if(ret <= 0){return ret;}

	return volumeProgram();
}

int intro()
{
	std::cout << "----- Vat Volume Calculation Program -----\n";
	std::cout << "Version: " << VERSION << " (" << __DATE__ " " << __TIME__ << ")\n";
	std::cout << "User:    " << USER << "\n";
	return 101;
}

int volumeProgram()
{
	// Startup
	std::cout << "-----STARTUP CHECK\n";

	std::fstream logfile;

	std::string logname = "log.txt";
	std::string logpath = get_log_path() + "/" + logname;

	if(!std::filesystem::exists(logpath)){
		std::cout << "Creating new log file...\n";
		logfile.open(logpath, std::ios::out|std::ios::trunc);

		if(!std::filesystem::exists(logpath)){
			std::cout << "ERROR -107: Log file not created.\n";
			return -107;
		}
	}
	else{
		std::cout << "Logfile............OK\n";
		logfile.open(logpath, std::ios::out|std::ios::app);
	}

	if(!logfile.is_open()){
		std::cout << "ERROR -108: Log file not opened.\n";
		return -108;
	}

	logfile << slowtime();

	std::cout << "-----STARTUP CHECK COMPLETE\n\n";

	// Intro

	std::string user = USER;
	std::string access = "NUL";

	//std::cout << "\x1B[2J\x1B[H";
	//std::cout << "\n\n\n\n\n";
	std::cout << "----- Vat Volume Calculator -----\n";
	std::cout << "User: " + user + "\n";
	std::cout << "Access: " + access + "\n\n";

	// IO Settings

	int type = 0;
	double to_m_conv = 1;
	double from_m_conv = 1;
	std::string str_input_unit = "m";

	std::cout << "Input Type\n";
	std::cout << "Metres      - 1\n";
	std::cout << "Millimetres - 2\n";
	std::cout << "Feet        - 3\n";
	std::cout << "Inches      - 4\n";
	std::cout << "\nSelection: ";
	std::cin >> type;
	std::cout << "\n";

	switch(type){
		case 1:
			to_m_conv= 1;
			from_m_conv = 1/to_m_conv;
			str_input_unit = "m";
			break;
		case 2:
			to_m_conv= 0.001;
			from_m_conv = 1/to_m_conv;
			str_input_unit = "mm";
			break;
		case 3:
			to_m_conv= 0.3048;
			from_m_conv = 1/to_m_conv;
			str_input_unit = "ft";
			break;
		case 4:
			to_m_conv= 0.0254;
			from_m_conv = 1/to_m_conv;
			str_input_unit = "in";
			break;

		// Default Input Case
		default:
			to_m_conv= 1;
			from_m_conv = 1/to_m_conv;
			str_input_unit = "m";
	}

	logfile << "|Input:" << to_m_conv<< "(" << str_input_unit << ")"; // LOGFILE

	double from_m3_conv = 0;
	std::string str_output_unit = "";

	std::cout << "Output Type\n";
	std::cout << "Metres Cubed   - 1\n";
	std::cout << "Litres         - 2\n";
	std::cout << "Cubic Feet     - 3\n";
	std::cout << "Imperial Pints - 4\n";
	std::cout << "\nSelection: ";
	std::cin >> type;
	std::cout << "\n";

	switch(type){
		case 1:
			from_m3_conv = 1.0;
			str_output_unit = "m^3";
			break;
		case 2:
			from_m3_conv = 1000.0;
			str_output_unit = "L";
			break;
		case 3:
			from_m3_conv = 35.3146667;
			str_output_unit = "ft^3";
			break;
		case 4:
			from_m3_conv = 1000000.0 / 568.26125;
			str_output_unit = "pt";
			break;

		// Default Output Case
		default:
			from_m3_conv= 1;
			str_output_unit = "m^3";
	}

	logfile << "|Output:" << from_m3_conv<< "(" << str_output_unit << ")"; // LOGFILE

	std::string vat_company{"NULL"}, vat_id{"NULL"};

	std::cout << "Vat Company:";
	std::cin.ignore(100,'\n');
	std::getline(std::cin,vat_company);
	std::cout << "Vat ID     :";
	std::getline(std::cin,vat_id);

	logfile << "|Company:" << vat_company << "|ID:" << vat_id; // LOGFILE

	std::string filename = vat_company + "-" + vat_id + ".csv";
	std::string filepath = get_vat_path() + "/" + filename;

	logfile << "|Filepath:" << filepath;

	// Main Sequence

	std::fstream vatfile;

	vatfile.open(filepath, std::ios::out|std::ios::in|std::ios::trunc);

	if(!std::filesystem::exists(filepath)){
		std::cout << "ERROR -109: Vat file not created.\n";
		return -109;
	}
	if(!vatfile.is_open()){
		std::cout << "ERROR -110: Vat file not opened.\n";
		return -110;
	}

	// -------------------- Vat Type Numbering --------------------

	enum Vat_Shapes{FLAT = 1 , CONE, SPHERE, SPHERICALCAP         , TRUNCATEDCONE         , TRUNCATEDSPHERICALCAP         ,
                        CYLINDER   , CYLINDER_CONE, CYLINDER_SPHERICALCAP, CYLINDER_TRUNCATEDCONE, CYLINDER_TRUNCATEDSPHERICALCAP, CYLINDER_HOR,
                        RECTANGULAR,
                        END};

	// -------------------- Vat Type Display --------------------

	std::cout << "\n";
	std::cout << "Vat Options\n";

	//std::cout << "Flat: "                                         << FLAT                           << "\n";
    std::cout << "Cone: "                                         << CONE                           << "\n";
    std::cout << "Sphere: "                                         << SPHERE                           << "\n";
    std::cout << "Spherical Cap: "                                << SPHERICALCAP                   << "\n";
    //std::cout << "Truncated Cone: "                               << TRUNCATEDCONE                  << "\n";
    //std::cout << "Truncated Spherical Cap: "                      << TRUNCATEDSPHERICALCAP          << "\n";
    std::cout << "Vertical Cylinder with flat ends: "                      << CYLINDER                       << "\n";
    //std::cout << "Cylinder with cone base: "                      << CYLINDER_CONE                  << "\n";
    //std::cout << "Cylinder with spherical cap base: "             << CYLINDER_SPHERICALCAP          << "\n";
    //std::cout << "Cylinder with truncated cone base: "            << CYLINDER_TRUNCATEDCONE         << "\n";
    std::cout << "Horizontal Cylinder with flat ends: "           << CYLINDER_HOR                   << "\n";
    //std::cout << "Cylinder with truncated spherical cap base: "   << CYLINDER_TRUNCATEDSPHERICALCAP << "\n";
    std::cout << "Cuboid: "                                       << RECTANGULAR                    << "\n";

	std::cout << "\n";

	// -------------------- Vat Type Input --------------------

	int vat = 0; // Vat type storage variable

	std::cout << "Vat type: ";

	std::cin >> vat;

	// -------------------- Vat Type Required Variables --------------------

	bool needHeight{false}, needWidth{false}, needRadius{false}, needLength{false}, needDiameter{false};
	std::string strVatType = "NULL";

	switch(vat)
	{
		case CONE:
			strVatType = "Conical Vat";
			needDiameter = true; needHeight= true;
			break;
		case SPHERE:
			strVatType = "Spherical Vat";
			needDiameter = true;
			break;
		case SPHERICALCAP:
			strVatType = "Spherical Cap Vat";
			needWidth = true; needHeight = true;
			break;
		case CYLINDER:
			strVatType = "Vertical Cylinder with flat ends";
			needRadius = true; needLength = true;
			break;
		case CYLINDER_HOR:
			strVatType = "Horizontal Cylinder with flat ends";
			needRadius = true; needLength = true;
			break;
		case RECTANGULAR:
			strVatType = "Cuboid";
			needHeight = true; needWidth = true; needLength = true;
			break;
		default:
			std::cout << "Incompatible type";
			return -5;
	}

	// -------------------- Required Variables Input --------------------

	std::string storedVariables = "", tempVariables = "";
	storedVariables += ("Vat Type:," + strVatType + "\n");
	logfile << "|Type:" << strVatType << ":" << vat;

	double diameter{0.0};
	if(needDiameter)
	{
		std::cout << "Enter vat diameter (" << str_input_unit << "): ";
		std::cin >> diameter;
		storedVariables += ("Diameter:," + std::to_string(diameter) + "," + str_input_unit + "\n");
		logfile << "|Diameter:" << diameter;
		diameter = abs(diameter) * to_m_conv;
	}	
	
	double height{0.0};
	if(needHeight)
	{
		std::cout << "Enter vat height (" << str_input_unit << "): ";
		std::cin >> height;
		storedVariables += ("Height:," + std::to_string(height) + "," + str_input_unit + "\n");
		logfile << "|Height:" << height;
		height = abs(height) * to_m_conv;
	}

	double width{0.0};
	if(needWidth)
	{
		std::cout << "Enter vat width (" << str_input_unit << "): ";
		std::cin >> width;
		storedVariables += ("Width:," + std::to_string(width) + "," + str_input_unit + "\n");
		logfile << "|Width:" << width;
		width = abs(width) * to_m_conv;
	}

	double radius{0.0};
	if(needRadius)
	{
		std::cout << "Enter vat radius (" << str_input_unit << "): ";
		std::cin >> radius;
		storedVariables += ("Radius:," + std::to_string(radius) + "," + str_input_unit + "\n");
		logfile << "|Radius:" << radius;
		radius = abs(radius) * to_m_conv;
	}

	double length{0.0};
	if(needLength)
	{
		std::cout << "Enter vat length (" << str_input_unit << "): ";
		std::cin >> length;
		storedVariables += ("Length:," + std::to_string(length) + "," + str_input_unit + "\n");
		logfile << "|Length:" << length;
		length = abs(length) * to_m_conv;
	}

	double step{0.0};
	if(true)
	{
		std::cout << "Enter step size required (" << str_input_unit << "): ";
		std::cin >> step;
		storedVariables += ("Step:," + std::to_string(step) + "," + str_input_unit + "\n");
		logfile << "|Step:" << step;
		step = abs(step) * to_m_conv;
    }

	double depth{0.0};

	switch(vat)
	{
		case CYLINDER: depth=length; break;
		case SPHERE: depth=diameter; break;
		case SPHERICALCAP: depth=height; break;
		case CYLINDER_HOR: depth=2*radius; break;
		case RECTANGULAR: depth=height; break;
		case CONE: depth=height; break;
	}

	// -------------------- Assign memory for tabling --------------------

	long long int numberOfValues = (long long int)(depth / step + 1.0 + 0.1);

	double* v = NULL;
	v = new (std::nothrow) double[numberOfValues]; // Assign potentially large amount of memory to heap.
	if(v == NULL)
	{
		std::cout << "Array not created\n";
		return -8;
	}

	// -------------------- Calculate tabling --------------------

	double h = 0.0;
	intmax_t i = 0;

	for(h = 0.0, i = 0; i < numberOfValues; h+= step, i++)
	{
		switch(vat)
		{
			case CYLINDER: v[i] = cylinder_vertical(h, radius); break;
			case SPHERE: v[i] = sphere(h,diameter/2.0); break;
			case SPHERICALCAP: v[i] = spherical_cap(h,height,width/2.0); break;
			case CYLINDER_HOR: v[i] = cylinder_horizontal(h, length, radius); break;
			case RECTANGULAR: v[i] = cuboid(h,length,width); break;
			case CONE: v[i] = cone(h,diameter,height); break;
			default: return -7;
		}
	}

	// -------------------- Output data --------------------

	std::cout << "Writing data to: " << filepath << "\n";

	vatfile << storedVariables;

	vatfile << "Depth (" << str_input_unit << "),Volume (" << str_output_unit << ")\n";

	for(h = 0.0, i = 0; i < numberOfValues; h+= step, i++)
	{
		vatfile << std::scientific << std::setprecision(3) << h*from_m_conv << ","; 
		vatfile << std::fixed << std::setprecision(3) << v[i]*from_m3_conv << ",";
		vatfile << "\n";
	}

	// -------------------- Close all --------------------

	delete[] v;
	logfile << "\n";
	logfile.close();
	vatfile.close();
	std::cout << "\a\n"; // End of file bell and space

	return 0;
}
