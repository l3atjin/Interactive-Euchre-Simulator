#ifndef CARD_H
#define CARD_H
/* Card.h
 *
 * Represents a single playing card
 * Project UID 1d9f47bfc76643019cfbf037641defe1
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2014-12-21
 */

#include <iostream>
#include <string>


class Card {
public:
  // rank and suit names
  static constexpr const char* const RANK_TWO = "Two";
  static constexpr const char* const RANK_THREE = "Three";
  static constexpr const char* const RANK_FOUR = "Four";
  static constexpr const char* const RANK_FIVE = "Five";
  static constexpr const char* const RANK_SIX = "Six";
  static constexpr const char* const RANK_SEVEN = "Seven";
  static constexpr const char* const RANK_EIGHT = "Eight";
  static constexpr const char* const RANK_NINE = "Nine";
  static constexpr const char* const RANK_TEN = "Ten";
  static constexpr const char* const RANK_JACK = "Jack";
  static constexpr const char* const RANK_QUEEN = "Queen";
  static constexpr const char* const RANK_KING = "King";
  static constexpr const char* const RANK_ACE = "Ace";

  static constexpr const char* const SUIT_SPADES = "Spades";
  static constexpr const char* const SUIT_HEARTS = "Hearts";
  static constexpr const char* const SUIT_CLUBS = "Clubs";
  static constexpr const char* const SUIT_DIAMONDS = "Diamonds";

  //EFFECTS Initializes Card to the Two of Spades
  Card();

  //REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
  //  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
  //  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
  //EFFECTS Initializes Card to specified rank and suit
  Card(const std::string &rank_in, const std::string &suit_in);

  //EFFECTS Returns the rank
  std::string get_rank() const;

  //EFFECTS Returns the suit.  Does not consider trump.
  std::string get_suit() const;

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  std::string get_suit(const std::string &trump) const;

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool is_face() const;

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool is_right_bower(const std::string &trump) const;

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool is_left_bower(const std::string &trump) const;

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool is_trump(const std::string &trump) const;

private:
  std::string rank;
  std::string suit;
};

// Suits in order from lowest suit to highest suit.
constexpr const char* const SUIT_NAMES_BY_WEIGHT[] = {
  Card::SUIT_SPADES,
  Card::SUIT_HEARTS,
  Card::SUIT_CLUBS,
  Card::SUIT_DIAMONDS
};
const int NUM_SUITS = 4;

// Ranks in order from lowest rank to highest rank.
constexpr const char* const RANK_NAMES_BY_WEIGHT[] = {
  Card::RANK_TWO,
  Card::RANK_THREE,
  Card::RANK_FOUR,
  Card::RANK_FIVE,
  Card::RANK_SIX,
  Card::RANK_SEVEN,
  Card::RANK_EIGHT,
  Card::RANK_NINE,
  Card::RANK_TEN,
  Card::RANK_JACK,
  Card::RANK_QUEEN,
  Card::RANK_KING,
  Card::RANK_ACE
};
const int NUM_RANKS = 13;

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs);

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs);

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit);

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card);

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump);

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump);

#endif
