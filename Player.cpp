
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Pack.h"
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

public:
	SimplePlayer()
	{}

	SimplePlayer(std::string name_in)
		: name(name_in) {}

	virtual std::vector<Card> get_hand()
	{
		return hand;
	}

	virtual void sort_hand(std::string trump) override
	{
		Card temp;
		for (unsigned int i = 0; i < 15; i++)
		{
			for (unsigned int j = 0; j < hand.size()-1; j++)
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
	//EFFECTS returns card at given index
	virtual Card get_card(int index) override
	{
		return hand.at(index);
	}

	virtual void print_hand(std::string trump) override
	{
		sort_hand(trump);
		for (unsigned int i = 0; i < hand.size(); i++)
		{
			std::cout << get_card(i) << std::endl;
		}
		std::cout << std::endl;
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
		if (round == 1) {

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
			hand.erase(hand.end());
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
			if (hand.at(i+1).is_trump(trump))
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
			if (hand.at(i).get_suit() == led_card.get_suit()) 
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

	class HumanPlayer : public Player {
	private:
		std::string name;
		// Maximum number of cards in a player's hand
		// *variable moved from public to private*
		static const int MAX_HAND_SIZE = 5;
		//hand of SimplePlayer
		std::vector<Card> hand;
		//bool islead;

	public:

		HumanPlayer()
		{}

		HumanPlayer(std::string name_in)
			: name(name_in) {}

		virtual void sort_hand(std::string trump) override
		{
			Card temp;
			for (unsigned int i = 0; i < 15; i++)
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

		

		virtual std::vector<Card> get_hand()
		{
			return hand;
		}

		//EFFECTS returns player's name
		virtual const std::string& get_name() const override {
			return name;
		}

		virtual Card get_card(int index) override
		{
			return hand.at(index);
		}

		virtual void print_hand(std::string trump) override
		{
			sort_hand(trump);
			for (unsigned int i = 0; i < hand.size(); i++)
			{
				std::cout << get_card(i) << std::endl;
			}
			std::cout << std::endl;
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
			std::vector<Card> temp;
			unsigned int index = 10;
			unsigned int count;
			for (unsigned int j = 0; j < 5; j++)
			{
				for (unsigned int i = 0; i < hand.size(); i++)
				{
					if (j == index)
					{
						continue;
					}
					if (hand.at(j) < hand.at(i))
					{
						count++;
					}
				}
				if (count == (4 - j))
				{
					temp.push_back(hand.at(j));
					index = j;
				}
			}

			if (round == 1)
			{
				for (unsigned int i = 0; i < hand.size(); i++)
				{
					std::cout << "Human player Judea's hand: ["
						<< i << "]" << temp.at(i) << std::endl;
				}
				std::cout << "Human player " //<< this->get_name()
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
				if (is_dealer)
				{
					order_up_suit = Suit_next(upcard.get_suit());
					return true;
				}
				for (unsigned int i = 0; i < hand.size() ; i++)
				{
					std::cout << "Human player Judea's hand: ["
						<< i << "]" << hand.at(i) << std::endl;
				}
				std::cout << "Human player " << this->get_name()
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
			sort_hand(upcard.get_suit());
			for (unsigned int i = 0; i < hand.size(); i++)
			{
				std::cout << "Human player Judea's hand: ["
					<< i << "]" << hand.at(i) << std::endl;
			}
			std::cout << "Discard upcard: [-1]" << std::endl;
			std::cout << "Human player " << this->get_name()
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
			std::sort(hand.begin(), hand.end());
			int index;
			Card temp;
			for (unsigned int i = 0; i < hand.size(); i++)
			{
				std::cout << "Human player Judea's hand: ["
					<< i << "]" << hand.at(i) << std::endl;
			}
			std::cout << "Discard upcard: [-1]" << std::endl;
			std::cout << "Human player " << this->get_name()
				<< ", please select a card:" << std::endl;
			std::cin >> decision;
			index = std::stoi(decision);
			std::cout << hand.at(index) << "led by " << this->get_name() << std::endl;
			temp = hand.at(index);
			hand.erase(hand.begin() + index);
			return temp;
		}

		//REQUIRES Player has at least one card, trump is a valid suit
		//EFFECTS  Plays one Card from Player's hand according to their strategy.
		//  The card is removed from the player's hand.
		virtual Card play_card(const Card& led_card, const std::string& trump) override {
			std::string decision;
			std::sort(hand.begin(), hand.end());
			Card temp;
			int index;
			for (unsigned int i = 0; i < hand.size(); i++)
			{
				std::cout << "Human player Judea's hand: ["
					<< i << "]" << hand.at(i) << std::endl;
			}
			std::cout << "Discard upcard: [-1]" << std::endl;
			std::cout << "Human player " << this->get_name()
				<< ", please select a card:" << std::endl;
			std::cin >> decision;
			index = std::stoi(decision);
			std::cout << hand.at(index) << "played by " << this->get_name() << std::endl;
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
