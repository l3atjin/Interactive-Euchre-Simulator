// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card()
	: rank(RANK_TWO), suit(SUIT_SPADES) { }

Card::Card(const std::string &rank_in, const std::string &suit_in)
	: rank(rank_in), suit(suit_in) { }

//EFFECTS Returns the rank
std::string Card::get_rank() const
{
	return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const
{
	return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string& trump) const
{
	
	if (this->is_left_bower(trump))
	{
		return trump;
	}
	return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const
{
	if (this->get_rank() == RANK_JACK 
		|| this->get_rank() == RANK_QUEEN
		|| this->get_rank() == RANK_KING
		|| this->get_rank() == RANK_ACE)
	{
		return true;
	}
	return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string& trump) const
{
	if (rank == RANK_JACK && suit == trump)
	{
		return true;
	}
	return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string& trump) const
{
	if (suit == Suit_next(trump) && rank == RANK_JACK)
	{
		return true;
	}
	return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string& trump) const
{
	if (this->get_suit() == trump)
	{
		return true;
	}
	else if (this->is_left_bower(trump))
	{
		return true;
	}
	return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card& lhs, const Card& rhs)
{
	int lhs_rank;
	int rhs_rank;
	int lhs_suit;
	int rhs_suit;
	for (int i = 0; i < NUM_RANKS; i++)
	{
		if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
			lhs_rank = i;
		}
		if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
			rhs_rank = i;
		}
	}

	for (int i = 0; i < NUM_SUITS; i++)
	{
		if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
			lhs_suit = i;
		}
		if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
			rhs_suit = i;
		}
	}
	if (lhs_rank == rhs_rank)
	{
		if (lhs_suit < rhs_suit)
		{
			return true;
		}
		else if (lhs_suit == rhs_suit)
		{
			return false;
		}
		return false;
	}
	else if (lhs_rank < rhs_rank) {
		return true;
	}
	return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card& lhs, const Card& rhs)
{
	int lhs_rank;
	int rhs_rank;
	int lhs_suit;
	int rhs_suit;
	for (int i = 0; i < NUM_RANKS; i++)
	{
		if (RANK_NAMES_BY_WEIGHT[i] == lhs.get_rank()) {
			lhs_rank = i;
		}
		if (RANK_NAMES_BY_WEIGHT[i] == rhs.get_rank()) {
			rhs_rank = i;
		}
	}

	for (int i = 0; i < NUM_SUITS; i++)
	{
		if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
			lhs_suit = i;
		}
		if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
			rhs_suit = i;
		}
	}
	if (lhs_rank == rhs_rank)
	{
		if (lhs_suit < rhs_suit)
		{
			return false;
		}
		else if (lhs_suit == rhs_suit)
		{
			return false;
		}
		return true;
	}
	else if (lhs_rank < rhs_rank) {
		return false;
	}
	return true;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs)
{
	if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit())
	{
		return true;
	}
	return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs)
{
	if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit())
	{
		return false;
	}
	return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string& suit)
{
	if (suit == Card::SUIT_SPADES)
	{
		return Card::SUIT_CLUBS;
	}
	else if (suit == Card::SUIT_CLUBS)
	{
		return Card::SUIT_SPADES;
	}
	else if (suit == Card::SUIT_DIAMONDS)
	{
		return Card::SUIT_HEARTS;
	}
	return Card::SUIT_DIAMONDS;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.get_rank() << " of " << card.get_suit();
	return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const std::string& trump)
{
	if (b.is_right_bower(trump))
	{
		return true;
	}
	else if (a.is_right_bower(trump))
	{
		return false;
	}
	else if (a.is_left_bower(trump) && !b.is_right_bower(trump))
	{
		return false;
	}
	else if (a.is_left_bower(trump) && b.is_right_bower(trump))
	{
		return true;
	}
	else if (b.is_left_bower(trump))
	{
		return true;
	}
	else if (a.is_trump(trump) && !b.is_trump(trump))
	{
		return false;
	}
	else if (!a.is_trump(trump) && b.is_trump(trump))
	{
		return true;
	}
	else if (a.is_trump(trump) && b.is_trump(trump))
	{
		if (a < b)
		{
			return true;
		}
		else return false;
	}
	else if (a < b)
	{
		return true;
	}
	return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card,
	const std::string& trump)
{
	std::string led_suit = led_card.get_suit();
	if (b.is_right_bower(trump))
	{
		return true;
	}
	else if (a.is_right_bower(trump))
	{
		return false;
	}
	else if (a.is_left_bower(trump) && !b.is_right_bower(trump))
	{
		return false;
	}
	else if (a.is_left_bower(trump) && b.is_right_bower(trump))
	{
		return true;
	}
	else if (b.is_left_bower(trump))
	{
		return true;
	}
	if (a.is_trump(trump) && !b.is_trump(trump))
	{
		return false;
	}
	else if (!a.is_trump(trump) && b.is_trump(trump))
	{
		return true;
	}
	else if (a.is_trump(trump) && b.is_trump(trump))
	{
		if (a < b)
		{
			return true;
		}
		else return false;
	}
	else if (a.is_trump(led_suit) && !b.is_trump(led_suit))
	{
		return false;
	}
	else if (!a.is_trump(led_suit) && b.is_trump(led_suit))
	{
		return true;
	}
	else if (a.is_trump(led_suit) && b.is_trump(led_suit))
	{
		if (a < b)
		{
			return true;
		}
		else return false;
	}
	else if (a < b)
	{
		return true;
	}
	return false;
}
