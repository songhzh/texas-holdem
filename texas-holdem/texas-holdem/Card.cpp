#include "Card.h"

Card::Card(int r, int s) : rank(r), suit(s)
{
}

std::string Card::getName()
{
	std::string name;
	name += '[';
	switch (rank)
	{
	case 1:
		name += 'A';
		break;
	case 10:
		name += 'T';
		break;
	case 11:
		name += 'J';
		break;
	case 12:
		name += 'Q';
		break;
	case 13:
		name += 'K';
		break;
	default:
		name += rank + '0';
		break;
	}
	name += '.';
	switch (suit)
	{
	case 0:
		name += 'C';
		break;
	case 1:
		name += 'D';
		break;
	case 2:
		name += 'H';
		break;
	case 3:
		name += 'S';
		break;
	default:
		name += '?';
		break;
	}
	name += ']';

	return name;
}