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

	bool rmNoneNumeric(char c)
	{
		return c < '0' || c > '9';
	}

	int makeInt(std::string s)
	{
		s.erase(std::remove_if(s.begin(), s.end(), rmNoneNumeric), s.end());
		return s.length() == 0 ? -1 : atoi(s.c_str());
	}

	int getInt(int min, int max, std::string s)
	{
		std::string input;
		int num;
		do
		{
			getString(input, s);
			num = makeInt(input);
		} while (num < min || num > max);

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

	void getString(std::string& input, std::string s)
	{
		std::cout << ">" + s;
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

	void clearScreen()
	{
		std::cout << std::flush;
		if (system("cls"))
			system("clear");
	}

	void line()
	{
		
	}
}