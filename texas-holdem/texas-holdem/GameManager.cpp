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
	std::cout << "Texa$ hold'em!" << std::endl;

	std::cout << "How many will be playing? (2-10)" << std::endl;
	int playerNum = sf::getInt(2, 10, "");
	std::cout << "What will be the starting money? ($100-$1,000,000)" << std::endl;
	int startingMoney = sf::getInt(100, 1000000, "$");
	players.push_back(Player("a", 100));
	players.push_back(Player("b", 100));
	players.push_back(Player("c", 100));
	players.push_back(Player("d", 100));
	sf::clearScreen();
}

int GameManager::getAllPlayers()
{
	return players.size();
}

int GameManager::getNotFoldedPlayers()
{
	int num = players.size();
	for (auto it : players)
		if (it.folded)
			num--;
	return num;
}

int GameManager::getMovesPlayers()
{
	int num = players.size();
	for (auto it : players)
		if (it.getMoneyFree() == 0 || it.cannotRaise(minRaise))
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
	std::cout << rname + ", " + current->getName() + " turn." << std::endl;
	while (!current->raise(minMatch, minRaise)) {}
	nextPlayer();
	if (rname == "Big blind")
	{
		bigBlind = minMatch;
		minRaise = minMatch;
		firstIdx = getActivePlayerIdx(1);
	}
	sf::clearScreen();
}

void GameManager::roundContainer(std::string rname)
{
	if (getNotFoldedPlayers() == 1 || getMovesPlayers() == 0)
		return;

	unsigned int notInRoundFailsafe = 0; // extra precaution
	while (continueRound())
	{
		if (!current->inRound())
		{
			notInRoundFailsafe++;
			if (notInRoundFailsafe > players.size())
				break;
			nextPlayer();
			continue;
		}
		std::cout << rname + ", " + current->getName() + " turn." << std::endl;
		ps::parseRound(this);
		current->raiseTurn = true;
		nextPlayer();
		sf::clearScreen();
	}
	currentIdx = getActivePlayerIdx(0);
	current = &players[getActivePlayerIdx(0)];
	firstIdx = getActivePlayerIdx(0);
	canCheck = true;
	minRaise = bigBlind;
	for (auto& it : players)
		it.raiseTurn = false;
}

void GameManager::getWinner()
{
	std::cout << "Showdown." << std::endl;
	std::vector<Player*> eligible;

	for (auto& it : players)
	{
		if (it.folded)
			continue;
		eligible.push_back(&it);
		cm::getBestHand(it, community, it.score);
	}
	
	for (int i = 0; i < 6; i++)
	{
		int max = 0;
		for (auto it : eligible)
			max = it->score[i] > max ? it->score[i] : max;

		auto rmPlayers = std::remove_if(eligible.begin(), eligible.end(), [max, i](Player* p)
		{
			return p->score[i] < max;
		});
		eligible.erase(rmPlayers, eligible.end());

		if (eligible.size() == 1)
			break;
	}

	if (eligible.size() == 1)
		std::cout << "The winner is: " + eligible.front()->getName() << std::endl;
	else
	{
		std::cout << "Tie! The winners are: ";
		for (auto it = eligible.begin(); it != eligible.end(); it++)
		{
			if (it == eligible.end() - 1)
				std::cout << " and ";
			std::cout << (*it)->getName();
			if (it < eligible.end() - 2)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
		

	for (auto& it : eligible)
	{
		it->winner = true;
	}
		

	for (auto& all : players)
		for (auto& win : eligible)
			all.transfer(win, eligible.size());
	sf::clearScreen();
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
	if (getNotFoldedPlayers() == 1 || getMovesPlayers() == 0)
		return false;
	if (canCheck || current->getMoneyBet() < minMatch)
		return true;
	return !allPlayersPlayed();
}

bool GameManager::allPlayersPlayed()
{
	for (auto it : players)
	{
		if (!it.inRound())
			continue;
		else if (!it.raiseTurn)
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