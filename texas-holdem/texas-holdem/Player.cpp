#include "Player.h"



Player::Player(std::string n, int m_f) : name(n), money_free(m_f)
{
	money_bet = 0;
	reset();
}


Player::~Player()
{
}

std::string Player::getName()
{
	return "<" + name + ">";
}

std::vector<Card> Player::getHole()
{
	return hole;
}

int Player::getMoneyBet()
{
	return money_bet;
}

int Player::getMoneyFree()
{
	return money_free;
}

int Player::getMoneyTotal()
{
	return money_total;
}

bool Player::hasMatched(int minMatch)
{
	if (money_total < minMatch)
		return money_bet == money_total;
	else
		return money_bet == minMatch;
}

bool Player::cannotRaise(int minRaise)
{
	return money_bet + minRaise > money_total && hasMatched(minRaise);
}

bool Player::inRound()
{
	return (!folded) && (money_free != 0);
}

void Player::bet(int amt)
{
	money_bet += amt;
	money_free -= amt;
}

void Player::call(int minMatch)
{
	if (money_total < minMatch)
		bet(money_free);
	else
		bet(minMatch - money_bet);
}

bool Player::raise(int& minMatch, int& minRaise)
{
	if (money_total < minMatch + minRaise)
	{
		std::cout << "You do not meet the minimum raise amount." << std::endl;
		return false;
	}
	std::cout << "Your bets : $" << money_bet << std::endl;
	std::cout << "Your free : $" << money_free << std::endl;
	std::cout << "Min raise : $" << minRaise << std::endl;
	std::cout << "Min total : $" << minMatch + minRaise << std::endl;
	int match = sf::getInt(1, money_total, "$");
	if (match - minMatch < minRaise)
	{
		std::cout << "The amount was not enough." << std::endl;
		return false;
	}
	minRaise = match - minMatch;
	minMatch = match;
	call(minMatch);
	return true;
}

bool Player::raise(int& minMatch, int& minRaise, int amt)
{
	if (money_total < minMatch + minRaise)
	{
		std::cout << "You do not meet the minimum raise amount." << std::endl;
		return false;
	}
	else if (amt - minMatch < minRaise)
	{
		std::cout << "The amount was not enough." << std::endl;
		return false;
	}
	minRaise = amt - minMatch;
	minMatch = amt;
	call(minMatch);
	return true;
}

bool Player::all_in(int& minMatch, int& minRaise)
{
	if (money_total <= minMatch)
	{
		std::cout << "You call using all of your money." << std::endl;
		call(minMatch);
	}
	else
	{
		minRaise = money_total - minMatch;
		minMatch = money_total;
		call(money_total);
	}
	return true;
}

void Player::transfer(Player* target, int num)
{
	if (winner)
		return;
		
	if (money_transfer == -1)
		money_transfer = money_bet / num;
	int amt = target->money_bet < money_transfer ? target->money_bet : money_transfer;
	target->money_bet += amt;
	money_bet -= amt;
}

void Player::draw(Deck& d)
{
	hole.push_back(d.draw());
}

void Player::print()
{
	std::cout << "Your hole : ";
	for (auto it : hole)
		std::cout << it.getName() << " ";
	std::cout << std::endl;
	std::cout << "Your bets : $" << money_bet << std::endl;
	std::cout << "Your free : $" << money_free << std::endl;
	std::cout << "Your total: $" << money_total << std::endl;
}

void Player::reset()
{
	money_free += money_bet;
	money_bet = 0;
	money_total = money_free;
	hole.clear();
	money_transfer = -1;
	folded = false;
	raiseTurn = false;
	newCard = true;
	score[4] = { 0 };
	winner = false;
}