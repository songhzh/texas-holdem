#include "Parser.h"

namespace ps
{
	void help(std::string input)
	{
		if (input == "")
			std::cout << "Commands:\n-help\n-info\n-check\n-call\n-raise\n-fold\n-all in\nEnter 'help [command]' for more info" << std::endl;
		else if (input == "help")
			std::cout << "Displays a list of commands. Enter a command for more info." << std::endl;
		else if (input == "info")
			std::cout << "Displays information about yourself and the current game." << std::endl;
		else if (input == "check" || input == "wait")
			std::cout << "Wait on the next player.\nThis can only be done if no players have made a move this round." << std::endl;
		else if (input == "call" || input == "match")
			std::cout << "Match the minimum bet." << std::endl;
		else if (input == "raise" || input == "bet")
			std::cout << "Increase, then match, the minimum bet." << std::endl;
		else if (input == "fold" || input == "quit")
			std::cout << "Remove yourself from the current round.\nYou forfeit your bets." << std::endl;
		else if (input == "all in" || input == "all-in")
			std::cout << "Raise using all of your money." << std::endl;
		else
			std::cout << "'" + input + "' is not a valid command." << std::endl;
	}

	void info(Player* current, std::string input, int minMatch, int pot, std::vector<Card> community)
	{
		if (sf::noAdditionalCommands(input, "info"))
			return;
		if (community.size() > 0) {
			std::cout << "Community : ";
			for (auto it : community) {
				std::cout << it.getName() + " ";
			}
			std::cout << std::endl;
		}
		current->print();
		std::cout << "Min match : $" << minMatch << std::endl;
		std::cout << "Crnt pot  : $" << pot << std::endl;
	}

	bool check(Player* current, std::string input, bool& canCheck)
	{
		if (sf::noAdditionalCommands(input, "check"))
			return false;
		if (canCheck)
		{
			return true;
		}
		std::cout << "You cannot check this round." << std::endl;
		return false;
	}

	bool call(Player* current, std::string input, bool canCheck, int& minMatch)
	{
		if (sf::noAdditionalCommands(input, "call"))
			return false;
		if (canCheck)
		{
			std::cout << "You cannot call before someone raises." << std::endl;
			return false;
		}
		current->call(minMatch);
		return true;
	}

	bool raise(Player* current, std::string input, bool& canCheck, int& minMatch)
	{
		current->raise(minMatch);
		canCheck = false;
		return true;
	}

	bool fold(Player* current, bool& canCheck, std::string input)
	{
		if (sf::noAdditionalCommands(input, "fold"))
			return false;
		current->fold();
		canCheck = false;
		return true;
	}

	bool all_in(Player* current, std::string input, bool& canCheck, int& minMatch)
	{
		if (sf::noAdditionalCommands(input, "all in"))
			return false;
		current->all_in(minMatch);
		canCheck = false;
		return true;
	}

	void parseRound(Player* current, bool& canCheck, int& minMatch, int pot, std::vector<Card> community)
	{
		bool complete = false;
		do
		{
			std::string input;
			sf::getString(input);
			
			if (sf::findString(input, "help"))
				help(input);
			else if (sf::findString(input, "info"))
				info(current, input, minMatch, pot, community);
			else if (sf::findString(input, "check") || sf::findString(input, "wait"))
				complete = check(current, input, canCheck);
			else if (sf::findString(input, "call") || sf::findString(input, "match"))
				complete = call(current, input, canCheck, minMatch);
			else if (sf::findString(input, "raise") || sf::findString(input, "bet"))
				complete = raise(current, input, canCheck, minMatch);
			else if (sf::findString(input, "fold") || sf::findString(input, "quit"))
				complete = fold(current, canCheck, input);
			else if (sf::findString(input, "all in") || sf::findString(input, "all-in"))
				complete = all_in(current, input, canCheck, minMatch);
			else
				std::cout << "Error. Enter 'help' for a list of commands." << std::endl;
		} while (!complete);
	}
}