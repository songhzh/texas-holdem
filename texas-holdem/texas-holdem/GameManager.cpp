#include "GameManager.h"



GameManager::GameManager()
{
	gameIdx = -1;
	roundIdx = -1;
	currentIdx = -1;
	newGame();
	reset();
}


GameManager::~GameManager()
{
}

void GameManager::newGame()
{
	players.push_back(Player("a", 100));
	players.push_back(Player("b", 100));
	players.push_back(Player("c", 100));
}

int GameManager::getAllPlayers()
{
	return players.size();
}

int GameManager::getFoldedPlayers()
{
	int num = players.size();
	for (auto it : players)
		if (it.getFolded())
			num--;
	return num;
}

int GameManager::getMatchedMaxPlayers()
{
	int num = players.size();
	for (auto it : players)
		if (it.getMoneyFree() == 0)
			num--;
	return num;
}

void GameManager::dealPlayerCards(int num)
{
	for (int i = 0; i < num; i++)
		for (auto& it : players)
			it.draw(deck);
}

void GameManager::dealCommunityCards(int num)
{
	for (int i = 0; i < num; i++)
		community.push_back(deck.draw());
}

void GameManager::blindContainer(std::string rname)
{
	std::cout << rname << std::endl;
	std::cout << current->getName() + " turn." << std::endl;
	while (!current->raise(minMatch, minRaise)) {}
	nextPlayer();
	if (rname == "Big blind.")
	{
		bigBlind = minMatch;
		minRaise = minMatch;
		firstIdx = getActivePlayerIdx(1);
	}
}

void GameManager::roundContainer(std::string rname1, std::string rname2)
{
	if (getFoldedPlayers() == 1 || getMatchedMaxPlayers() == 0)
		return;

	std::cout << rname1;
	while (continueRound())
	{
		if (!current->inRound())
			continue;
		std::cout << rname2 << std::endl;
		std::cout << current->getName() + " turn." << std::endl;
		ps::parseRound(this);
		nextPlayer();
	}
	currentIdx = getActivePlayerIdx(0);
	current = &players[getActivePlayerIdx(0)];
	firstIdx = getActivePlayerIdx(0);
	canCheck = true;
	minRaise = bigBlind;
}

void GameManager::getWinner()
{
	std::cout << "Showdown." << std::endl;
	for (auto it : players)
	{
		it.print();
		std::cout << std::endl;
	}
		
}

void GameManager::nextPlayer()
{
	currentIdx = (currentIdx + 1) % players.size();
	current = &players[currentIdx];
	updatePot();
}

int GameManager::getActivePlayerIdx(int offset)
{
	int idx = roundIdx + offset;
	while (!players[idx].inRound())
		idx = (idx + 1) % players.size();
	return idx;
}

bool GameManager::continueRound()
{
	if (getFoldedPlayers() == 1 || getMatchedMaxPlayers() == 0)
		return false;
	if (canCheck || current->getMoneyBet() < minMatch || !allPlayersPlayed())
		return true;
	return currentIdx == firstIdx;
}

bool GameManager::allPlayersPlayed()
{
	for (auto it : players)
	{
		if (!it.inRound())
			continue;
		else if (!it.hasMatched(minMatch))
			return false;
	}
	return true;
}

void GameManager::updatePot()
{
	pot = 0;
	for (auto it : players)
		pot += it.getMoneyBet();
}

bool playersRm(Player p)
{
	return p.getMoneyTotal() == 0;
}

void GameManager::reset()
{
	for (auto& it : players)
		it.reset();
	players.erase(std::remove_if(players.begin(), players.end(), playersRm), players.end());
	community.clear();
	deck = Deck();
	deck.shuffle();
	bigBlind = 0;
	minMatch = 0;
	minRaise = 1;
	pot = 0;
	gameIdx = (gameIdx + 1) % players.size();
	roundIdx = gameIdx;
	firstIdx = 0;
	currentIdx = gameIdx;
	current = &players[gameIdx];
	canCheck = true;
}