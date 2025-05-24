#include "../src/handscore.h"
#include "../src/card.h"
#include <assert.h>
#include <stdio.h>

void test_straight_flush() {
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
    printf("✅ Passed: test_straight_flush()\n");
}

int main(){
    test_straight_flush();
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