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
		gm.blindContainer("Small blind");
		gm.blindContainer("Big blind");
		gm.roundContainer("Pre-flop");
		gm.dealCommunityCards(3);
		gm.roundContainer("Post-flop");
		gm.dealCommunityCards(1);
		gm.roundContainer("Post-turn");
		gm.dealCommunityCards(1);
		gm.roundContainer("Post-river");
		gm.getWinner();
		gm.reset();
	}
	return 0;
}