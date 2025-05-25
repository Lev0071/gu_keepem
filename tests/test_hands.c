#include "../src/handscore.h"
#include "../src/card.h"
#include <assert.h>
#include <stdio.h>

void test_royal_flush() {
    Card hole[2] = {
        {TEN, SPADES},
        {JACK, SPADES}
    };
    Card table[5] = {
        {QUEEN, SPADES},
        {KING, SPADES},
        {ACE, SPADES},
        {TWO, HEARTS},  // junk
        {THREE, DIAMONDS}  // junk
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT_FLUSH);
    assert(result.main_values[0] == ACE); // Royal Flush
    printf("✅ Passed: test_royal_flush()\n");
}

void test_straight_flush() {
    Card hole[2] = {
        {SEVEN, SPADES},
        {EIGHT, SPADES}
    };
    Card table[5] = {
        {SIX, SPADES},
        {NINE, SPADES},
        {TEN, SPADES},
        {TWO, DIAMONDS},  
        {THREE, CLUBS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT_FLUSH);
    assert(result.main_values[0] == TEN); // Straight Flush
    printf("✅ Passed: test_straight_flush()\n");
}

void test_ace_low_straight_flush() {
    Card hole[2] = {
        {ACE, SPADES},
        {TWO, SPADES}
    };
    Card table[5] = {
        {THREE, SPADES},
        {FOUR, SPADES},
        {FIVE, SPADES},
        {EIGHT, DIAMONDS},  
        {NINE, HEARTS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT_FLUSH);
    assert(result.main_values[0] == FIVE);  
    printf("✅ Passed: test_ace_low_straight_flush()\n");
}

void four_of_a_kind() {
    Card hole[2] = {
        {NINE, SPADES},
        {NINE, CLUBS}
    };
    Card table[5] = {
        {NINE, HEARTS},
        {NINE, DIAMONDS},
        {KING, SPADES},
        {TWO, CLUBS},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FOUR_OF_A_KIND);
    assert(result.main_values[0] == NINE);
    assert(result.kicker_values[0] == KING);
    printf("✅ Passed: four_of_a_kind()\n");
}

void four_of_a_kind_lower_kicker() {
    Card hole[2] = {
        {NINE, SPADES},
        {NINE, CLUBS}
    };
    Card table[5] = {
        {NINE, HEARTS},
        {NINE, DIAMONDS},
        {JACK, SPADES},
        {TWO, CLUBS},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FOUR_OF_A_KIND);
    assert(result.main_values[0] == NINE);
    assert(result.kicker_values[0] == JACK);
    printf("✅ Passed: four_of_a_kind_lower_kicker()\n");
}

void four_of_a_kind_higher_kicker() {
    Card hole[2] = {
        {NINE, SPADES},
        {NINE, CLUBS}
    };
    Card table[5] = {
        {NINE, HEARTS},
        {NINE, DIAMONDS},
        {ACE, SPADES},
        {TWO, CLUBS},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FOUR_OF_A_KIND);
    assert(result.main_values[0] == NINE);
    assert(result.kicker_values[0] == ACE);
    printf("✅ Passed: four_of_a_kind_higher_kicker()\n");
}

void full_house_1() {
    Card hole[2] = {
        {QUEEN, SPADES},
        {QUEEN, HEARTS}
    };
    Card table[5] = {
        {QUEEN, DIAMONDS},
        {NINE, SPADES},
        {NINE, CLUBS},
        {TWO, SPADES},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FULL_HOUSE);
    assert(result.main_values[0] == QUEEN);
    assert(result.main_values[1] == NINE);
    printf("✅ Passed: full_house_1()\n");
}

void full_house_2() {
    Card hole[2] = {
        {QUEEN, SPADES},
        {QUEEN, HEARTS}
    };
    Card table[5] = {
        {QUEEN, DIAMONDS},
        {EIGHT, SPADES},
        {EIGHT, CLUBS},
        {TWO, SPADES},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FULL_HOUSE);
    assert(result.main_values[0] == QUEEN);
    assert(result.main_values[1] == EIGHT);
    printf("✅ Passed: full_house_2()\n");
}

void full_house_3() {
    Card hole[2] = {
        {JACK, SPADES},
        {JACK, HEARTS}
    };
    Card table[5] = {
        {JACK, DIAMONDS},
        {NINE, SPADES},
        {NINE, CLUBS},
        {TWO, SPADES},  
        {THREE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FULL_HOUSE);
    assert(result.main_values[0] == JACK);
    assert(result.main_values[1] == NINE);
    printf("✅ Passed: full_house_3()\n");
}

void flush_1() {
    Card hole[2] = {
        {TEN, HEARTS},
        {EIGHT, HEARTS}
    };
    Card table[5] = {
        {ACE, HEARTS},
        {SIX, HEARTS},
        {TWO, HEARTS},
        {THREE, CLUBS},  
        {NINE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FLUSH);
    assert(result.main_values[0] == ACE);
    assert(result.main_values[1] == TEN);
    assert(result.main_values[2] == EIGHT);
    assert(result.main_values[3] == SIX);
    assert(result.main_values[4] == TWO);
    printf("✅ Passed: flush_1()\n");
}

void flush_2() {
    Card hole[2] = {
        {QUEEN, HEARTS},
        {SEVEN, HEARTS}
    };
    Card table[5] = {
        {TEN, HEARTS},
        {EIGHT, HEARTS},
        {THREE, HEARTS},
        {SIX, DIAMONDS},  
        {NINE, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_FLUSH);
    assert(result.main_values[0] == QUEEN);
    assert(result.main_values[1] == TEN);
    assert(result.main_values[2] == EIGHT);
    assert(result.main_values[3] == SEVEN);
    assert(result.main_values[4] == THREE);
    printf("✅ Passed: flush_2()\n");
}

void test_straight() {
    Card hole[2] = {
        {SEVEN, HEARTS},
        {EIGHT, CLUBS}
    };
    Card table[5] = {
        {SIX, DIAMONDS},
        {NINE, SPADES},
        {TEN, CLUBS},
        {ACE, SPADES},  
        {THREE, CLUBS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT);
    assert(result.main_values[0] == TEN);
    printf("✅ Passed: flush_2()\n");
}

void test_ace_low_straight() {
    Card hole[2] = {
        {ACE, CLUB},
        {TWO, DIAMONDS}
    };
    Card table[5] = {
        {THREE, SPADE},
        {FOUR, HEARTS},
        {FIVE, DIAMONDS},
        {NINE, HEARTS},  
        {KING, DIAMONDS}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT);
    assert(result.main_values[0] == FIVE);
    printf("✅ Passed: flush_2()\n");
}

void test_ace_high_straight() {
    Card hole[2] = {
        {TEN, HEARTS},
        {JACK, SPADES}
    };
    Card table[5] = {
        {QUEEN, DIAMONDS},
        {KING, CLUBS},
        {ACE, SPADES},
        {FIVE, HEARTS},  
        {SIX, SPADES}  
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_STRAIGHT);
    assert(result.main_values[0] == ACE);
    printf("✅ Passed: flush_2()\n");
}

void three_of_a_kind() {
    Card hole[2] = {
    {EIGHT, SPADES},
    {EIGHT, CLUBS}
    };
    Card table[5] = {
        {EIGHT, DIAMONDS},
        {TEN, SPADES},
        {TWO, CLUBS},
        {FIVE, HEARTS},
        {SIX, DIAMONDS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == EIGHT);
    assert(result.kicker_values[0] == TEN);
    assert(result.kicker_values[0] == SIX);
    printf("✅ Passed: three_of_a_kind()\n");
}

void three_of_a_kind_tiebreaker_sameTrips_higherKicker() {
    Card hole[2] = {
        {EIGHT, SPADES},
        {EIGHT, CLUBS}
    };
    Card table[5] = {
        {EIGHT, DIAMONDS},
        {ACE, SPADES},
        {KING, HEARTS},
        {FIVE, CLUBS},
        {TWO, DIAMONDS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == EIGHT);
    assert(result.kicker_values[0] == ACE);
    assert(result.kicker_values[0] == KING);
    printf("✅ Passed: three_of_a_kind()\n");
}

void three_of_a_kind_tiebreaker_sameTrips_higherKicker() {
    Card hole[2] = {
        {EIGHT, SPADES},
        {EIGHT, CLUBS}
    };
    Card table[5] = {
        {EIGHT, DIAMONDS},
        {ACE, SPADES},
        {KING, HEARTS},
        {FIVE, CLUBS},
        {TWO, DIAMONDS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == EIGHT);
    assert(result.kicker_values[0] == ACE);
    assert(result.kicker_values[0] == KING);
    printf("✅ Passed: three_of_a_kind()\n");
}

void three_of_a_kind_tiebreaker_differentTrips() {
    Card hole[2] = {
        {SEVEN, SPADES},
        {SEVEN, CLUBS}
    };
    Card table[5] = {
        {SEVEN, DIAMONDS},
        {ACE, SPADES},
        {QUEEN, HEARTS},
        {FIVE, CLUBS},
        {TWO, DIAMONDS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == SEVEN);
    assert(result.kicker_values[0] == ACE);
    assert(result.kicker_values[0] == QUEEN);
    printf("✅ Passed: three_of_a_kind()\n");
}

void two_pair() {
    Card hole[2] = {
        {QUEEN, CLUBS},
        {QUEEN, HEARTS}
    };
    Card table[5] = {
        {FOUR, SPADES},
        {FOUR, DIAMONDS},
        {NINE, DIAMONDS},
        {SIX, SPADES},
        {THREE, CLUBS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == QUEEN);
    assert(result.main_values[1] == FOUR);
    assert(result.kicker_values[0] == NINE);
    printf("✅ Passed: two_pair()\n");
}

void two_pair_higher_pair() {
    Card hole[2] = {
        {QUEEN, CLUBS},
        {FOUR, CLUBS}
    };
    Card table[5] = {
        {QUEEN, HEARTS},
        {FOUR, SPADES},
        {NINE, DIAMONDS},
        {SIX, SPADES},
        {THREE, CLUBS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == QUEEN);
    assert(result.main_values[1] == FOUR);
    assert(result.kicker_values[0] == NINE);
    printf("✅ Passed: two_pair_higher_pair()\n");
}

void two_pair_EdgeCase_Two_pair_from_board() {
    Card hole[2] = {
        {TEN, SPADES},
        {JACK, CLUBS}
    };
    Card table[5] = {
        {NINE, HEARTS},
        {NINE, SPADES},
        {THREE, DIAMONDS},
        {THREE, SPADES},
        {ACE, HEARTS}
    };

    HandScore result = evaluate_best_hand(hole, table);
    assert(result.hand_rank == HAND_THREE_OF_A_KIND);
    assert(result.main_values[0] == NINE);
    assert(result.main_values[1] == THREE);
    assert(result.kicker_values[0] == ACE);
    printf("✅ Passed: two_pair_EdgeCase_Two_pair_from_board()\n");
}


int main(){
    printf("###### TEST HAND EVALUATION ###### == START\n");
    printf("Testing all Straight Flush cases...\n");
    test_royal_flush();
    test_straight_flush();
    test_ace_low_straight_flush();
    printf("Testing all Four of a Kind cases...\n");
    four_of_a_kind();
    four_of_a_kind_lower_kicker();
    four_of_a_kind_higher_kicker();
    printf("Testing all Full House cases...\n");
    full_house_1();
    full_house_2();
    full_house_3();
    printf("Testing Flush cases...\n");
    flush_1();
    flush_2();
    printf("Testing Straight cases...\n");
    test_straight();
    test_ace_low_straight();
    test_ace_high_straight();
    printf("Testing Three of a kind cases...\n");
    three_of_a_kind();
    three_of_a_kind_tiebreaker_sameTrips_higherKicker();
    three_of_a_kind_tiebreaker_differentTrips();
    printf("Testing Two Pair cases...\n");
    two_pair();
    two_pair_higher_pair();
    two_pair_EdgeCase_Two_pair_from_board();
    printf("Testing Two Pair cases...\n");
    one_pair();
    one_pair_kicker_comparison();
    one_pair_BoardPair_vs_HolePair();
    printf("###### TEST HAND EVALUATION ###### == END\n");
}

// gcc -o run_tests tests/test_hands.c src/*.c -I./src
// ./run_tests

/// Mac
// gcc -o run_tests test_hands.c ../src/*.c -I../src
// ./run_tests

/// Windoes
// gcc -o run_tests test_hands.c ^
//   ../src/card.c ../src/player.c ../src/utils.c ^
//   ../src/game.c ../src/handscore.c ^
//   -I../src

// gcc -o run_tests test_hands.c ../src/card.c ../src/player.c ../src/utils.c ../src/game.c ../src/handscore.c -I../src


// run_tests.exe

// Windows 2
// cd path\to\gu_keepem\tests
// build_tests.bat

// test_royal_flush()	HAND_STRAIGHT_FLUSH	High = ACE
// test_straight_low_ace()	HAND_STRAIGHT	A-2-3-4-5
// test_four_of_a_kind()	HAND_FOUR_OF_A_KIND	Quad + 1 kicker
// test_two_pair()	HAND_TWO_PAIR	Higher and lower pair
// test_high_card()	HAND_HIGH_CARD	No combos
// test_full_house()	HAND_FULL_HOUSE	Trip + Pair