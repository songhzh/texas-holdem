#include "Parser.h"

namespace ps
{
	void help(std::string input)
	{
		if (input == "")
			std::cout << "Commands:\n-help\n-info\n-log\n-check\n-call\n-raise\n-all in\n-fold\n"
			"Enter 'help [command]' for more info" << std::endl;
		else if (input == "help")
			std::cout << "Displays a list of commands. Enter a command for more info.\nNot that I needed to tell you this." << std::endl;
		else if (input == "info")
			std::cout << "Displays information about yourself and the current game.\n"
			"Community : 3-5 cards that are shared among players.\n"
			"Your hole : 2 private 'hole' cards make up your hand.\n"
			"Your bets : Money that you have contributed to the pot this game.\n"
			"Your free : Money that you have remaining.\n"
			"Your total: Sum of your bets and free money.\n"
			"Min match : Minimum amount that you must match (call) in order to stay in the game.\n"
			"Min raise : Minimum amount that you must raise by, if you choose to do so.\n"
			"Min total : Minimum amount that 'your bets' will be, if you choose to raise.\n"
			"Crnt pot  : Sum of all bets that players have made this game." << std::endl;
		else if (input == "log")
			std::cout << "A running log of the current game. The newer entries are on top.\n"
			"Additional parameter: [number] of entries to display." << std::endl;
		else if (input == "check" || input == "wait")
			std::cout << "Wait on the next player.\nThis can only be done if no players have called or raised yet this round." << std::endl;
		else if (input == "call" || input == "match")
			std::cout << "Match the minimum bet.\nYou must do this in order to stay in the game." << std::endl;
		else if (input == "raise" || input == "bet")
			std::cout << "Increase and match the minimum bet.\n"
			"Each round, the minimum raise is reset to the big blind amount.\nAdditional parameter: [number] of money to raise to." << std::endl;
		else if (input == "all in" || input == "all-in")
			std::cout << "Raise using all of your money.\n"
			"You may not win more money from each player than the amount you have bet yourself." << std::endl;
		else if (input == "fold" || input == "quit")
			std::cout << "Remove yourself from the current game.\nYou forfeit your bets and cut your losses." << std::endl;
		else
			std::cout << "'" + input + "' is not a valid command." << std::endl;
	}

	void info(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "info"))
			return;
		if (gm->community.size() > 0)
		{
			std::cout << "Community : ";
			for (auto it : gm->community)
				std::cout << it.getName() + " ";
			std::cout << std::endl;
		}
		gm->current->print();
		std::cout << "Min match : $" << gm->minMatch << std::endl;
		std::cout << "Min raise : $" << gm->minRaise << std::endl;
		std::cout << "Min total : $" << gm->minMatch + gm->minRaise << std::endl;
		std::cout << "Crnt pot  : $" << gm->pot << std::endl;
	}

	void log(std::string input, GameManager* gm)
	{
		int num;
		if (input == "")
			num = gm->log.size();
		else if (sf::makeInt(input) > 0)
			num = sf::makeInt(input);
		for (int i = 0; i < num && gm->log.size() > i; i++)
			std::cout << gm->log[gm->log.size() - 1 - i] << std::endl;
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
		if (gm->canCheck)
		{
			std::cout << "To pass your turn, enter 'check'." << std::endl;
			return false;
		}
		if (gm->currentIdx == gm->firstIdx && gm->allPlayersMatched())
		{
			std::cout << "To end the round without raising, enter 'check'." << std::endl;
			return false;
		}
		gm->current->call(gm->minMatch);
		return true;
	}

	bool raise(std::string input, GameManager* gm)
	{
		if (gm->current->cannotRaise(gm->minMatch, gm->minRaise))
		{
			std::cout << "You do not meet the minimum raise amount, but you may go all-in." << std::endl;
			return false;
		}
		if (input == "")
			return gm->current->raise(gm->minMatch, gm->minRaise);
		else if (sf::makeInt(input) != -1)
			return gm->current->raise(gm->minMatch, gm->minRaise, sf::makeInt(input));
		std::cout << "Error. Cannot raise." << std::endl;
		return false;
	}

	bool all_in(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "all in"))
			return false;
		return gm->current->all_in(gm->minMatch, gm->minRaise);
	}

	bool fold(std::string input, GameManager* gm)
	{
		if (sf::noAdditionalCommands(input, "fold"))
			return false;
		gm->current->folded = true;
		return true;
	}

	void parseRound(GameManager* gm)
	{
		while (true)
		{
			std::cout << std::endl;
			std::string input;
			sf::getString(input, "");
			
			if (sf::findString(input, "help"))
				help(input);
			else if (sf::findString(input, "info"))
				info(input, gm);
			else if (sf::findString(input, "log"))
				log(input, gm);
			else if (sf::findString(input, "check") || sf::findString(input, "wait"))
			{
				if (check(input, gm))
				{
					gm->log.push_back("-" + gm->current->getName() + " checked.");
					return;
				}
			}
			else if (sf::findString(input, "call") || sf::findString(input, "match"))
			{
				if (call(input, gm))
				{
					gm->log.push_back("-" + gm->current->getName() + " called $" + std::to_string(gm->minMatch) + ".");
					gm->canCheck = false;
					return;
				}
			}
			else if (sf::findString(input, "raise") || sf::findString(input, "bet"))
			{
				if (raise(input, gm))
				{
					gm->log.push_back("-" + gm->current->getName() + " raised to total $" + std::to_string(gm->minMatch) + ".");
					gm->canCheck = false;
					return;
				}
			}
			else if (sf::findString(input, "all in") || sf::findString(input, "all-in"))
			{
				if (all_in(input, gm))
				{
					gm->log.push_back("-" + gm->current->getName() + " went all in, to total $" + std::to_string(gm->minMatch) + ".");
					gm->canCheck = false;
					return;
				}
			}
			else if (sf::findString(input, "fold") || sf::findString(input, "quit"))
			{
				if (fold(input, gm))
				{
					gm->log.push_back("-" + gm->current->getName() + " folded.");
					return;
				}
			}
			else
				std::cout << "Error. Enter 'help' for a list of commands." << std::endl;
		}
	}
}