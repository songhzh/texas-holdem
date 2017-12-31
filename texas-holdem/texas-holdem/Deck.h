#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include "Card.h"

class Deck
{
public:
	Deck();
	~Deck();
	void shuffle();
	void print();
	Card draw();
private:
	std::vector<Card> deck;
};

