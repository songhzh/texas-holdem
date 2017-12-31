#pragma once

#include "StringFunctions.h"
#include "Player.h"

namespace ps
{
	void parseRound(Player* current, bool& canCheck, int& minMatch, int pot, std::vector<Card> community);
}
