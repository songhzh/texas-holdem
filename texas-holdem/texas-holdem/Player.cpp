#include "Player.h"



Player::Player(std::string n, int m_t) : name(n), money_total(m_t)
{
	reset();
}


Player::~Player()
{
}

std::string Player::getName()
{
	return name;
}

std::vector<Card> Player::getHole()
{
	return hole;
}

bool Player::getFolded()
{
	return folded;
}

int Player::getMoneyBet()
{
	return money_bet;
}

int Player::getMoneyTotal()
{
	return money_total;
}

void Player::call(int min)
{
	if (money_total < min)
		money_bet = money_total;
	else
		money_bet = min;
}

void Player::raise(int& min)
{
	if (money_total > min)
		min = sf::getInt(min + 1, money_total);
	call(min);
}

void Player::fold()
{
	folded = true;
}

void Player::all_in(int& min)
{
	if (money_total > min)
		min = money_total;
	call(min);
}

bool Player::inRound()
{
	return (!folded) && (money_bet != money_total);
}

void Player::draw(Deck& d)
{
	hole.push_back(d.draw());
}

void Player::print()
{
	std::cout << "Your hand : ";
	for (auto it : hole)
		std::cout << it.getName() << " ";
	std::cout << std::endl;
	std::cout << "Your bets : $" << money_bet << std::endl;
	std::cout << "Your total: $" << money_total << std::endl;
}

void Player::reset()
{
	money_bet = 0;
	folded = false;
	hole.clear();
}