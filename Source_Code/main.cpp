#include "files.hpp"
#include "confirm.hpp"
#include "shapes.hpp"
#include "time.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>

#define USER "SOURCE"
#define ACCESS "DEV"
#define VERSION "2020-06-06"



int main()
{
	//std::string version = VERSION;
	std::string compiled = __TIMESTAMP__;
	std::string compiler = __VERSION__;
	std::string version = compiled + "(" + compiler + ")";
	std::cout << "Version: " << version << "\n";
	
	// Main variables
	int ret = 0;

	// Startup
	std::cout << "---STARTUP\n";

	ret = files_setup();
	if(ret != 0){return ret;}
	
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
		std::cout << "Logfile...OK\n";
		logfile.open(logpath, std::ios::out|std::ios::app);
	}
	
	if(!logfile.is_open()){
		std::cout << "ERROR -108: Log file not opened.\n";
		return -108;
	}
	
	logfile << slowtime();

	std::cout << "---STARTUP CHECKS COMPLETE\n\n";

	// Intro

	std::string user = USER;
	std::string access = ACCESS;

	//std::cout << "\x1B[2J\x1B[H";
	//std::cout << "\n\n\n\n\n";
	std::cout << "----- Vat Volume Calculator -----\n";
	std::cout << "User: " + user + "\n";
	std::cout << "Access: " + access + "\n\n";
	
	logfile << "|Version:" << version << "|User:" << user << "|Access:" << access; // LOGFILE

	// IO Settings

	int type = 0;
	double input = 1;
	std::string inputM = "m";

	std::cout << "Input Type\n";
	std::cout << "Metres      - 1\n";
	std::cout << "Millimetres - 2\n";
	std::cout << "Feet        - 3\n";
	std::cout << "\nSelection: ";
	std::cin >> type;
	std::cout << "\n";

	switch(type){
		case 1:
			input = 1;
			inputM = "m";
			break;
		case 2:
			input = 0.001;
			inputM = "mm";
			break;
		case 3:
			input = 0.3048;
			inputM = "ft";
			break;

		// Default Input Case
		default:
			input = 1;
			inputM = "m";
	}
	
	logfile << "|Input:" << input << "(" << inputM << ")"; // LOGFILE

	double output = 0;
	std::string outputM = "";

	std::cout << "Output Type\n";
	std::cout << "Metres Cubed - 1\n";
	std::cout << "Litres       - 2\n";
	std::cout << "Feet Cubed   - 3\n";
	std::cout << "\nSelection: ";
	std::cin >> type;
	std::cout << "\n";

	switch(type){
		case 1:
			output = 1;
			outputM = "m^3";
			break;
		case 2:
			output = 1000;
			outputM = "L";
			break;
		case 3:
			output = 35.3146667;
			outputM = "ft^3";
			break;

		// Default Output Case
		default:
			output = 1;
			outputM = "m^3";
	}
	
	logfile << "|Output:" << output << "(" << outputM << ")"; // LOGFILE


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

	double volume = 0.0;
	double step = 1.0;

	std::cout << "\n";
	std::cout << "Vat Options\n";
	shape_options();
	std::cout << "\n";

	std::cout << "Writing data to: " << filepath << "\n";

	volume = input*input*input*output*cylinder_horizontal(10,3,1.4);
	std::cout << "Volume: " << volume << " " << outputM << "\n";

	// Close All	

	logfile << "\n";
	logfile.close();
	vatfile.close();

	return 0;
}



