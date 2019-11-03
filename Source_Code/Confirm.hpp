#ifndef CONFIRM_HPP
#define CONFIRN_HPP

#include <string>
#include <iostream>

bool confirm()
{
	std::string aString{"n"};
	getline(std::cin, aString);
	char a = aString[0];

	if(a == 'y'  || a == 'Y' || a == '1' || a == 'j' || a == 'J' || a == 'o' || a == 'O')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif
