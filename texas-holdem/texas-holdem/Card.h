#pragma once

#include <string>

struct Card
{
	Card(int r, int s);
	std::string getName();
	int rank;
	int suit;
};

