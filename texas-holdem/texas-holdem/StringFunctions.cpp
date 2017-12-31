#include "StringFunctions.h"


namespace sf
{
	bool noAdditionalCommands(std::string input, std::string s)
	{
		if (input != "")
		{
			std::cout << "'" + s + "' does not take additional commands." << std::endl;
			return true;
		}
		return false;
	}

	bool isInt(std::string s)
	{
		for (auto it : s)
			if (it < '0' || it > '9')
				return false;
		return true;
	}

	int getInt(int min, int max)
	{
		std::string s;
		int num;
		do
		{
			getString(s, "$");
			num = atoi(s.c_str());
		} while (!isInt(s) || num < min || num > max);

		return num;
	}

	void rmWhiteSpace(std::string& s)
	{

	}

	void lowerString(std::string& s)
	{
		for (auto& it : s)
			if (it >= 'A' && it <= 'Z')
				it -= 'A' - 'a';
	}

	void getString(std::string& input)
	{
		std::cout << ">";
		std::getline(std::cin, input);
		rmWhiteSpace(input);
		lowerString(input);
	}

	void getString(std::string& input, std::string s)
	{
		std::cout << ">" << s;
		std::getline(std::cin, input);
		rmWhiteSpace(input);
		lowerString(input);
	}

	bool findString(std::string& input, std::string s)
	{
		if (input.find(s) == 0)
		{
			input.erase(0, s.length() + 1);
			return true;
		}
		return false;
	}
}