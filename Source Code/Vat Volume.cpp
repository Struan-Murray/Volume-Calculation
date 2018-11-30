#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.1415926535

using namespace std;

double getVolume(double, double, double, double, double);

int main()
{
	std::string str, title, company, filename, vattype;
	cout << "Vat Company: ";
	getline(cin, company);
	cout << "Vat ID: ";
	getline(cin, str);
	title.append(company);
	title.append("-");
	title.append(str);
	filename.append(title);
	filename.append(".csv");

	ofstream vatfile;

	vatfile.open(filename, ios::trunc);

	if(vatfile.is_open())
	{
		vatfile << "Vat:," << title << endl;
		cout << filename << " succesfully created and open.\n" << endl;
	}
	else
	{
		cout << "UNABLE TO OPEN FILE\n";
		return 1;
	} 

	double depth, width, radius, accuracy;
	//int vat;
	char x[20];

	/*
	cout << "Vat type: ";
	cin >> vat;

	vatfile << "Type:,";

	switch(vat){
		case 10: vatfile << "Spherical Cap Base Vat";
				break;
		case 11:vatfile << "Truncated Spherical Cap Base Vat";
				break;
		case 20: vatfile << "Cone Base Vat";
				break;
		case 21: vatfile << "Truncated Cone Base Vat";
				break;
		default: cout << "Incompatible type";
				return 0;
	}
	*/

	cout << "Enter vat depth (mm): ";
	cin >> depth;
	cout << "Enter vat width (mm): ";
	cin >> width;
	cout << "Enter vat bottom radius (mm): ";
	cin >> radius;
	cout << "Enter calculation step (mm): ";
	cin >> accuracy;

	depth = abs(depth);
	width = abs(width);
	radius = abs(radius);
	accuracy = abs(accuracy);

	if(width > 2*radius)
	{
		cout << "IMPOSSIBLE RADIUS";
		return 2;
	}
	else if(depth / accuracy > 1048575)
	{
		cout << "C++ will calculate " << depth << "/" << accuracy << " = " << depth/accuracy <<
		" rows.\nThis will be incompatible with ALL Excel versions.\nDo you wish to continue? (Y/N) ";

		cin >> x;

		if(x[0] != 'Y' && x[0] != 'y' && x[0] != '1')
		{
			cout << "Incompatible with ALL Excel versions.";
			return 4;
		}
		else{}
	}
	else if(depth / accuracy > 65535)
	{
		cout << "C++ will calculate " << depth << "/" << accuracy << " = " << depth/accuracy <<
		" rows.\nThis may be incompatible with Excel verions before and including 2003.\nDo you wish to continue? (Y/N) ";

		cin >> x;

		if(x[0] != 'Y' && x[0] != 'y' && x[0] != '1')
		{
			cout << "Excel Version too old.";
			return 3;
		}
		else{}
	}
	else{}

	double bottomH = radius-sqrt(radius*radius-((width/2)*(width/2)));
	double bottomV = (PI * bottomH * bottomH / 3) * (3 * radius - bottomH)/1e6;

	vatfile << endl << endl << "Description,Value,Unit" << endl;
	vatfile << "Depth:," << depth << ",mm" << endl;
	vatfile << "Width:," << width << ",mm" << endl;
	vatfile << "Bottom Radius:," << radius << ",mm" << endl;
	vatfile << "Accuracy:," << accuracy << ",mm" << endl;
	vatfile << "Base Height:," << bottomH << ",mm" << endl;
	vatfile << "Base Volume:," << bottomV << ",L" << endl;
	vatfile << endl << "Fill Level (mm),Total Volume (L)" << endl;

	for(double h = 0, v = 0; h <= depth; h += accuracy)
	{
		v = getVolume(radius/1000,width/1000,h/1000,bottomH/1000,bottomV);
		vatfile << h << "," << v << "\n";
	}

	vatfile.close();

	cout << "Complete";

	return 0;
}

double getVolume(double radius, double width, double height, double bottomH, double bottomV)
{
	if(height < bottomH)
	{
		return 1000 * ((PI*height*height)/3) * (3*radius-height);
	}
	else
	{
		return (1000 * (PI*width*width/4)*(height-bottomH) + bottomV);
	}
}