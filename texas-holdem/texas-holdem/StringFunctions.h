#pragma once

#include <iostream>
#include <string>

namespace sf
{
	bool noAdditionalCommands(std::string input, std::string s);
	int getInt(int min, int max);
	void getString(std::string& input);
	void getString(std::string& input, std::string s);
	bool findString(std::string& input, std::string s);
}

