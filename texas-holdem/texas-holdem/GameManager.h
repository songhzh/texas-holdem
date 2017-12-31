#pragma once

#include <vector>
#include "CardManager.h"
#include "Parser.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void newGame();
	int getActivePlayers();
	void dealPlayerCards(int num);
	void dealCommunityCards(int num);
	void blindContainer(std::string rname);
	void roundContainer(std::string rname);
	void getWinner();
	void nextPlayer();
	bool continueRound();
	void updatePot();
	void reset();

private:
	std::vector<Player> players;
	std::vector<Card> community;
	Deck deck;
	int minMatch;
	int minRaise;
	int pot;
	int gameIdx;
	int roundIdx;
	int currentIdx;
	Player* current;
	bool canCheck;
};

