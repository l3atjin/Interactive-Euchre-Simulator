
#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"


Pack::Pack()
//index of the card
	: next(0) {	
	int n = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j < 13; j++) {
            cards[n] = Card(RANK_NAMES_BY_WEIGHT[j], SUIT_NAMES_BY_WEIGHT[i]);
            n++;
        }
    }
}

Pack::Pack(std::istream& pack_input)
	: next(0) {
    std::string Rank;
    std::string Suit;
    std::string temp;

    for (int i = 0; i < 24; i++) {
        pack_input >> Rank;
        pack_input >> temp;
        pack_input >> Suit;
        cards[i] = Card(Rank, Suit);
    }
}

Card Pack::deal_one() {
	int temp = next;
	next++;
    return cards[temp];
}

void Pack::reset() {
	this->next = 0;
}

void Pack::shuffle() {
	for (int j = 0; j < 7; j++)
	{
		Card temp1[12];
		for (int i = 0; i < 12; i++)
		{
			temp1[i] = cards[i];
		}

		Card temp2[12];
		for (int i = 0; i < 12; i++)
		{
			temp2[i] = cards[i + 12.0];
		}
		int count = 0;
		for (int i = 0; i < PACK_SIZE; i++)
		{
			if (i % 2 == 0)
			{
				cards[i] = temp2[i / 2];
			}
			else
			{
				cards[i] = temp1[count];
				count++;
			}
		}
	}
}

bool Pack::empty() const {
    if (next == 24) {
        return true;
    }
    return false;
}



