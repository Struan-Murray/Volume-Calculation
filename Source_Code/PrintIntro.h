#ifndef PRINT_INTRO
#define PRINT_INTRO

#include <iostream>
#include <string>

void printIntro(std::string name = "NULL", intmax_t a = 0, intmax_t b = 0, intmax_t c = 0, intmax_t d = 0, intmax_t e = 0)
{
	std::string version = std::to_string(a);
	intmax_t versionValues[5] = {a,b,c,d,e};
	int_fast16_t validIntegers = 5;

	for(int16_t i = 4; i > 0; i--)
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

	for(int16_t i = 1; i < validIntegers; i++)
	{
		version = version + "." + std::to_string(versionValues[i]);
	}

	std::cout << "Greetings, user." << std::endl;
	std::cout << "Now starting \"" << name << "\", " << "Version " << version << std::endl;;
	std::cout << std::endl;

	return;
}

#endif
