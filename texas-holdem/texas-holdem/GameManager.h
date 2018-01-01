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
	int getAllPlayers();
	int getFoldedPlayers();
	int getMatchedMaxPlayers();
	void dealPlayerCards(int num);
	void dealCommunityCards(int num);
	void blindContainer(std::string rname);
	void roundContainer(std::string rname1, std::string rname2);
	void getWinner();
	void nextPlayer();
	int getActivePlayerIdx(int offset);
	bool continueRound();
	bool allPlayersPlayed();
	void updatePot();
	void reset();

	std::vector<Player> players;
	std::vector<Card> community;
	Deck deck;
	int bigBlind;
	int minMatch;
	int minRaise;
	int pot;
	int gameIdx;
	int roundIdx; // index of small blind; dealer is ignored
	int firstIdx; // starts at big blind for pre-flop, and small blind for others
	int currentIdx;
	Player* current;
	bool canCheck;
};

