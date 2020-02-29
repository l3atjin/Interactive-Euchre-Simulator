// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;

    Player* bobby = Player_factory("Bobby", "Human");
    ASSERT_EQUAL("Bobby", bobby->get_name());

    delete bobby;
}

// Add more tests here
TEST(test_add_card) {
    Player* alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card c2(Card::RANK_KING, Card::SUIT_CLUBS);
    alice->add_card(c);
    ASSERT_EQUAL(alice->lead_card("Hearts"), c);
    alice->add_card(c);
    alice->add_card(c);
    alice->add_card(c);
    alice->add_card(c2);
    ASSERT_EQUAL(alice->lead_card("Hearts"), c2);

    delete alice;
}

TEST(test_make_trump) {
    Player* bold = Player_factory("Bold", "Simple");
    Player* zulaa = Player_factory("Zulaa", "Simple");
    Player* saraa = Player_factory("Saraa", "Simple");
    Player* dorj = Player_factory("Dorj", "Simple");
    //the upcard
    Card c1("Ten", "Clubs");
    // the next upcard
    Card c1n("Ten", "Spades");
    //the left bower
    Card c2("Jack", "Spades");
    //second trump face card
    Card c3("Queen", "Clubs");
    Card c4("Ten", "Spades");
    Card c5("Nine", "Hearts");
    //not a bower
    Card c6("Jack", "Diamonds");
    //more trump cards
    Card c7("Ace", "Clubs");
    Card c8("Nine", "Clubs");
    Card c9("King", "Clubs");
    Card c10("Jack", "Clubs");
    Card c10n("Jack", "Spades");

    string order_up_suit = "Clubs";

    //testing with empty hand;
    ASSERT_FALSE(bold->make_trump(c6, false, 2, order_up_suit));
    
    bold->add_card(c2);
    bold->add_card(c3);
    bold->add_card(c4);
    bold->add_card(c5);
    bold->add_card(c6);
    
    //2 trumps (1 left bower and 1 face) returns true for all
    //dealer, round 1
    ASSERT_TRUE(bold->make_trump(c1, true, 1, order_up_suit));
    // round 2, dealer
    ASSERT_TRUE(bold->make_trump(c1n, true, 2, order_up_suit));
    // round 1, not dealer
    ASSERT_TRUE(bold->make_trump(c1, false, 1, order_up_suit));
    // round 2, not dealer
    ASSERT_TRUE(bold->make_trump(c1n, false, 2, order_up_suit));

    zulaa->add_card(c10);
    zulaa->add_card(c3);
    zulaa->add_card(c7);
    zulaa->add_card(c8);
    zulaa->add_card(c9);

    //all trumps, one of which is a right bower, true for all
    //round one, dealer
    ASSERT_TRUE(zulaa->make_trump(c1, true, 1, order_up_suit));
    //round one, non dealer
    ASSERT_TRUE(zulaa->make_trump(c1, false, 1, order_up_suit));
    //round two dealer
    ASSERT_TRUE(zulaa->make_trump(c1n, true, 2, order_up_suit));
    //round two non dealer
    ASSERT_TRUE(zulaa->make_trump(c1n, false, 2, order_up_suit));
    
    saraa->add_card(c8);
    saraa->add_card(c1);
    saraa->add_card(c4);
    saraa->add_card(c5);
    saraa->add_card(c6);

    //two trumps but none are face cards
    //dealer/round1
    ASSERT_FALSE(saraa->make_trump(c10, true, 1, order_up_suit));
    //round 2, screw the dealer
    ASSERT_TRUE(saraa->make_trump(c10n, true, 2, order_up_suit));
    //round 1, non dealer
    ASSERT_FALSE(saraa->make_trump(c10, false, 1, order_up_suit));
    // round 2, not dealer
    ASSERT_FALSE(saraa->make_trump(c10n, false, 2, order_up_suit));

    dorj->add_card(c8);
    dorj->add_card(c10);
    dorj->add_card(c4);
    dorj->add_card(c5);
    dorj->add_card(c6);
    
    //two trumps only one is face card
    ASSERT_FALSE(dorj->make_trump(c1, true, 1, order_up_suit));
    //in round 2 when dealer, and trump = 1
    ASSERT_TRUE(dorj->make_trump(c1n, true, 2, order_up_suit));
    //false when trump = 1, non dealer
    ASSERT_FALSE(dorj->make_trump(c1, false, 1, order_up_suit));
    //true when round 2, not dealer, 1 trump
    ASSERT_TRUE(dorj->make_trump(c1n, false, 2, order_up_suit));
    
    delete bold;
    delete zulaa;
    delete saraa;
    delete dorj;
}

TEST(test_add_and_discard) {
    Player* dorj = Player_factory("Dorj", "Simple");
    Player* bold = Player_factory("Bold", "Simple");
    Player* zulaa = Player_factory("Zulaa", "Simple");
    Player* saraa = Player_factory("Saraa", "Simple");
    Player* teneg = Player_factory("Teneg", "Simple");

    Card c0("Ten", "Clubs");
    Card c1("Ten", "Spades");
    Card c2("Jack", "Spades");
    Card c3("Queen", "Clubs");
    Card c4("Nine", "Clubs");
    Card c5("Nine", "Hearts");
    Card c6("Nine", "Diamonds");
    Card c7("Ace", "Clubs");
    Card c8("King", "Clubs");
    //test when card has one card
    dorj->add_card(c1);
   
    //after adding upcard c0, c1 should be discarded
    dorj->add_and_discard(c0);
    ASSERT_EQUAL(c0, dorj->lead_card("Clubs"));

    bold->add_card(c2);
    bold->add_card(c1);
   
    //c1 should be discarded again, second least card 
    bold->add_and_discard(c0);
    ASSERT_EQUAL(c2, bold->lead_card("Clubs"));
    ASSERT_EQUAL(c0, bold->lead_card("Clubs"));

    zulaa->add_card(c1);
    zulaa->add_card(c2);
    zulaa->add_card(c5);
    zulaa->add_card(c4);
    zulaa->add_card(c3);

	//zulaa->print_hand();
    //c5 should be discarded, c4 is trump  // lies
    zulaa->add_and_discard(c0);
	//zulaa->print_hand();
    ASSERT_EQUAL(c1, zulaa->lead_card("Clubs"));
    //checking that c0 is 3rd card after sorting/discarding;
    ASSERT_EQUAL(c2, zulaa->lead_card("Clubs"));
    ASSERT_EQUAL(c3, zulaa->lead_card("Clubs"));
    ASSERT_EQUAL(c0, zulaa->lead_card("Clubs"));
    ASSERT_EQUAL(c4, zulaa->lead_card("Clubs"));

    saraa->add_card(c1);
    saraa->add_card(c2);
    saraa->add_card(c6);
    saraa->add_card(c4);
    saraa->add_card(c5);
	//saraa->print_hand();

    //c5 should be discarded, c5 and c6 both nine, but c5 is hearts  
    saraa->add_and_discard(c0);
	//saraa->print_hand();
    ASSERT_EQUAL(c1, saraa->lead_card("Clubs"));
    //check that upcard is biggest now
    ASSERT_EQUAL(c6, saraa->lead_card("Clubs"));
    ASSERT_EQUAL(c2, saraa->lead_card("Clubs"));
    ASSERT_EQUAL(c0, saraa->lead_card("Clubs"));
    ASSERT_EQUAL(c4, saraa->lead_card("Clubs"));

    teneg->add_card(c0);
    teneg->add_card(c2);
    teneg->add_card(c7);
    teneg->add_card(c3);
    teneg->add_card(c8);
	//teneg->print_hand();

    teneg->add_and_discard(c4);
	//teneg->print_hand();

    //upcard should be discarded
    ASSERT_EQUAL(c2, teneg->lead_card("Clubs"));
    ASSERT_EQUAL(c7, teneg->lead_card("Clubs"));
    ASSERT_EQUAL(c8, teneg->lead_card("Clubs"));
    ASSERT_EQUAL(c3, teneg->lead_card("Clubs"));
    ASSERT_EQUAL(c0, teneg->lead_card("Clubs"));

    delete bold;
    delete zulaa;
    delete saraa;
    delete dorj;
    delete teneg;
}

TEST(test_lead_card) {
    Player* dorj = Player_factory("Dorj", "Simple");
    Player* bold = Player_factory("Bold", "Simple");
    Player* zulaa = Player_factory("Zulaa", "Simple");
    Player* saraa = Player_factory("Saraa", "Simple");
    Player* teneg = Player_factory("Teneg", "Simple");

    Card c1("Nine", "Spades");
    Card c2("Ten", "Spades");
    Card c3("Jack", "Spades");
    Card c4("Jack", "Clubs");
    Card c5("Ace", "Spades");
    Card c6("King", "Spades");
    Card c7("Ace", "Hearts");
    Card c8("Ace", "Diamonds");
    Card c9("Jack", "Diamonds");

    dorj->add_card(c1);
    dorj->add_card(c2);
    dorj->add_card(c3);
    dorj->add_card(c4);
    dorj->add_card(c5);
	//dorj->print_hand();
    ASSERT_EQUAL(c3, dorj->lead_card("Spades"));

    bold->add_card(c1);
    bold->add_card(c2);
    bold->add_card(c6);
    bold->add_card(c4);
    bold->add_card(c5);

    ASSERT_EQUAL(c4, bold->lead_card("Spades"));

    zulaa->add_card(c1);
    zulaa->add_card(c2);
    zulaa->add_card(c7);
    zulaa->add_card(c8);
	//zulaa->print_hand();
    ASSERT_EQUAL(c8, zulaa->lead_card("Spades"));

    saraa->add_card(c1);
	//saraa->print_hand();
    ASSERT_EQUAL(c1, saraa->lead_card("Spades"));

    teneg->add_card(c7);
    teneg->add_card(c9);
	//teneg->print_hand();

    ASSERT_EQUAL(c7, teneg->lead_card("Spades"));

    delete bold;
    delete zulaa;
    delete saraa;
    delete dorj;
    delete teneg;
}

TEST(test_play_card) {
    Player* dorj = Player_factory("Dorj", "Simple");
    Player* bold = Player_factory("Bold", "Simple");
    Player* zulaa = Player_factory("Zulaa", "Simple");
    Player* saraa = Player_factory("Saraa", "Simple");
    Player* teneg = Player_factory("Teneg", "Simple");
    Player* erguu = Player_factory("Erguu", "Simple");
    Player* niceguy = Player_factory("NiceGuy", "Simple");
    
    

    Card c0("Ten", "Hearts");
    Card c1("Nine", "Diamonds");
    Card c2("Ten", "Spades");
    Card c3("Ten", "Clubs");
    Card c4("King", "Spades");
    Card c5("Ace", "Spades");
    Card c6("Nine", "Hearts");
    Card c7("Ace", "Hearts");
    Card c8("King", "Diamonds");
    Card c9("Jack", "Clubs");

    dorj->add_card(c1);
    dorj->add_card(c2);
    dorj->add_card(c3);
    dorj->add_card(c4);
    dorj->add_card(c5);

	//dorj->print_hand("Diamonds");

    ASSERT_EQUAL(c2, dorj->play_card(c0, "Diamonds"));

    bold->add_card(c2);
    bold->add_card(c3);
    bold->add_card(c4);
	//bold->print_hand("Diamonds");
    
    ASSERT_EQUAL(c2, bold->play_card(c0, "Diamonds"));

    zulaa->add_card(c1);
    zulaa->add_card(c3);
    zulaa->add_card(c6);
	//zulaa->print_hand("Diamonds");
    ASSERT_EQUAL(c6, zulaa->play_card(c0, "Diamonds"));

    saraa->add_card(c6);
    saraa->add_card(c7);
    
    ASSERT_EQUAL(c7, saraa->play_card(c0, "Diamonds"));

    teneg->add_card(c1);
    teneg->add_card(c8);

    ASSERT_EQUAL(c1, teneg->play_card(c0, "Diamonds"));

    erguu->add_card(c2);
    erguu->add_card(c4);
    erguu->add_card(c5);

    ASSERT_EQUAL(c5, erguu->play_card(c2, "Spades"));

    niceguy->add_card(c5);
    niceguy->add_card(c9);

    ASSERT_EQUAL(c5, niceguy->play_card(c0, "Spades"));

    delete bold;
    delete zulaa;
    delete saraa;
    delete dorj;
    delete teneg;
    delete erguu;
	delete niceguy;
}

TEST_MAIN()
