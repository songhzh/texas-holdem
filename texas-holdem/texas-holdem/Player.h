#pragma once

#include <vector>
#include <iostream>
#include "Deck.h"
#include "StringFunctions.h"

class Player
{
public:
	Player(std::string n, int m_f);
	~Player();

	std::string getName();
	std::vector<Card> getHole();
	int getMoneyBet();
	int getMoneyFree();
	int getMoneyTotal();
	bool hasMatched(int minMatch);
	bool cannotRaise(int minRaise);
	bool inRound();

	void call(int minMatch);
	bool raise(int& minMatch, int& minRaise);
	bool raise(int& minMatch, int& minRaise, int amt);
	void transfer(Player* target, int num);
	
	void draw(Deck& d);
	void print();
	void reset();

	bool folded;
	bool raiseTurn;
	int score[6];
	bool winner;

private:
	void bet(int amt);

	std::string name;
	int money_free;
	int money_bet;
	int money_total;
	std::vector<Card> hole;
	int money_transfer;
};

