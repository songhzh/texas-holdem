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
	int getActivePlayers();
	//int getNotFoldedPlayers();
	//int getMovesPlayers();
	void dealPlayerCards(int num);
	void dealCommunityCards(int num);
	void blindContainer(std::string rname);
	void roundContainer(std::string rname1, std::string rname2);
	void getWinner();
	void nextPlayer(int idx);
	int getNextActivePlayerIdx(int idx);
	bool continueRound();
	bool allPlayersPlayed();
	bool allPlayersMatched();
	void updatePot();
	void reset();

	std::vector<Player> players;
	std::vector<Card> community;
	std::vector<std::string> log;
	Deck deck;
	int bigBlind;
	int minMatch;
	int minRaise;
	int pot;
	int gameIdx;
	int roundIdx; // index of small blind; dealer is ignored
	int firstIdx; // starts at big blind for pre-flop, and small blind for rest
	int currentIdx;
	Player* current;
	bool canCheck;
};

