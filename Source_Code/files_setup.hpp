#ifndef FILES_SETUP_HPP
#define FILES_SETUP_HPP

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#define LPATH "logs"
#define LRPATH "logs/README.txt"
#define VPATH "vats"
#define VRPATH "vats/README.txt"

int files_setup()
{
	std::cout << "\n-----DIRECTORIES CHECK\n";
	// Create "logs" Directory if it doesn't already exist ERR-101

	if(!std::filesystem::exists(LPATH)){
		std::cout << "Creating new \"logs\" directory.\n";
		std::filesystem::create_directories(LPATH);

		if(!std::filesystem::exists(LPATH)){
			std::cerr << "ERROR -101: \"logs\" Directory not created.\n";
			return -101;
		}
	}
	else{
		std::cout << "\"logs\" Directory...OK\n";
	}

	// Create "logs" README file if it doesn't already exist ERR-102

	std::fstream lreadme;

	if(!std::filesystem::exists(LRPATH)){
		std::cout << "Creating new \"logs\" README.\n";

		lreadme.open(LRPATH, std::ios::out);

		if(!std::filesystem::exists(LRPATH)){
			std::cerr << "ERROR -102: \"logs\" README not created.\n";
			return -102;
		}
		lreadme.close();
	}
	else{
		std::cout << "\"logs\" README 1....OK\n";
	}

	// Modify "logs" README file if it doesn't match current info ERR-103

	lreadme.open(LRPATH, std::ios::in);
	// Log revision date, if the existing log has a different date, overwrites it.
	std::string lreadmeintro = "LRv2020.06.04.14";

	std::string lreadmeline;
	std::getline(lreadme, lreadmeline);

	lreadme.close();

	if(lreadmeline != lreadmeintro){
		std::cout << "Writing new \"logs\" README.\n";
		lreadme.open(LRPATH, std::ios::out|std::ios::in|std::ios::trunc);

		lreadme << lreadmeintro + "\n\n";
		lreadme << "These logs are used to store your previous entries.\n";
		lreadme << "These logs may be deleted if you wish but they act as a history to your searches.\n";
		lreadme << "You can use these to figure out the entries you made, they will not be overwritten for the same vat.\n";
		lreadme << "The purpose of these logs is to help with debugging, repairing mistakes and identifying anomalies in code.\n";
		lreadme.seekg(0);
		lreadmeline = "";
		std::getline(lreadme, lreadmeline);

		if(lreadmeline != lreadmeintro){
			std::cerr << "ERROR -103: \"logs\" README not written.\n";
			return -103;
		}
		lreadme.close();
	}
	else{
		std::cout << "\"logs\" README 2....OK\n";
	}


	// Create "vats" Directory if it doesn't already exist ERR-104

	if(!std::filesystem::exists(VPATH)){
		std::cout << "Creating new \"vats\" directory.\n";
		std::filesystem::create_directories(VPATH);

		if(!std::filesystem::exists(VPATH)){
			std::cerr << "ERROR -104: \"vats\" Directory not created.\n";
			return -104;
		}
	}
	else{
		std::cout << "\"vats\" Directory...OK\n";
	}

	// Create "vats" README file if it doesn't already exist ERR-105

	std::fstream vreadme;

	if(!std::filesystem::exists(VRPATH)){
		std::cout << "Creating new \"vats\" README.\n";
		vreadme.open(VRPATH, std::ios::out);

		if(!std::filesystem::exists(VRPATH)){
			std::cout << "ERROR -105: \"vats\" README not created.\n";
			return -105;
		}
		vreadme.close();
	}
	else{
		std::cout << "\"vats\" README 1....OK\n";
	}

	// Modify "vats" README file if it doesn't match current info ERR-106

	vreadme.open(VRPATH, std::ios::in);
	// Output file revision date, if the existing log has a different date, overwrites it.
	std::string vreadmeintro = "VRv2020.06.04.15";

	std::string vreadmeline;
	std::getline(vreadme, vreadmeline);

	vreadme.close();

	if(vreadmeline != vreadmeintro){
		std::cout << "Writing new \"vats\" README.\n";
		vreadme.open(VRPATH, std::ios::out|std::ios::in|std::ios::trunc);

		vreadme << vreadmeintro + "\n\n";
		vreadme << "These .csv's contain the vat tabling data, they can be opened in Microsoft Excel (Paid), LibreOffice Calc (Free) or Apache OpenOffice Calc (Free) and saved as a .xlsx file.";
		vreadme << "Records of the inputs can be found at the top of the file.\n";
		vreadme << "Running the program for the same vat will overwrite the previous .csv to ensure everything is up to date.\n";
		vreadme << "If you make a mistake, the \"logs\" directory may be of use to try and find previous entries.\n";

		vreadme.seekg(0);
		vreadmeline = "";
		std::getline(vreadme, vreadmeline);

		if(vreadmeline != vreadmeintro){
			std::cout << "ERROR -106: \"vats\" README not written.\n";
			return -106;
		}
		vreadme.close();
	}
	else{
		std::cout << "\"vats\" README 2....OK\n";
	}

	// Next Stuff

	std::filesystem::create_directory("Report This Folder");
	std::filesystem::remove_all("Report This Folder");

	std::cout << "-----DIRECTORIES CHECK COMPLETE\n\n";

	return 102;
}


std::string get_vat_path(){
	return VPATH;
}


std::string get_log_path(){
	return LPATH;
}

#endif
