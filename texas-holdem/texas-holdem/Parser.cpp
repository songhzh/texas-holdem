#include "Parser.h"

namespace ps
{
	void help(std::string input)
	{
		if (input == "")
			std::cout << "Commands:\n-help\n-info\n-check\n-call\n-raise\n-all in\n-fold\nEnter 'help [command]' for more info" << std::endl;
		else if (input == "help")
			std::cout << "Displays a list of commands. Enter a command for more info." << std::endl;
		else if (input == "info")
			std::cout << "Displays information about yourself and the current game." << std::endl;
		else if (input == "check" || input == "wait")
			std::cout << "Wait on the next player.\nThis can only be done if no players have made a move this round,\n"
			"or you played first this round and have matched the bet." << std::endl;
		else if (input == "call" || input == "match")
			std::cout << "Match the minimum bet." << std::endl;
		else if (input == "raise" || input == "bet")
			std::cout << "Increase, then match, the minimum bet." << std::endl;
		else if (input == "all in" || input == "all-in")
			std::cout << "Raise using all of your money." << std::endl;
		else if (input == "fold" || input == "quit")
			std::cout << "Remove yourself from the current round.\nYou forfeit your bets." << std::endl;
		else
			std::cout << "'" + input + "' is not a valid command." << std::endl;
	}

	void info(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "info"))
			return;
		if (gm->community.size() > 0) {
			std::cout << "Community : ";
			for (auto it : gm->community) {
				std::cout << it.getName() + " ";
			}
			std::cout << std::endl;
		}
		gm->current->print();
		std::cout << "Min match : $" << gm->minMatch << std::endl;
		std::cout << "Min raise : $" << gm->minRaise << std::endl;
		std::cout << "Crnt pot  : $" << gm->pot << std::endl;
	}

	bool check(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "check"))
			return false;
		if (gm->canCheck)
			return true;
		if (gm->currentIdx == gm->firstIdx && gm->current->getMoneyBet() == gm->minMatch)
			return true;
		std::cout << "A bet has been made. You cannot check this round." << std::endl;
		return false;
	}

	bool call(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "call"))
			return false;
		if (gm->canCheck && gm->current->getMoneyBet() == gm->minMatch)
		{
			std::cout << "To pass your turn, enter 'check'." << std::endl;
			return false;
		}
		if (gm->currentIdx == gm->firstIdx && gm->current->getMoneyBet() == gm->minMatch)
		{
			std::cout << "To end the round without raising, enter 'check'." << std::endl;
			return false;
		}
		gm->current->call(gm->minMatch);
		gm->canCheck = false;
		return true;
	}

	bool raise(std::string input, GameManager* gm)
	{
		if (input.length() > 1 && input.front() == '$')
			input = input.substr(1, input.length() - 1);
		if (input == "")
		{
			if (gm->current->raise(gm->minMatch, gm->minRaise))
			{
				gm->canCheck = false;
				return true;
			}
		}
		else if (sf::isInt(input))
		{
			if (gm->current->raise(gm->minMatch, gm->minRaise, atoi(input.c_str())))
			{
				gm->canCheck = false;
				return true;
			}
		}
		std::cout << "Error. cannot raise." << std::endl;
		return false;
	}

	bool all_in(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "all in"))
			return false;
		if (!gm->current->raise(gm->minMatch, gm->minRaise, gm->current->getMoneyTotal()))
		{
			std::cout << "Error. You did not meet the requirements." << std::endl;
			return false;
		}
		gm->canCheck = false;
		return true;
	}

	bool fold(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "fold"))
			return false;
		gm->current->fold();
		return true;
	}

	void parseRound(GameManager* gm)
	{
		bool complete = false;
		do
		{
			std::string input;
			sf::getString(input);
			
			if (sf::findString(input, "help"))
				help(input);
			else if (sf::findString(input, "info"))
				info(input, gm);
			else if (sf::findString(input, "check") || sf::findString(input, "wait"))
				complete = check(input, gm);
			else if (sf::findString(input, "call") || sf::findString(input, "match"))
				complete = call(input, gm);
			else if (sf::findString(input, "raise") || sf::findString(input, "bet"))
				complete = raise(input, gm);
			else if (sf::findString(input, "all in") || sf::findString(input, "all-in"))
				complete = all_in(input, gm);
			else if (sf::findString(input, "fold") || sf::findString(input, "quit"))
				complete = fold(input, gm);
			else
				std::cout << "Error. Enter 'help' for a list of commands." << std::endl;
		} while (!complete);
	}
}