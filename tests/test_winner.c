#include "../src/handscore.h"
#include "../src/card.h"
#include "../src/utils.h"
#include "../src/player.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 8

// Fisher–Yates Shuffle
void shuffle(char array[][50], int size) { // shuffles an array
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap
        char temp[50];
        strcpy(temp, array[i]);
        strcpy(array[i], array[j]);// array[i] = array[j];
        strcpy(array[j], temp);// array[j] = temp;
    }
}

int main() {
    srand(time(NULL));  // Seed RNG
    int player_count;
    char names[MAX_PLAYERS][50]; // row the player object, column the player's name || 2D Array
    Card hole[MAX_PLAYERS][2]; // row of players and their cards as card objects || 2D Array
    Card table[5];
    Card deck[52];
    int deck_size = 0;
    char decide = '0';

    do{
        printf("Generate players manually or auto generated ? (m/a):");
        scanf("%c", &decide);
        int ch;while ((ch = getchar()) != '\n' && ch != EOF);
    } while (decide != 'm' && decide != 'M' && decide != 'a' && decide != 'A');

    if(decide == 'm' || decide == 'M'){
        do {
            printf("Enter number of players (2–8): ");
            scanf("%d", &player_count);
            if(player_count < 2 || player_count > 8){
                printf("Invalid Number of Players\n");
                continue;
            }
        } while (player_count < 2 || player_count > 8);
        
        
        if (player_count < 2 || player_count > MAX_PLAYERS) {
        printf("Invalid player count.\n");
        return 1;
    }
    }else if(decide == 'a' || decide == 'A'){
        char playerNames[8][50] = {
        "Yasin",
        "Andrea",
        "Adrian",
        "Mia",
        "Liam",
        "Sophie",
        "Noah",
        "Ella"
        };
        player_count = (rand() % 7) + 2;  // range: 2 to 8
        shuffle(playerNames, MAX_PLAYERS);

        for (int i = 0; i < player_count; i++) {
            strcpy(names[i], playerNames[i]);
        }
    }
    if(decide == 'm' || decide == 'M'){
      for (int i = 0; i < player_count; i++) {
            printf("Enter name for Player %d: ", i + 1);
            scanf("%s", names[i]);
        }      
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