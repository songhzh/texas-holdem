#include "CardManager.h"


namespace cm
{
	std::vector<Card> mergeHands(Player& current, std::vector<Card> community)
	{
		std::vector<Card> hand = current.getHole();
		for (auto it : community)
			hand.push_back(it);
		return hand;
	}

	void cardSwap(std::vector<Card>& hand, int& idx, std::vector<Card>::iterator it)
	{
		Card temp = *it;
		*it = hand[idx];
		hand[idx] = temp;
		idx++;
	}

	bool hSorter(Card c1, Card c2)
	{
		return c1.rank > c2.rank;
	}

	void sortHand(std::vector<Card>& hand, int idx)
	{
		for (auto it = hand.begin() + idx; it != hand.end(); it++)
			if (it->rank == 1)
			{
				cardSwap(hand, idx, it);
			}
		std::sort(hand.begin() + idx, hand.end(), hSorter);
	}

	void printHand(std::vector<Card> hand)
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << hand[i].getName() + " ";
		}
		std::cout << " | ";
		for (int i = 5; i < 7; i++)
		{
			std::cout << hand[i].getName() + " ";
		}
		std::cout << std::endl << std::endl;
	}

	bool hasMoveFront(std::vector<Card>& hand, int r, int& idx)
	{
		for (auto it = hand.begin() + idx; it != hand.end(); it++)
			if (it->rank == r)
			{
				cardSwap(hand, idx, it);
				return true;
			}
		return false;
	}

	bool hasMoveFront(std::vector<Card>& hand, int r, int s, int& idx)
	{
		for (auto it = hand.begin() + idx; it != hand.end(); it++)
			if (it->rank == r && it->suit == s)
			{
				cardSwap(hand, idx, it);
				return true;
			}
		return false;
	}

	bool hasSame(std::vector<Card>& hand, int& idx, int r, int num)
	{
		int tempIdx = idx;
		for (int c = 0; c < num; c++)
			if (!hasMoveFront(hand, r, idx))
			{
				idx = tempIdx;
				return false;
			}
		return true;
	}

	int flushCheck(std::vector<Card> hand)
	{
		for (int s = 0; s <= 3; s++)
		{
			int count = 0;
			for (auto it : hand)
				if (it.suit == s)
					count++;
			if (count >= 5)
				return s;
		}
		return -1;
	}

	int straightCheck(std::vector<Card>& hand, int s)
	{
		int idx = 0;
		if (hasMoveFront(hand, 1, s, idx))
		{
			bool s1 = true;
			for (int r = 13; r >= 10 && s1; r--)
				s1 = hasMoveFront(hand, r, s, idx);
			if (s1)
				return 1;
		}
		for (int r = 13; r >= 5; r--)
		{
			idx = 0;
			bool s2 = true;
			for (int c = 0; c < 5 && s2; c++)
				s2 = hasMoveFront(hand, r - c, s, idx);
			if (s2)
				return r;
		}
		return -1;
	}

	bool hasRoyalFlush(std::vector<Card>& hand)
	{
		int s = flushCheck(hand);
		if (s == -1)
			return false;
		return straightCheck(hand, s) == 1;
	}

	bool hasStraightFlush(std::vector<Card>& hand)
	{
		int s = flushCheck(hand);
		if (s == -1)
			return false;
		return straightCheck(hand, s) != -1;
	}

	bool hasFourKind(std::vector<Card>& hand)
	{
		int idx = 0;
		for (int ri = 14; ri >= 2; ri--)
		{
			idx = 0;
			int r = ri == 14 ? 1 : ri;
			if (hasSame(hand, idx, r, 4))
				return true;
		}
		return false;
	}

	bool hasFullHouse(std::vector<Card>& hand)
	{
		int idx = 0;
		bool three = false;
		for (int ri = 14; ri >= 2 && !three; ri--)
		{
			idx = 0;
			int r = ri == 14 ? 1 : ri;
			three = hasSame(hand, idx, r, 3);
		}
		if (!three)
			return false;
		int tempIdx = idx;
		for (int ri = 14; ri >= 2; ri--)
		{
			idx = tempIdx;
			int r = ri == 14 ? 1 : ri;
			if (hasSame(hand, idx, r, 2))
				return true;
		}
		return false;
	}

	bool hasFlush(std::vector<Card>& hand)
	{
		int idx = 0;
		int s = flushCheck(hand);
		if (s == -1)
			return false;
		for (int ri = 14; ri >= 2; ri--)
		{
			int r = ri == 14 ? 1 : ri;
			hasMoveFront(hand, r, s, idx);
		}
		return true;
	}

	bool hasStraight(std::vector<Card>& hand)
	{
		int idx = 0;
		if (hasMoveFront(hand, 1, idx))
		{
			bool s1 = true;
			for (int r = 13; r >= 10 && s1; r--)
				s1 = hasMoveFront(hand, r, idx);
			if (s1)
				return true;
		}
		for (int r = 13; r >= 5; r--)
		{
			idx = 0;
			bool s2 = true;
			for (int c = 0; c < 5 && s2; c++)
				s2 = hasMoveFront(hand, r - c, idx);
			if (s2)
				return true;
		}
		return false;
	}

	bool hasThreeKind(std::vector<Card>& hand)
	{
		int idx = 0;
		for (int ri = 14; ri >= 2; ri--)
		{
			idx = 0;
			int r = ri == 14 ? 1 : ri;
			if (hasSame(hand, idx, r, 3))
				return true;
		}
		return false;
	}

	bool hasTwoPair(std::vector<Card>& hand)
	{
		int idx = 0;
		int tempIdx = 0;
		int count = 0;
		for (int ri = 14; ri >= 2; ri--)
		{
			idx = tempIdx;;
			int r = ri == 14 ? 1 : ri;
			if (hasSame(hand, idx, r, 2))
			{
				count++;
				switch (count)
				{
				case 1:
					tempIdx = idx;
					break;
				case 2:
					return true;
				default:
					break;
				}
			}
		}
		return false;
	}

	bool hasPair(std::vector<Card>& hand)
	{
		int idx = 0;
		for (int ri = 14; ri >= 2; ri--)
		{
			idx = 0;
			int r = ri == 14 ? 1 : ri;
			if (hasSame(hand, idx, r, 2))
				return true;
		}
		return false;
	}

	void getBestHand(Player& current, std::vector<Card> community, int score[])
	{
		std::vector<Card> hand = mergeHands(current, community);

		std::cout << current.getName() + ": ";
		if (hasRoyalFlush(hand))
		{
			std::cout << "Royal flush." << std::endl;
			score[0] = 9;
		}
		else if (hasStraightFlush(hand))
		{
			std::cout << "Straight flush." << std::endl;
			score[0] = 8;
		}
		else if (hasFourKind(hand))
		{
			std::cout << "Four-of-a-kind." << std::endl;
			score[0] = 7;
			sortHand(hand, 4);
		}
		else if (hasFullHouse(hand))
		{
			std::cout << "Full house." << std::endl;
			score[0] = 6;
		}
		else if (hasFlush(hand))
		{
			std::cout << "Flush." << std::endl;
			score[0] = 5;
		}
		else if (hasStraight(hand))
		{
			std::cout << "Straight." << std::endl;
			score[0] = 4;
		}
		else if (hasThreeKind(hand))
		{
			std::cout << "Three-of-a-kind." << std::endl;
			score[0] = 3;
			sortHand(hand, 3);
		}
		else if (hasTwoPair(hand))
		{
			std::cout << "Two pair." << std::endl;
			score[0] = 2;
			sortHand(hand, 4);
		}
		else if (hasPair(hand))
		{
			std::cout << "Pair." << std::endl;
			score[0] = 1;
			sortHand(hand, 2);
		}
		else
		{
			std::cout << "High card." << std::endl;
			score[0] = 0;
			sortHand(hand, 0);
		}
		printHand(hand);

		for (int i = 1; i < 6; i++)
			score[i] = hand[i].rank == 1 ? 14 : hand[i].rank;
	}
}