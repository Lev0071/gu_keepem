#include "../src/handscore.h"
#include "../src/card.h"
#include "../src/utils.h"
#include "../src/player.h"
#include <assert.h>
#include <stdio.h>

#define MAX_PLAYERS 8

int main() {
    int player_count;
    char names[MAX_PLAYERS][50]; // row the player object, column the player's name || 2D Array
    Card hole[MAX_PLAYERS][2]; // row of players and their cards as card objects || 2D Array
    Card table[5];
    Card deck[52];
    int deck_size = 0;

    printf("Enter number of players (2–8): ");
    scanf("%d", &player_count);
    if (player_count < 2 || player_count > MAX_PLAYERS) {
        printf("Invalid player count.\n");
        return 1;
    }

    for (int i = 0; i < player_count; i++) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%s", names[i]);
    }

    // Step 1: Shuffle deck
    init_deck(deck, &deck_size);
    shuffle_deck(deck, deck_size);

    // Step 2: Deal hole cards
    for (int i = 0; i < player_count; i++) {
        hole[i][0] = deck[--deck_size];
        hole[i][1] = deck[--deck_size];
    }

    // Step 3: Deal table
    for (int i = 0; i < 5; i++) {
        table[i] = deck[--deck_size];
    }

    // Step 4: Evaluate hands
    HandScore scores[MAX_PLAYERS];
    HandScore best_score = {0};  // Initializes all members of best_score (hand_rank, main_values[], kicker_values[], etc.) to zero
    int winner_indices[MAX_PLAYERS]; // Stores the index of each winner
    int winner_count = 0; // Tracks how many winners are currently stored

    printf("\n🃏 Community Cards:\n");
    for (int i = 0; i < 5; i++) {
        print_card(table[i]);
        printf(" ");
    }
    printf("\n\n");

    for (int i = 0; i < player_count; i++) {
        printf("\n============= Player: %d Name: %s ============= [START]\n",i,names[i]);
        printf("Player %s's hand: ", names[i]);
        print_card(hole[i][0]); printf(" ");
        print_card(hole[i][1]); printf("\n");

        scores[i] = evaluate_best_hand(hole[i], table);

        #if DEBUG
        print_hand_score(scores[i]);
        #endif

        if (i == 0 || compare_hand_scores(scores[i], best_score) > 0) { // first player is assigned best score at the start, or current player is the single winner if they beat running best score
            best_score = scores[i];
            winner_indices[0] = i;
            winner_count = 1;
        } else if (compare_hand_scores(scores[i], best_score) == 0) {
            winner_indices[winner_count++] = i;
        }
        printf("============= Player %d Name %s ============= [END]",i,names[i]);
    }

    // Step 5: Show winners
    printf("\n🏆 Winner%s:\n", winner_count > 1 ? "s" : "");
    for (int i = 0; i < winner_count; i++) {
        printf("  %s\n", names[winner_indices[i]]);
    }

    return 0;
}

// gcc -o run_winner_test test_winner.c ../src/card.c ../src/player.c ../src/utils.c ../src/game.c ../src/handscore.c -I../src
// ./run_winner_test   # on Linux/macOS
// run_winner_test.exe # on Windows

// chcp 65001