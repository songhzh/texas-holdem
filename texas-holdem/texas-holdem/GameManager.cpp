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

bool hasRepeatName(std::vector<Player> players, std::string name)
{
	Player temp(name, -1);
	for (auto it : players)
		if (it.getName() == temp.getName())
		{
			std::cout << "Someone has already picked that name!" << std::endl;
			return true;
		}
			
	return false;
}

void GameManager::newGame()
{
	
	std::cout << "Welcome to <Texa$ hold'em!>" << std::endl << std::endl;
	
	std::cout << "How many will be playing? (2-10)" << std::endl;
	int playerNum = sf::getInt(2, 10, "");
	std::cout << std::endl;
	std::cout << "What will be the starting money? ($100-$1,000,000)" << std::endl;
	int startingMoney = sf::getInt(100, 1000000, "$");
	std::cout << std::endl;
	for (int i = 1; i <= playerNum; i++)
	{
		std::cout << "Player " << i << " name?" << std::endl;
		std::string playerName;
		do
		{
			sf::getString(playerName, "");
		} while (playerName == "" || hasRepeatName(players, playerName));
		
		players.push_back(Player(playerName, startingMoney));
		std::cout << std::endl;
	}
	std::cout << "All players accounted for.";

	sf::confirm();
	sf::clearScreen();
	

	//players.push_back(Player("a", 10));
	//players.push_back(Player("b", 2));
	//players.push_back(Player("c", 100));
	
}

int GameManager::getAllPlayers()
{
	return players.size();
}

int GameManager::getActivePlayers()
{
	int num = players.size();
	for (auto it : players)
		if (it.folded || it.getMoneyFree() == 0)
			num--;
	return num;
}

/*
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
*/
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
	std::cout << "[" + rname + ", " + current->getName() + " turn]" << std::endl;
	std::cout << "You must raise during a blind." << std::endl << std::endl;
	if (current->cannotRaise(minMatch, minRaise))
		current->call(minMatch);
	else
		while (!current->raise(minMatch, minRaise)) {}
	if (rname == "BIG BLIND")
	{
		bigBlind = minMatch;
		minRaise = minMatch;
		firstIdx = currentIdx;
	}
	nextPlayer(currentIdx);
	sf::confirm();
	sf::clearScreen();
}

void GameManager::roundContainer(std::string rname1, std::string rname2)
{
	if (rname1 != "PRE-FLOP")
		log.push_back("The " + rname2 + (rname1 == "FLOP" ? " cards " : " card ") + "has been dealt!");
	if (getActivePlayers() == 0)
		return;
	while (continueRound())
	{
		std::cout << "[" + rname1 + ", " + current->getName() + " turn]" << std::endl;
		if (current->newCard && rname1 != "PRE-FLOP")
		{
			std::cout << "The " + rname2 + (rname1 == "FLOP" ? " cards " : " card ") + "has been dealt!" << std::endl;
			current->newCard = false;
		}
		ps::parseRound(this);
		if (!canCheck)
			current->raiseTurn = true;
		nextPlayer(currentIdx);
		updatePot();
		sf::confirm();
		sf::clearScreen();
	}
	nextPlayer(-1);
	firstIdx = currentIdx;
	canCheck = true;
	minRaise = bigBlind;
	for (auto& it : players)
	{
		it.raiseTurn = false;
		it.newCard = true;
	}
}

bool playersRm(Player p)
{
	if (p.getMoneyTotal() == 0)
	{
		std::cout << p.getName() + " has been eliminated." << std::endl;
		return true;
	}
	return false;
}

void GameManager::getWinner()
{
	std::cout << "[SHOWDOWN]" << std::endl;
	/*
	if (getNotFoldedPlayers() == 1)
		std::cout << "Default!" << std::endl;
	else if (getMovesPlayers() == 0)
		std::cout << "No possible moves!" << std::endl;
		*/
	std::cout << std::endl;

	std::vector<Player*> eligible;

	for (auto& it : players)
	{
		cm::getBestHand(it, community, it.score);
		if (!it.folded)
			eligible.push_back(&it);
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
		std::cout << "The winner is: " + eligible.front()->getName();
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
	}
	std::cout << "!" << std::endl;

	for (auto& it : eligible)
	{
		it->winner = true;
	}
		
	for (auto& all : players)
		for (auto& win : eligible)
			all.transfer(win, eligible.size());

	for (auto& it : players)
		it.reset();
	players.erase(std::remove_if(players.begin(), players.end(), playersRm), players.end());

	sf::confirm();
	sf::clearScreen();
}

void GameManager::nextPlayer(int idx)
{
	currentIdx = getNextActivePlayerIdx(idx);
	current = &players[currentIdx];
	updatePot();
}

int GameManager::getNextActivePlayerIdx(int idx)
{
	idx = (idx + 1) % players.size();
	for (auto it : players)
		if (!players[idx].isActive())
			idx = (idx + 1) % players.size();
	return idx;
}

bool GameManager::continueRound()
{
	if (getActivePlayers() == 0)
		return false;
	else if (getActivePlayers() == 1)
	{
		for (auto it : players)
			if (!it.folded && it.getMoneyFree() != 0)
				return !it.hasMatched(minMatch);
	}
	else
		return !allPlayersPlayed();
}

bool GameManager::allPlayersPlayed()
{
	for (auto it : players)
		if (it.isActive() && !it.hasMatched(minMatch))
			return false;
	for (auto it : players)
		if (it.isActive() && !it.raiseTurn)
			return false;
	return true;
}

bool GameManager::allPlayersMatched()
{
	for (auto it : players)
		if (!it.hasMatched(minMatch))
			return false;
	return true;
}

void GameManager::updatePot()
{
	pot = 0;
	for (auto it : players)
		pot += it.getMoneyBet();
}

void GameManager::reset()
{
	community.clear();
	log.clear();
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