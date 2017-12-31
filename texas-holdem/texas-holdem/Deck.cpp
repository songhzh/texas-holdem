#include "Deck.h"



Deck::Deck()
{
	for (int r = 1; r <= 13; r++)
		for (int s = 0; s <= 3; s++)
			deck.push_back(Card(r, s));
}


Deck::~Deck()
{
}

int myRand(int i) { return rand() % i; }

void Deck::shuffle()
{
	random_shuffle(deck.begin(), deck.end(), myRand);
}

void Deck::print()
{
	std::cout << deck.size() << std::endl;

	for (auto it : deck)
		std::cout << it.getName() << std::endl;
}

Card Deck::draw()
{
	Card c = deck.back();
	deck.pop_back();
	return c;
}