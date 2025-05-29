#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "utils.h"
#include "card.h"
#include "config.h"
#include "gamestate.h"
#include "handscore.h"
#include "playerStatus.h"
#include <stdbool.h>

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration
#define SMALL_GUESS 5
#define BIG_GUESS 10

static Card deck[52];       // the full deck
static Card table[5];       // 5 cards: flop (3), turn (1), river (1)
static int deck_size = 0;   // number of cards remaining
static int big_blind = 0;   
static int small_blind = 0;   
static Player players[MAX_PLAYERS];  // players array private to the file (game.c)
static int player_count = 0;
static int dealer_index = 0;

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator, make it truly random each time program is executed (based on time)

    do{
        player_count = get_integer_input("Please enter the number of players [2-8]: ");
    }while(player_count<2||player_count>MAX_PLAYERS);
    if(player_count == 2)printf("Heads-Up game selected\n");
    else printf("%i player game selected\n",player_count);
    
    int player_credits = get_integer_input("How many credits will each player start with?: ");
    big_blind = get_integer_input("What should the big blind be set to: ");
    if(big_blind>player_credits){
        do{
            printf("Cannot be bigger that players initial credits\n");
            big_blind = get_integer_input("What should the big blind be set to: ");
        }while(small_blind>big_blind);
    }
    
    small_blind = get_integer_input("What should the small blind be set to: ");

    if(small_blind>big_blind){
        do{
            printf("Cannot be bigger that the big blind\n");
            small_blind = get_integer_input("What should the small blind be set to: ");
        }while(small_blind>big_blind);
    }
    
    for (int i = 0; i < player_count; i++) {
        printf("Enter name for Player %d: ", i + 1);
        get_string_input("", players[i].name, sizeof(players[i].name));
        players[i].credits = player_credits;
        players[i].in_game = PLAYING;
    }

    dealer_index = rand() % player_count;
    #if DEBUG
    printf("\n===== DEBUG DUMP BEFORE EXIT =====\n");
    printf("Big Blind: %d\n", big_blind);
    printf("Small Blind: %d\n", small_blind);
    printf("Player Count: %d\n", player_count);
    for (int i = 0; i < player_count; i++) {
        printf("Player %d:\n", i + 1);
        printf("  Name:    %s\n", players[i].name);
        printf("  Credits: %d\n", players[i].credits);
        printf("  In Game: %s\n", players[i].in_game == PLAYING ? "PLAYING" : "QUIT");
    }
    printf("==================================\n");
    #endif
    
}

void print_table_cards(int count) {
    printf("Table Cards: ");
    for (int i = 0; i < count; i++) {
        print_card(table[i]);
        printf(" ");
    }
    printf("\n");
}

void deal_community_cards() {
    // Deal flop
    table[0] = deck[--deck_size];
    table[1] = deck[--deck_size];
    table[2] = deck[--deck_size];

    // Deal turn
    table[3] = deck[--deck_size];

    // Deal river
    table[4] = deck[--deck_size];
}

void deal_hole_cards(){
    init_deck(deck, &deck_size);
    //////////////
    // printf("\n===== deal_hole_cards =====\n");
    // printf("\n===== deck[52] =====\n");
    // printf("Cards in deck\n");
    // int ind = sizeof(deck) / sizeof(deck[0]);
    // for(int i = 0; i < ind; i++){

    //     if((i+1) % 13 == 0){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }
    //     else if(i == ind-1){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }else{
    //         print_card(deck[i]);
    //         printf(", ");
    //     }
    // }
    // printf("==================================\n");
    ///////////////////////////
    shuffle_deck(deck, deck_size);
    ///////////////////////////
    // printf("\n\n");
    // printf("\n===== shuffle_deck =====\n");
    // printf("\n===== deck[52] =====\n");
    // printf("Cards in deck\n");
    // ind = sizeof(deck) / sizeof(deck[0]);
    // for(int i = 0; i < ind; i++){

    //     if((i+1) % 13 == 0){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }
    //     else if(i == ind-1){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }else{
    //         print_card(deck[i]);
    //         printf(", ");
    //     }
    // }
    // printf("==================================\n");
    // exit(0);
    ///////////////////////////
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue;
        // printf("\n===== DECK Before HAND=====\n");
        // printf("Cards in deck\n");
        // for(int i = 0; i < deck_size; i++){

        //     if((i+1) % 13 == 0){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }
        //     else if(i == deck_size-1){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }else{
        //         print_card(deck[i]);
        //         printf(", ");
        //     }
        // }
        // printf("==================================\n");
        players[i].hand[0] = deck[--deck_size];
        players[i].hand[1] = deck[--deck_size];
        // printf("\n===== DECK After HAND=====\n");
        // printf("Cards in deck\n");
        // for(int i = 0; i < deck_size; i++){

        //     if((i+1) % 13 == 0){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }
        //     else if(i == deck_size-1){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }else{
        //         print_card(deck[i]);
        //         printf(", ");
        //     }
        // }
        // printf("==================================\n");
    }
}



void remove_quitters(){
    for(int i=0;i<player_count;i++){
        if(!players[i].in_game||players[i].credits <=0) continue;
        printf("%s, do you want to quit ? (1= Yes,0= No):",players[i].name);
        int choice = get_integer_input("");
        if(choice == 1){
            players[i].in_game = 0;
            printf("%s has left the game.\n",players[i].name);
        }
    }
}

void play_hand() { 
    printf("\n--- Starting a new hand ---\n");
    printf("%s is the dealer",players[dealer_index].name);
    wait_for_enter("\nPress Enter to begin...\n");

    // Step 1: Reset pot
    int pot = 0;

    // Step 2: Deal cards
    deal_hole_cards();
    deal_community_cards();

    // Step 3: Show players' hole cards
    printf("\n🃏 Cards dealt to all players...\n");
    wait_for_enter("\nPress Enter to begin...\n");
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue; // This line runs ONLY if the player is in the game AND has credits > 0
        printf("%s's hand: ", players[i].name);
        print_card(players[i].hand[0]);
        printf(" ");
        print_card(players[i].hand[1]);
        printf("\n");
    }

    // Step 4: Flop
    printf("\n Dealing the flop...\n");
    print_table_cards(3); // First 3 cards
    // Here you will later insert: run_prediction_round();

    // Step 5: Turn
    printf("\n Dealing the turn...\n");
    print_table_cards(4); // First 4 cards (flop + turn)
    // Here you will later insert: run_prediction_round();

    // Step 6: River
    printf("\n Dealing the river...\n");
    print_table_cards(5); // All 5 cards
    // Here you will later insert: run_prediction_round();

    // Step 7: FOR NOW - pick random winner
    int winner = -1;
    do {
        winner = rand() % player_count;
    } while (!players[winner].in_game || players[winner].credits <= 0);

    // Step 8: Deduct random credits (FAKE until betting is built)
    for (int i = 0; i < player_count; i++) {
        if (i == winner || !players[i].in_game || players[i].credits <= 0) continue;

        int deduction = rand() % 11 + 5; // 5–15 credits
        if (players[i].credits < deduction) deduction = players[i].credits;

        players[i].credits -= deduction;
        pot += deduction;
    }

    // Step 9: Award pot to winner
    players[winner].credits += pot;

    printf("🏆 %s wins this round and collects %d credits!\n", players[winner].name, pot);

    // Step 10: Show player credits
    printf("\n💰 Player Credits:\n");
    printf("\n$$$$$$$$$$$$$$$$$$\n");
    for (int i = 0; i < player_count; i++) {
        printf("%s: %d credits\n", players[i].name, players[i].credits);
    }
    printf("$$$$$$$$$$$$$$$$$$\n");

    dealer_index = (dealer_index +1)%player_count;

    printf("Table cards at the end:\n");
    for(int i=0;i<5;i++){
        print_card(table[i]);
    }printf("\n");
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue; // This line runs ONLY if the player is in the game AND has credits > 0
        printf("%s's hand: ", players[i].name);
        print_card(players[i].hand[0]);
        printf(" ");
        print_card(players[i].hand[1]);
        printf("\n");
    }
    printf("Evaluate each players best hand\n");
    for(int i=0;i<player_count;i++){
        printf("Player %s had the best hand: ",players[i].name);
        HandScore score = evaluate_best_hand(players[i].hand,table);
        for (int j = 0; j < 5; j++) {
            print_card(score.best_hand[j]);
        }
        printf("\n");
    }
}



int game_over(){
    int active = 0;
    for(int i =0;i<player_count;i++){
        if(players[i].in_game && players[i].credits > 0) active++; // as long as all players in the game have credit --> active
    }
    return active <= 1;  
}

void show_final_message(){     // Print game over message
    for (int i = 0; i < player_count; i++) {
        if (players[i].in_game && players[i].credits > 0) {
            printf("\n🎉 %s is the final winner with %d credits! 🎉\n", players[i].name, players[i].credits);
            return;
        }
    }
    printf("\nAll players have quit or lost. No winner this time!\n");
}

void run_prediction_round() {
    int current_bet = 0;
    int pot = 0;

    printf("\n🔔 Starting a prediction round!\n");

    // Step 1: Small Guess
    int small_index = 0; // First player
    if (players[small_index].in_game && players[small_index].credits > 0) {
        int amount = SMALL_GUESS;
        if (players[small_index].credits < amount) amount = players[small_index].credits;
        players[small_index].credits -= amount;
        players[small_index].current_bet = amount;
        pot += amount;
        printf("%s posts Small Guess (%d credits)\n", players[small_index].name, amount);
        current_bet = amount;
    }

    // Step 2: Big Guess
    int big_index = 1 % player_count; // Second player
    if (players[big_index].in_game && players[big_index].credits > 0) {
        int amount = BIG_GUESS;
        if (players[big_index].credits < amount) amount = players[big_index].credits;
        players[big_index].credits -= amount;
        players[big_index].current_bet = amount;
        pot += amount;
        printf("%s posts Big Guess (%d credits)\n", players[big_index].name, amount);
        if (amount > current_bet) current_bet = amount;
    }

    // Step 3: Betting Round
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue;

        // Skip players who already posted guesses
        if (i == small_index || i == big_index) continue;

        printf("\n%s's turn (Credits: %d)\n", players[i].name, players[i].credits);
        printf("1. Predict (bet new)  2. Call (match %d)  3. Raise  4. Fold\n", current_bet);
        int choice = get_integer_input("Enter choice: ");

        if (choice == 1) { // Predict (new bet)
            int bet = get_integer_input("Enter your bet amount: ");
            if (bet > players[i].credits) bet = players[i].credits;
            players[i].credits -= bet;
            players[i].current_bet = bet;
            pot += bet;
            if (bet > current_bet) current_bet = bet;
        } 
        else if (choice == 2) { // Call (match current bet)
            int diff = current_bet - players[i].current_bet;
            if (diff > players[i].credits) diff = players[i].credits;
            players[i].credits -= diff;
            players[i].current_bet += diff;
            pot += diff;
        }
        else if (choice == 3) { // Raise
            int raise = get_integer_input("Enter raise amount: ");
            if (raise > players[i].credits) raise = players[i].credits;
            int total = current_bet + raise;
            int diff = total - players[i].current_bet;
            if (diff > players[i].credits) diff = players[i].credits;
            players[i].credits -= diff;
            players[i].current_bet += diff;
            pot += diff;
            current_bet = players[i].current_bet;
        }
        else if (choice == 4) { // Fold
            players[i].status = 2; // Folded
            printf("%s folds!\n", players[i].name);
        }
    }

    printf("\nEnd of prediction round. Pot now has %d credits.\n", pot);
}

bool is_valid_action(Player *p, GameState *g, ActionType action) {
    if (p->in_game != PLAYING || p->status != STATUS_ACTIVE || p->credits <= 0) {
        return false;
    }

    int call_amount = g->current_bet - p->current_bet;

    switch (action) {
        case ACTION_CHECK:
            return call_amount == 0;

        case ACTION_CALL:
            return call_amount > 0 && p->credits >= call_amount;

        case ACTION_BET:
            return g->current_bet == 0 && p->credits > 0;

        case ACTION_RAISE:
            return g->current_bet > 0 && p->credits > call_amount;

        case ACTION_ALL_IN:{
            if (p->credits <= 0) return false;

            if (g->current_bet == 0) {
                // All-in as a bet
                return true;
            } else if (p->credits + p->current_bet > g->current_bet) {
                // All-in as a raise
                return true;
            } else if (p->credits + p->current_bet == g->current_bet) {
                // All-in as a call
                return true;
            } else {
                // All-in is less than call — still allowed, but not re-raisable
                return true;
            }
        }

        case ACTION_FOLD:
            return p->status == STATUS_ACTIVE;

        default:
            return false;
    }
}

