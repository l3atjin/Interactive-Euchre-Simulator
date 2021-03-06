#include <cassert>
#include <iostream>
#include <string>
#include "Pack.h"
#include "Card.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include <cstring>
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
    int round = 0;
    int maxScore;
    unsigned int dealer = 0;
    int trick1 = 0;
    int trick2 = 0;
    int leader = 1;
    bool is1OrderUp = false;
    bool is2OrderUp = false;
    
public:
    Game(string name0_in, string type0_in,
         string name1_in, string type1_in,
         string name2_in, string type2_in,
         string name3_in, string type3_in,
         Pack deck_in, int score_in, string shuffle_in)
    : deck(deck_in), maxScore(score_in) {
        player0 = Player_factory(name0_in, type0_in);
        players.push_back(player0);
        player1 = Player_factory(name1_in, type1_in);
        players.push_back(player1);
        player2 = Player_factory(name2_in, type2_in);
        players.push_back(player2);
        player3 = Player_factory(name3_in, type3_in);
        players.push_back(player3);
    }
	int score1 = 0;
	int score2 = 0;
    
    bool isGameOver()
    {
        if (score1 >= maxScore || score2 >= maxScore)
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
		Card temp = deck.deal_one();
		cout << temp << " turned up" << endl;
        return temp;
    }
    
    vector<Player*> get_players()
    {
        return players;
    }
    
    void choose_trump(Card& upcard, string& trumpSuit)
    {
        bool isDealer = false;
        for (int i = 1; i < 3; i++)
        {
            for (unsigned int j = 1; j < players.size() + 1; j++)
            {
                if (((dealer + j) % 4) == dealer)
                {
                    isDealer = true;
                }
                if (players.at((dealer+j)%4)->make_trump(upcard, isDealer, i, trumpSuit))
                {
					cout << players.at((dealer + j) % 4)->get_name() 
						<< " orders up " << trumpSuit << endl;
	
					if (i == 1)
						players.at(dealer % 4)->add_and_discard(upcard);
                    if (((dealer + j) % 4) %2 == 0)
                        is1OrderUp = true;
                    else
                        is2OrderUp = true;
					cout << endl;
					i = 3;
                    break;
                }
				else
				{
					cout << players.at((dealer + j) % 4)->get_name() 
						<< " passes" << endl;
				}
            }
        }
    }
    
    void deal()
    {
		cout << players.at(dealer%4)->get_name() << " deals" << endl;
        for (int i = 0; i < 2; i++) {
            
            for (int j = 0; j < (3 - i); j++) {
                players.at((dealer + 1) % 4)->add_card(deck.deal_one());
            }
            
            
            for (int j = 0; j < (2 + i); j++) {
                players.at((dealer + 2) % 4)->add_card(deck.deal_one());
            }
            
            
            for (int j = 0; j < (3 - i); j++) {
                players.at((dealer + 3) % 4)->add_card(deck.deal_one());
            }
            
            
            for (int j = 0; j < (2 + i); j++) {
                players.at((dealer + 4) % 4)->add_card(deck.deal_one());
            }
        }
    }
    
    void reset(string isShuffle) {
        deck.reset();
		if (isShuffle == "shuffle")
		{
			deck.shuffle();
		}
        trick1 = 0;
        trick2 = 0;
        is1OrderUp = false;
        is2OrderUp = false;
        dealer++;
        leader = dealer + 1;
        round++;
    }
    
    int get_round()
    {
        return round;
    }
   
    void team2Win()
    {
        if (is2OrderUp && (trick2 == 3 || trick2 == 4))
        {
            score2++;
            cout << player1->get_name() <<
            " and " << player3->get_name()
            << " win the hand" << endl;
        }
        else if (is2OrderUp && trick2 == 5)
        {
            score2 += 2;
            cout << player1->get_name() <<
            " and " << player3->get_name()
            << " win the hand" << endl;
            cout << "march!" << endl;
        }
        else if (is1OrderUp)
        {
            score2 += 2;
            cout << player1->get_name() <<
            " and " << player3->get_name()
            << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
		cout << player0->get_name() <<
			" and " << player2->get_name()
			<< " have " << score1 
			<< " points" << endl;
		cout << player1->get_name() <<
			" and " << player3->get_name()
			<< " have " << score2
			<< " points" << endl;
		cout << endl;
    }
    
    void team1Win()
    {
        if (is1OrderUp && (trick1 == 3 || trick1 == 4))
        {
            score1++;
            cout << player0->get_name() <<
            " and " << player2->get_name()
            << " win the hand" << endl;
        }
        else if(is1OrderUp && trick1 == 5)
        {
            score1+=2;
            cout << player0->get_name() <<
            " and " << player2->get_name()
            << " win the hand" << endl;
            cout << "march!" << endl;
        }
        else if (is2OrderUp)
        {
            score1 += 2;
            cout << player0->get_name() <<
            " and " << player2->get_name()
            << " win the hand" << endl;
            cout << "euchred!" << endl;
        }
		cout << player0->get_name() <<
			" and " << player2->get_name()
			<< " have " << score1
			<< " points" << endl;
		cout << player1->get_name() <<
			" and " << player3->get_name()
			<< " have " << score2
			<< " points" << endl;
		cout << endl;
    }
    
    int get_maxScore()
    {
        return maxScore;
    }
    
    bool isWin1()
    {
        if (trick1 >= 3 && (trick1 + trick2) == 5)
        {
            return true;
        }
        return false;
    }
    
    bool isWin2()
    {
        if (trick2 >= 3 && (trick1 + trick2) == 5)
        {
            return true;
        }
        return false;
    }
    
    void play_trick(string trump)
    {
		Card led_card, played_card1, played_card2, played_card3;
        vector <Card> cards;
        cards.reserve(4);
        cards.resize(4); 
        Card winnerCard;
        int winner;
        while (!isWin1() && !isWin2())
        {
            led_card = players.at(leader % 4)->lead_card(trump);
			cout << led_card << " led by " 
				<< players.at(leader % 4)->get_name() << endl;
            winnerCard = led_card;
            cards.at(leader % 4) = led_card;
            winner = leader%4;
            
            played_card1 = players.at((leader + 1) % 4)->play_card(led_card, trump);
			cout << played_card1 << " played by " 
				<< players.at((leader + 1) % 4)->get_name() << endl;
            cards.at((leader + 1) % 4) = played_card1;
            if (Card_less(winnerCard, played_card1, led_card, trump))
            {
                winnerCard = played_card1;
                winner = (leader + 1) % 4;
            }
            played_card2 = players.at((leader + 2) % 4)->play_card(led_card, trump);
			cout << played_card2 << " played by " 
				<< players.at((leader + 2) % 4)->get_name() << endl;
            cards.at((leader + 2) % 4) = played_card2;
            if (Card_less(winnerCard, played_card2, led_card, trump))
            {
                winnerCard = played_card2;
                winner = (leader + 2) % 4;
            }
            played_card3 = players.at((leader + 3) % 4)->play_card(led_card, trump);
			cout << played_card3 << " played by " 
				<< players.at((leader + 3) % 4)->get_name() << endl;
            cards.at((leader + 3) % 4) = played_card3;
            if (Card_less(winnerCard, played_card3, led_card, trump))
            {
                winnerCard = played_card3;
                winner = (leader + 3) % 4;
            }
            leader = winner;
            if (winner%2 == 0)
                trick1++;
            else
                trick2++;

			cout << players.at(winner)->get_name() << " takes the trick" << endl;
			cout << endl;
        }
        if (isWin1())
            team1Win();
        else if(isWin2())
            team2Win();
    }
};

void print_exec(int size, char* array[]) {
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
	cout << endl;
}
bool isShuffle(string shuffle)
{
    if (shuffle == "shuffle")
    {
        return true;
    }
    return false;
}

bool checkInput(int argc, char* argv[])
{
	if (argc != 12)
	{
		return false;
	}
	if (strcmp(argv[2], "shuffle") != 0 && strcmp(argv[2], "noshuffle") != 0)
	{
		return false;
	}
	if (atoi(argv[3]) < 1 || atoi(argv[3]) > 100)
	{
		return false;
	}
	if (strcmp(argv[5], "Simple") != 0 && strcmp(argv[5], "Human") != 0)
	{
		return false;
	}
	if (strcmp(argv[7], "Simple") != 0 && strcmp(argv[7], "Human") != 0)
	{
		return false;
	}
	if (strcmp(argv[9], "Simple") != 0 && strcmp(argv[9], "Human") != 0)
	{
		return false;
	}
	if (strcmp(argv[11], "Simple") != 0 && strcmp(argv[11], "Human") != 0)
	{
		return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
    ifstream input(argv[1]);
    string input2 = argv[2];
    int gamePoint = atoi(argv[3]);
    if (!input.is_open()){
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
	if (!checkInput(argc, argv)){
		cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
			<< "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
			<< "NAME4 TYPE4" << endl;
		return 1;
	}
    Pack deck(input);
    Card upcard, trump;
    string trumpSuit;
    Game game(argv[4], argv[5], argv[6], argv[7], argv[8],
		argv[9], argv[10], argv[11], deck, gamePoint, input2);
    print_exec(argc, argv);
    if (isShuffle(input2)){
        game.shuffle();
    }
    while (!game.isGameOver()){
        cout << "Hand " << game.get_round() << endl;
        game.deal();
        upcard = game.make_upcard();
        game.choose_trump(upcard, trumpSuit);
        game.play_trick(trumpSuit);
        game.reset(input2);
    }
	if (game.score1 >= gamePoint)
		cout << argv[4] << " and " << argv[8] << " win!" << endl;
	else
		cout << argv[6] << " and " << argv[10] << " win!" << endl;
    for (int i = 0; i < int(game.get_players().size()); ++i){
        delete game.get_players().at(i);
    }
}
