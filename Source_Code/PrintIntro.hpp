#ifndef PRINTINTRO_HPP
#define PRINTINTRO_HPP

#include <iostream>
#include <string>

void printIntro(std::string pName = "NULL", std::string name = "SOURCE", intmax_t a = 0, intmax_t b = 0, intmax_t c = 0, intmax_t d = 0, intmax_t e = 0, intmax_t f = 0)
{
	std::string version = std::to_string(a);
	const int max_vI = 6;

	int vI = max_vI;
	intmax_t versionValues[max_vI] = {a,b,c,d,e,f};


	for(int i = vI-1; i > 0; i--)
	{
		if(versionValues[i] == 0)
		{
			vI--;
		}
		else
		{
			break;
		}
	}

	for(int i = 1; i < vI; i++)
	{
		version = version + "." + std::to_string(versionValues[i]);
	}

	std::cout << "User: " << name << "\n";
	std::cout << "Now starting \"" << pName << "\", " << "Version " << version << "\n";
	std::cout << "\n";

	return;
}

#endif
