#pragma once

#include <vector>
#include <iostream>
#include "Deck.h"
#include "StringFunctions.h"

class Player
{
public:
	Player(std::string n, int m_t);
	~Player();

	std::string getName();
	std::vector<Card> getHole();
	bool getFolded();
	int getMoneyBet();
	int getMoneyTotal();

	void call(int min);
	void raise(int& min);
	void fold();
	void all_in(int& min);
	bool inRound();

	void draw(Deck& d);
	void print();
	void reset();

private:
	std::string name;
	int money_total;
	int money_bet;
	bool folded;
	std::vector<Card> hole;
};

