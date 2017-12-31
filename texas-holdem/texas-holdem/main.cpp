#include <iostream>
#include <ctime>

#include "GameManager.h"

int main()
{
	srand(unsigned(time(0)));
	GameManager gm;

	while (gm.getActivePlayers() > 1)
	{
		gm.dealPlayerCards(2);
		gm.blindContainer("Small blind");
		gm.blindContainer("Big blind");
		gm.roundContainer("Pre-flop");
		std::cout << "Flop." << std::endl;
		gm.dealCommunityCards(3);
		gm.roundContainer("Post-flop");
		std::cout << "Turn." << std::endl;
		gm.dealCommunityCards(1);
		gm.roundContainer("Post-turn");
		std::cout << "River." << std::endl;
		gm.dealCommunityCards(1);
		gm.roundContainer("Post-river");
		std::cout << "Showdown." << std::endl;
		gm.getWinner();
		gm.reset();
	}
	return 0;
}