#pragma once

#include <algorithm>
#include <iostream>
#include <string>

namespace sf
{
	bool noAdditionalCommands(std::string input, std::string s);
	int makeInt(std::string s);
	int getInt(int min, int max, std::string s);
	void getString(std::string& input, std::string s);
	bool findString(std::string& input, std::string s);

	void clearScreen();
	void confirm();
}

