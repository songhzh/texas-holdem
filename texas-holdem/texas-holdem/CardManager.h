#pragma once

#include <algorithm>
#include "Player.h"

namespace cm
{
	void getBestHand(Player& current, std::vector<Card> community, int score[]); // score is size 6; hand type is at idx 0, then 5 tiebreaker cards
}