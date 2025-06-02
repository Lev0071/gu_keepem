#include "../src/game.h"
#include "../src/player.h"
#include "../src/pot.h"
#include "../src/handscore.h"
#include "../src/utils.h"
#include "../src/card.h"
#include <stdio.h>

int main() {
    printf("\nSCENARIO #1\n\n");

// ✅ Step 1: Scenario Recap
// We’re simulating this showdown:
// | Player | Stack | Action         |
// | ------ | ----- | -------------- |
// | Alice  | 100   | All-in         |
// | Bob    | 200   | All-in         |
// | Chloe  | 400   | Calls 200      |
// | Yasin  | 500   | Raises to 400  |
// | Chloe  | —     | Calls 200 more |

// 🪙 Pots:
// Main Pot: 400 (100 × 4) → Eligible: Alice, Bob, Chloe, Yasin
// Side Pot 1: 300 (100 × 3) → Eligible: Bob, Chloe, Yasin
// Side Pot 2: 400 (200 × 2) → Eligible: Chloe, Yasin

// 🃏 Hands (example scores):
// Bob: Two Pair (Jacks and Tens) → 1st
// Yasin: Two Pair (Jacks and Nines) → 2nd
// Alice: Pair of Queens → 3rd
// Chloe: One Pair (Eights) → 4th

    Player players1[4] = {
        {.name = "Alice", .credits = 0, .current_bet = 100},
        {.name = "Bob",   .credits = 0, .current_bet = 200},
        {.name = "Chloe", .credits = 0, .current_bet = 400},
        {.name = "Yasin", .credits = 0, .current_bet = 400},
    };

    players1[0].hand[0] = (Card){QUEEN, SPADES};
    players1[0].hand[1] = (Card){QUEEN, DIAMONDS};

    players1[1].hand[0] = (Card){JACK, CLUBS};
    players1[1].hand[1] = (Card){TEN, CLUBS};

    players1[2].hand[0] = (Card){EIGHT, HEARTS};
    players1[2].hand[1] = (Card){EIGHT, CLUBS};

    players1[3].hand[0] = (Card){JACK, HEARTS};
    players1[3].hand[1] = (Card){NINE, SPADES};

    Card table1[5] = {
        {JACK, SPADES},
        {NINE, HEARTS},
        {TEN, HEARTS},
        {TWO, CLUBS},
        {FIVE, SPADES}
    };

    for (int i = 0; i < 4; i++) {
        players1[i].status = STATUS_ACTIVE;
    }

    resolve_betting_round(players1, 4, table1);

    printf("\nSCENARIO #2\n\n");

// ✅ Step 1: Scenario Recap
// We’re simulating this showdown:
// | Player | Stack | Action         |
// |--------|-------|----------------|
// | Alice  | 150   | All-in         |
// | Bob    | 300   | All-in         |
// | Chloe  | 400   | Calls 300      |
// | Yasin  | 500   | Raises to 500  |
// | Zara   | 700   | Calls 500      |
// | Firas  | 1000  | Calls 500      |

// 🪙 Pots:
// Main Pot: 900  = 6 × 150  → Eligible: Alice, Bob, Chloe, Yasin, Zara, Firas
// Side Pot 1: 750 = 5 × 150 → Eligible: Bob, Chloe, Yasin, Zara, Firas
// Side Pot 2: 600 = 3 × 200 → Eligible: Yasin, Zara, Firas

// 🃏 Hands (example scores):
// Firas: Three of a Kind (Twos)        → 🥇 1st
// Bob:   Two Pair (Jacks and Tens)     → 🥈 2nd
// Yasin: Two Pair (Jacks and Nines)    → 🥉 3rd
// Alice: Pair of Queens                → 4th
// Chloe: One Pair (Fours)              → 5th
// Zara:  Ace High                      → 6th

// 🏆 Winnings:
// Firas wins Main Pot (900), Side Pot 1 (750), and Side Pot 2 (600)
// ✅ Total: 2250 credits

    Player players2[6] = {
        {.name = "Alice", .credits = 0, .current_bet = 150},
        {.name = "Bob",   .credits = 0, .current_bet = 300},
        {.name = "Chloe", .credits = 0, .current_bet = 300},
        {.name = "Yasin", .credits = 0, .current_bet = 500},
        {.name = "Zara",  .credits = 0, .current_bet = 500},
        {.name = "Firas", .credits = 0, .current_bet = 500},
    };

    players2[0].hand[0] = (Card){QUEEN, SPADES};      // Alice: Pair of Queens
    players2[0].hand[1] = (Card){QUEEN, DIAMONDS};

    players2[1].hand[0] = (Card){JACK, CLUBS};        // Bob: Two Pair (Jacks & Tens)
    players2[1].hand[1] = (Card){TEN, CLUBS};

    players2[2].hand[0] = (Card){FOUR, HEARTS};       // Chloe: One Pair (Fours)
    players2[2].hand[1] = (Card){FOUR, CLUBS};

    players2[3].hand[0] = (Card){JACK, HEARTS};       // Yasin: Two Pair (Jacks & Nines)
    players2[3].hand[1] = (Card){NINE, SPADES};

    players2[4].hand[0] = (Card){ACE, HEARTS};        // Zara: Ace High
    players2[4].hand[1] = (Card){SEVEN, CLUBS};

    players2[5].hand[0] = (Card){TWO, SPADES};        // Firas: Three of a Kind (Twos)
    players2[5].hand[1] = (Card){TWO, DIAMONDS};

    Card table2[5] = {
        {JACK, SPADES},
        {NINE, HEARTS},
        {TEN, HEARTS},
        {TWO, CLUBS},
        {FIVE, SPADES}
    };

    for (int i = 0; i < 6; i++) {
        players2[i].status = STATUS_ACTIVE;
    }

    resolve_betting_round(players2, 6, table2);

    return 0;
}


// gcc -o test_winner_distribution tests/test_winner_distribution.c \
//     src/game.c src/player.c src/pot.c src/card.c src/utils.c src/handscore.c -Isrc

// gcc -o test_winner_distribution tests/test_winner_distribution.c src/game.c src/player.c src/pot.c src/card.c src/utils.c src/handscore.c -Isrc
// gcc -o test_winner_distribution test_winner_distribution.c ../src/game.c ../src/player.c ../src/pot.c ../src/card.c ../src/utils.c ../src/handscore.c -Isrc

// ./test_winner_distribution

// test_winner_distribution.exe

