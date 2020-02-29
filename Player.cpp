
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Player.h"


class SimplePlayer : public Player {
private:
	std::string name;
	// Maximum number of cards in a player's hand
	// *variable moved from public to private*
	static const int MAX_HAND_SIZE = 5;
	//hand of SimplePlayer
	std::vector<Card> hand;


	void sort_hand(std::string trump)
	{
		Card temp;
			
		for (unsigned int i = 0; i < 21; i++)
		{
			for (unsigned int j = 0; j < hand.size() - 1; j++)
			{
				if (!Card_less(hand.at(j), hand.at(j + 1), trump))
				{
					temp = hand.at(j + 1);
					hand.at(j + 1) = hand.at(j);
					hand.at(j) = temp;
				}
			}
		}
	}


	/*void print_hand(std::string trump)
	{
		sort_hand(trump);
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			std::cout << hand.at(i) << std::endl;
		}
		std::cout << std::endl;
	}*/

public:
	SimplePlayer()
	{}

	SimplePlayer(std::string name_in)
		: name(name_in) {}

	virtual std::vector<Card> get_hand()
	{
		return hand;
	}

	//EFFECTS returns player's name
	// *SHOULD CONST BE THERE???????*
	virtual const std::string& get_name() const override {
		return name;
	}

	//REQUIRES player has less than MAX_HAND_SIZE cards
	//EFFECTS  adds Card c to Player's hand
	virtual void add_card(const Card& c) override {
		hand.push_back(c);
	}

	
	//REQUIRES round is 1 or 2
	//MODIFIES order_up_suit
	//EFFECTS If Player wishes to order up a trump suit then return true and
	//  change order_up_suit to desired suit.  If Player wishes to pass, then do
	//  not modify order_up_suit and return false.
	virtual bool make_trump(const Card& upcard, bool is_dealer,
		int round, std::string& order_up_suit) const override {
		int trumpCount = 0;
		if (is_dealer && round == 2)
		{
			order_up_suit = Suit_next(upcard.get_suit());
			return true;
		}
		else if (round == 1) {

			//*hand.size() or MAX_HAND_SIZE?*
			for (unsigned int i = 0; i < hand.size(); i++) {
				//Check if each card in hand is a trump face card
				if ((hand[i]).is_face() && hand[i].is_trump(upcard.get_suit())) {
					trumpCount++;
				}
			}
			if (trumpCount >= 2) {
				// ordering up if 2 or more trump face card
				order_up_suit = upcard.get_suit();
				return true;
			}
			else {
				return false;
			}
		}
		else if (round == 2) {
			for (unsigned int i = 0; i < hand.size(); i++) {
				//Check if each card in hand is a trump face card
				if ((hand[i]).is_face() &&
					hand[i].is_trump(Suit_next(upcard.get_suit()))) {
					trumpCount++;
				}
			}
			if (!is_dealer && (trumpCount >= 1)) {
				order_up_suit = Suit_next(upcard.get_suit());
				return true;
			}
			else if (!is_dealer) {
				return false;
			}
			else {
				order_up_suit = Suit_next(upcard.get_suit());
				return true;
			}
		}
		//?
		return false;
	}

	//REQUIRES Player has at least one card
	//EFFECTS  Player adds one card to hand and removes one card from hand.
	virtual void add_and_discard(const Card& upcard) override {
		//adding the card to hand
		hand.push_back(upcard);
		//sorting the cards
		sort_hand(upcard.get_suit());
		hand.erase(hand.begin());
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Leads one Card from Player's hand according to their strategy
	//  "Lead" means to play the first Card in a trick.  The card
	//  is removed the player's hand.
	virtual Card lead_card(const std::string& trump) override {
		//unsigned int count = 0;
		Card temp;
		sort_hand(trump);

		if (hand.at(0).is_trump(trump))
		{
			temp = hand.at(hand.size() - 1);
			hand.erase(hand.begin() + hand.size() - 1);
			return temp;
		}

		for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (i == hand.size()-1)
			{
				temp = hand.at(i);
				hand.erase(hand.begin() + i);
				return temp;
			}
			if (hand.at(i + 1.0).is_trump(trump))
			{
				temp = hand.at(i);
				hand.erase(hand.begin() + i);
				return temp;
			}
		}

		/*for (unsigned int i = 0; i < hand.size(); i++)
		{
			if (hand.at(i).is_trump(trump))
			{
				count++;
			}
		}
		if (count == hand.size())
		{
			temp = hand.at(hand.size() - 1);
			hand.erase(hand.end());
			return temp;
		}
		else
		{
			for (int i = hand.size()-1; i >= 0; i--)
			{
				if (!hand.at(i).is_trump(trump))
				{
					temp = hand.at(0);
					hand.erase(hand.begin() + i);
					return temp;
				}
			}
		}*/
		return temp;
	}

	//REQUIRES Player has at least one card, trump is a valid suit
	//EFFECTS  Plays one Card from Player's hand according to their strategy.
	//  The card is removed from the player's hand.
	virtual Card play_card(const Card& led_card, const std::string& trump)
		override {
		Card c;
		sort_hand(trump);
		// decrement this
		for (int i = hand.size()-1; i > 0; i--) {
			if (led_card.is_left_bower(trump))
			{
				if (hand.at(hand.size() - 1).is_trump(trump))
				{
					c = hand.at(i);
					hand.erase(hand.begin() + i);
					return c;
				}
				else
				{
					c = hand.at(0);
					hand.erase(hand.begin()+0);
					return c;
				}
			}
			else if ((hand.at(i).get_suit() == led_card.get_suit() 
				&& !hand.at(i).is_left_bower(trump)) 
				|| (hand.at(i).is_left_bower(trump) 
					&& trump == led_card.get_suit()))
			{
				c = hand.at(i);
				hand.erase(hand.begin() + i);
				return c;
			}
		}
		// if none of the cards match the suit, return the last/lowest card
		c = hand.at(0);
		hand.erase(hand.begin());
		return c;
	}

	//Needed to avoid some compiler errors 
	// is this right?
	~SimplePlayer() {}
};
	void print_hand(std::vector<Card> hand, std::string name)
	{
		std::vector<Card> copy = hand;
		std::sort(copy.begin(), copy.end());
		for (unsigned int i = 0; i < copy.size(); i++)
		{
			std::cout << "Human player " << name << "'s hand: ["
				<< i << "] " << copy.at(i) << std::endl;
		}
		//std::cout << std::endl;
	}
	class HumanPlayer : public Player {
	private:
		std::string name;
		// Maximum number of cards in a player's hand
		// *variable moved from public to private*
		static const int MAX_HAND_SIZE = 5;
		//hand of SimplePlayer
		std::vector<Card> hand;
		//bool islead;

		void sort_hand(std::string trump)
		{
			Card temp;
			for (unsigned int i = 0; i < 15; i++)
			{
				for (unsigned int j = 0; j < hand.size() - 1; j++)
				{
					if (!Card_less(hand.at(j), hand.at(j + 1.0), trump))
					{
						temp = hand.at(j + 1.0);
						hand.at(j + 1.0) = hand.at(j);
						hand.at(j) = temp;
					}
				}
			}
		}


		//Card get_card(int index)
		//{
		//	return hand.at(index);
		//}

		//void print_hand(std::string trump)
		//{
		//	sort_hand(trump);
		//	for (unsigned int i = 0; i < hand.size(); i++)
		//	{
		//		std::cout << get_card(i) << std::endl;
		//	}
		//	std::cout << std::endl;
		//}

	public:

		HumanPlayer()
		{}

		HumanPlayer(std::string name_in)
			: name(name_in) {}

		
		

		virtual std::vector<Card> get_hand()
		{
			return hand;
		}

		//EFFECTS returns player's name
		virtual const std::string& get_name() const override {
			return name;
		}

		

		//REQUIRES player has less than MAX_HAND_SIZE cards
		//EFFECTS  adds Card c to Player's hand
		virtual void add_card(const Card& c) override {
			hand.push_back(c);
		}


		//REQUIRES round is 1 or 2
		//MODIFIES order_up_suit
		//EFFECTS If Player wishes to order up a trump suit then return true and
		//  change order_up_suit to desired suit.  If Player wishes to pass, then do
		//  not modify order_up_suit and return false.
		virtual bool make_trump(const Card& upcard, bool is_dealer,
			int round, std::string& order_up_suit) const override {
			std::string decision;

			if (is_dealer && round == 2)
			{
				print_hand(hand, name);
				std::cout << "Human player " << name
					<< ", please enter a suit, or \"pass\":" << std::endl;
				std::cin >> decision;
				order_up_suit = decision;
				return true;
			}

			else if (round == 1)
			{
				/*for (unsigned int i = 0; i < hand.size(); i++)
				{pas
					std::cout << "Human player " << name << "'s hand: ["
						<< i << "]" << hand.at(i) << std::endl;
				}*/
				print_hand(hand, name);
				std::cout << "Human player " << name
					<< ", please enter a suit, or \"pass\":" << std::endl;
					std::cin >> decision;
				if (decision == "pass")
				{
					return false;
				}
				else
				{
					order_up_suit = upcard.get_suit();
					return true;
				}
			}
			else if (round == 2)
			{
				print_hand(hand, name);
				std::cout << "Human player " << name
					<< ", please enter a suit, or \"pass\":" << std::endl;
				std::cin >> decision;
				
				if (decision == "pass")
				{
					return false;
				}
				else
				{
					order_up_suit = decision;
					return true;
				}
			}
			return true;
		}

		//REQUIRES Player has at least one card
		//EFFECTS  Player adds one card to hand and removes one card from hand.
		virtual void add_and_discard(const Card& upcard) override {
			std::string decision;
			print_hand(hand, name);
			std::cout << "Discard upcard: [-1]" << std::endl;
			std::sort(hand.begin(), hand.end());
			std::cout << "Human player " << name
				<< ", please select a card to discard:" << std::endl;
			std::cin >> decision;
			int index = std::stoi(decision);
			if (index >= 0)
			{
				hand.erase(hand.begin() + index);
				hand.push_back(upcard);
			}
		}

		//REQUIRES Player has at least one card, trump is a valid suit
		//EFFECTS  Leads one Card from Player's hand according to their strategy
		//  "Lead" means to play the first Card in a trick.  The card
		//  is removed the player's hand.
		virtual Card lead_card(const std::string& trump) override {
			std::string decision;
			print_hand(hand, name);
			std::sort(hand.begin(), hand.end());
			int index;
			Card temp;
			std::cout << "Human player " << name
				<< ", please select a card:" << std::endl;
			std::cin >> decision;
			index = std::stoi(decision);
			temp = hand.at(index);
			hand.erase(hand.begin() + index);
			return temp;
		}

		//REQUIRES Player has at least one card, trump is a valid suit
		//EFFECTS  Plays one Card from Player's hand according to their strategy.
		//  The card is removed from the player's hand.
		virtual Card play_card(const Card& led_card, const std::string& trump) override {
			std::string decision;
			print_hand(hand, name);
			std::sort(hand.begin(), hand.end());
			Card temp;
			int index;
			std::cout << "Human player " << name
				<< ", please select a card:" << std::endl;
			std::cin >> decision;
			index = std::stoi(decision);
			temp = hand.at(index);
			hand.erase(hand.begin() + index);
			return temp;
		}

		// Maximum number of cards in a player's hand
		// is in private
		//static const int MAX_HAND_SIZE = 5;

		// Needed to avoid some compiler errors
		//??????????
		~HumanPlayer() {}
	};


	Player* Player_factory(const std::string& name, const std::string& strategy) {

		if (strategy == "Simple") {
			return new SimplePlayer(name);
		}
		if (strategy == "Human") {
			return new HumanPlayer(name);
		}
		assert(false);
		return nullptr;
	}

	std::ostream& operator<<(std::ostream& os, const Player& p) {
		os << p.get_name();
		return os;
	}
