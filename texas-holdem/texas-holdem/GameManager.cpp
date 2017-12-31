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
	//players.push_back(Player("c", 100));
}

int GameManager::getActivePlayers()
{
	return players.size();
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
	std::cout << rname + "." << std::endl;
	std::cout << current->getName() + " turn." << std::endl;
	current->raise(minMatch);
	nextPlayer();
}

void GameManager::roundContainer(std::string rname)
{
	while (continueRound())
	{
		if (!current->inRound())
			continue;
		std::cout << rname + "." << std::endl;
		std::cout << current->getName() + " turn." << std::endl;
		ps::parseRound(current, canCheck, minMatch, pot, community);
		nextPlayer();
	}
	canCheck = true;
}

void GameManager::getWinner()
{

}

void GameManager::nextPlayer()
{
	currentIdx = (currentIdx + 1) % players.size();
	current = &players[currentIdx];
	while (!players[roundIdx].inRound())
		roundIdx = (roundIdx + 1) % players.size();
	updatePot();
}

bool GameManager::continueRound()
{
	int foldNum = 0;
	for (auto it : players)
		if (it.getFolded())
			foldNum++;
			
	if (canCheck || (current->getMoneyBet() < minMatch) && (foldNum < players.size() - 1))
		return true;
	return (currentIdx != (roundIdx + 1) % players.size());
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
	players.erase(std::remove_if(players.begin(), players.end(), playersRm), players.end());
	for (auto& it : players)
		it.reset();
	community.clear();
	deck = Deck();
	minMatch = 0;
	minRaise = 0;
	pot = 0;
	gameIdx = (gameIdx + 1) % players.size();
	roundIdx = gameIdx;
	currentIdx = gameIdx;
	current = &players[gameIdx];
	canCheck = true;
}