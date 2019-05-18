#ifndef PRINT_INTRO
#define PRINT_INTRO

#include <iostream>
#include <string>

void printIntro(std::string name = "NULL", intmax_t a = 0, intmax_t b = 0, intmax_t c = 0, intmax_t d = 0, intmax_t e = 0)
{
	std::string version = std::to_string(a);
	intmax_t versionValues[5] = {a,b,c,d,e};
	int validIntegers = 5;

	for(int i = 4; i > 0; i--)
	{
		if(versionValues[i] == 0)
		{
			validIntegers--;
		}
		else
		{
			break;
		}
	}

	for(int i = 1; i < validIntegers; i++)
	{
		version = version + "." + std::to_string(versionValues[i]);
	}

	std::cout << "Greetings, user.\n";
	std::cout << "Now starting \"" << name << "\", " << "Version " << version << "\n";
	std::cout << "\n";

	return;
}

#endif
