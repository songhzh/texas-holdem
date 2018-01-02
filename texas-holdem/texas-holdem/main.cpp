#include <iostream>
#include <ctime>

#include "GameManager.h"

int main()
{
	srand(unsigned(time(0)));
	GameManager gm;

	while (gm.getAllPlayers() > 1)
	{
		gm.dealPlayerCards(2);
		gm.blindContainer("SMALL BLIND");
		gm.blindContainer("BIG BLIND");
		gm.roundContainer("PRE-FLOP", "");
		gm.dealCommunityCards(3);
		gm.roundContainer("POST-FLOP", "FLOP");
		gm.dealCommunityCards(1);
		gm.roundContainer("POST-TURN", "TURN");
		gm.dealCommunityCards(1);
		gm.roundContainer("POST-RIVER", "RIVER");
		gm.getWinner();
		gm.reset();
	}
	std::cout << "Game over! Thanks for playing <Texa$ Hold'em!>" << std::endl;
	sf::confirm();
	return 0;
}