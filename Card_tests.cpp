// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card c1(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_QUEEN, c1.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, c1.get_suit());
}

// Add more test cases here

TEST(test_card_ctor_default) {
    // FIX DEFAULT constructor
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());

}

TEST(test_get_rank) {
    // fix
    /*Card c();
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    */
    Card c1(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_JACK, c1.get_rank());

    Card c3("Nine", "Clubs");
        ASSERT_EQUAL(Card::RANK_NINE, c3.get_rank());

}

TEST(test_get_suit) {
    // fix
    /*Card c();
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
*/
    Card c1("Ace", "Diamonds");
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c1.get_suit());

    Card c2(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::RANK_TEN, c2.get_rank());
}

TEST(test_get_suit_trump) {
    Card c(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit(Card::SUIT_SPADES));

    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(Card::SUIT_SPADES, c1.get_suit(Card::SUIT_SPADES));
    
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c2.get_suit(Card::SUIT_CLUBS));


    Card c3(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c3.get_suit(Card::SUIT_DIAMONDS));

}

TEST(test_is_face) {
    Card c(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_face());

    Card c1(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_TRUE(c1.is_face());

    Card c2(Card::RANK_KING, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_face());

}

TEST(test_is_right_bower) {
    Card c(Card::RANK_EIGHT, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_right_bower(Card::SUIT_SPADES));

    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c1.is_right_bower(Card::SUIT_DIAMONDS));

    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_right_bower(Card::SUIT_SPADES));

    Card c3(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_FALSE(c3.is_right_bower(Card::SUIT_DIAMONDS));

}

TEST(test_is_left_bower) {
    
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_left_bower(Card::SUIT_DIAMONDS));

    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c1.is_left_bower(Card::SUIT_CLUBS));

    Card c2(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_FALSE(c2.is_left_bower(Card::SUIT_DIAMONDS));

}

TEST(test_is_trump) {

    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_FALSE(c.is_trump(Card::SUIT_DIAMONDS));

    Card c1(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c1.is_trump(Card::SUIT_CLUBS));

    Card c2(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_TRUE(c2.is_trump(Card::SUIT_SPADES));

    Card c3(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(c3.is_trump(Card::SUIT_DIAMONDS));

}

TEST(test_operator_less) {
    Card cl(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_TRUE(operator<(cl, cr));

    Card cl1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr1(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(operator<(cl1, cr1));

    Card cl2(Card::RANK_ACE, Card::SUIT_SPADES);
    Card cr2(Card::RANK_TWO, Card::SUIT_SPADES);

    ASSERT_FALSE(operator<(cl2, cr2));

    Card cl3(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr3(Card::RANK_KING, Card::SUIT_SPADES);

    ASSERT_TRUE(operator<(cl3, cr3));

    Card cl4(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr4(Card::RANK_TWO, Card::SUIT_HEARTS);

    ASSERT_TRUE(operator<(cl4, cr4));

    Card cl5(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card cr5(Card::RANK_KING, Card::SUIT_HEARTS);

    ASSERT_FALSE(operator<(cl5, cr5));

    Card cl6(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr6(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(operator<(cl6, cr6));
}

TEST(test_operator_more) {

    Card cl(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(operator>(cl, cr));

    Card cl1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr1(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_FALSE(operator>(cl, cr1));

    Card cl2(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr2(Card::RANK_THREE, Card::SUIT_HEARTS);

    ASSERT_FALSE(operator>(cl2, cr2));

    Card cl3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card cr3(Card::RANK_TEN, Card::SUIT_SPADES);

    ASSERT_TRUE(operator>(cl3, cr3));

    Card cl4(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr4(Card::RANK_TWO, Card::SUIT_HEARTS);

    ASSERT_FALSE(operator>(cl4, cr4));

    Card cl5(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card cr5(Card::RANK_KING, Card::SUIT_HEARTS);

    ASSERT_TRUE(operator>(cl5, cr5));

    Card cl6(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr6(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(operator>(cl6, cr6));

}

TEST(test_operator_equal) {

    Card cl(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(operator==(cl, cr));

    Card cl1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr1(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_FALSE(operator==(cl, cr1));

    Card cl2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr2(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(operator==(cl2, cr2));

    Card cl3(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr3(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    ASSERT_FALSE(operator==(cl3, cr3));
}


TEST(test_operator_not_equal) {

    Card cl(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(operator!=(cl, cr));

    Card cl1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr1(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_TRUE(operator!=(cl, cr1));

    Card cl2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr2(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(operator!=(cl2, cr2));

    Card cl3(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card cr3(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    ASSERT_TRUE(operator!=(cl3, cr3));
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Card::SUIT_HEARTS, Suit_next(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, Suit_next(Card::SUIT_HEARTS));
}

TEST(test_card_less) {
    Card cl(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_FALSE(Card_less(cl, cr, Card::SUIT_SPADES));

    Card cl1(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr1(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(cl1, cr1, Card::SUIT_HEARTS));

    Card cl2(Card::RANK_JACK, Card::SUIT_SPADES);
    Card cr2(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_FALSE(Card_less(cl2, cr2, Card::SUIT_CLUBS));

    Card cl3(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr3(Card::RANK_ACE, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(cl3, cr3, Card::SUIT_SPADES));

    Card cl4(Card::RANK_TWO, Card::SUIT_SPADES);
    Card cr4(Card::RANK_ACE, Card::SUIT_HEARTS);

    ASSERT_FALSE(Card_less(cl4, cr4, Card::SUIT_SPADES));

    //different suits, jack, none is bower
    Card cl5(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card cr5(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_FALSE(Card_less(cl5, cr5, Card::SUIT_HEARTS));

    Card cl6(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card cr6(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(cl6, cr6, Card::SUIT_CLUBS));
    
    Card cl7(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card cr7(Card::RANK_JACK, Card::SUIT_SPADES);

    ASSERT_TRUE(Card_less(cl7, cr7, Card::SUIT_CLUBS));

    Card cl8(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card cr8(Card::RANK_ACE, Card::SUIT_HEARTS);

    ASSERT_TRUE(Card_less(cl8, cr8, Card::SUIT_HEARTS));

}


TEST_MAIN()
