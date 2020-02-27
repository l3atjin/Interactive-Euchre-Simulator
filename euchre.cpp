
#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;



class Game {
private:
	Player* player0;
	Player* player1;
	Player* player2;
	Player* player3;
	vector<Player*> players;
	Pack deck;
	int round;
	int score1;
	int score2;
	int maxScore;
	int dealer;
	int trick1;
	int trick2;
	int leader;
	bool orderedUp;

public:
	Game(string name0_in, string type0_in,
		string name1_in, string type1_in,
		string name2_in, string type2_in,
		string name3_in, string type3_in,
		Pack deck_in, int score_in, string shuffle_in)
		: score1(0), score2(0), round(0),
		dealer(0), trick1(0), trick2(0),
		leader(1),
		deck(deck_in), maxScore(score_in) {
		player0 = Player_factory(name0_in, type0_in);
		players.push_back(player0);
		player1 = Player_factory(name1_in, type1_in);
		players.push_back(player1);
		player2 = Player_factory(name2_in, type2_in);
		players.push_back(player2);
		player3 = Player_factory(name3_in, type3_in);
		players.push_back(player3);
	}
	bool isGameOver()
	{
		if (score1 == maxScore || score2 == maxScore)
		{
			return true;
		}
		return false;
	}


	void shuffle()
	{
		deck.shuffle();
	}

	Card make_upcard()
	{
		deck.deal_one();
	}

	void set_leader(int index)
	{
		leader = index;
	}

	void choose_trump(const Card& upcard, string& trumpSuit)
	{
		bool isDealer = false;
		for (int j = 0; j < 2; j++)
		{
			for (unsigned int i = 0; i < players.size(); i++)
			{
				if (i == dealer)
				{
					isDealer = true;
				}
				if (players.at(i)->make_trump(upcard, isDealer, j, trumpSuit))
				{

					break;
				}
			}
		}
	}

	void deal()
	{
		for (int i = 0; i < 2; i++)
		{
			players.at((dealer + 1) % 4)->add_cards(deck, 3 - i);
			players.at((dealer + 2) % 4)->add_cards(deck, 2 + i);
			players.at((dealer + 3) % 4)->add_cards(deck, 3 - i);
			players.at((dealer + 4) % 4)->add_cards(deck, 2 + i);
		}
	}

	void reset() {
		deck.reset();
		deck.shuffle();
	}

	int get_round()
	{
		return round;
	}

	Pack get_deck()
	{
		return deck;
	}

	int get_score2()
	{
		return score2;
	}

	void team2Win()
	{
		score2++;
		cout << player1->get_name() <<
			" and " << player3->get_name()
			<< " win the hand" << endl;
	}

	int get_score1()
	{
		return score1;
	}

	void team1Win()
	{

		score1++;
		cout << player0->get_name() <<
			" and " << player2->get_name()
			<< " win the hand" << endl;
	}

	int get_maxScore()
	{
		return maxScore;
	}

	void set_round()
	{
		round++;
	}

	bool isWin1()
	{
		if (trick1 >= 3)
		{
			return true;
		}
	}

	bool isWin2()
	{
		if (trick2 >= 3)
		{
			return true;
		}
	}

	int find_Winner(vector<Card> cards, string trump)
	{
		Card max = cards.at(0);
		int index;
		for (unsigned int i = 0; i < cards.size()-1; i++)
		{
			if (max < cards.at(0))
			{
				max = cards.at(0);
				index = i;
			}
		}
		return index;
	}

	void play_trick(string trump)
	{
		Card led_card;
		Card played_card1;
		Card played_card2;
		Card played_card3;
		vector <Card> cards;
		int winner;

		while (!isWin1 && !isWin2)
		{
			led_card = players.at(leader % 4)->lead_card(trump);
			cards.at(leader % 4) = led_card;
			played_card1 = players.at((leader + 1) % 4)->play_card(led_card, trump);
			cards.at((leader + 1) % 4) = played_card1;
			played_card2 = players.at((leader + 2) % 4)->play_card(led_card, trump);
			cards.at((leader + 1) % 4) = played_card2;
			played_card3 = players.at((leader + 3) % 4)->play_card(led_card, trump);
			cards.at((leader + 1) % 4) = played_card3;
			winner = find_Winner(cards, trump);
			leader = winner;
			if (winner%2 == 0)
			{
				trick1++;
			}
			else
			{
				trick2++;
			}
		}
		if (isWin1)
		{
			team1Win();
		}
		else {
			team2Win();
		}
	}
};

void print_exec(int size, char* array[]) {
	for (unsigned int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
}
bool isShuffle(string shuffle)
{
	if (shuffle == "shuffle")
	{
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Error opening " << argv[1] << endl;
		return 1;
	}

	Pack deck(input);
	Card upcard, trump;
	string trumpSuit;

	Game game(argv[4], argv[5], argv[6], argv[7], argv[8],
		argv[9], argv[10], argv[11], deck, atoi(argv[11]));

	print_exec(argc, argv);
	game.shuffle();
	while (!game.isGameOver())
	{
		cout << "Hand " << game.get_round() << endl;
		game.deal();
		upcard = game.make_upcard();
		game.choose_trump(upcard, trumpSuit);
		game.play_trick(trumpSuit);



	}

	for (int i = 0; i < int(players.size()); ++i) 
	{
		delete players[i];
	}

	return 0;
}