#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "utils.h"

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration

static Player players[MAX_PLAYERS];  // players array private to the file (game.c)
int player_count = 0;

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator, make it truly random each time program is executed (based on time)
    
    do{
        player_count = get_integer_input("Enter number of players [2-8]: ");
    }while(player_count<2||player_count>MAX_PLAYERS);
    
    for (int i = 0; i < player_count; i++) {
        printf("Enter name for Player %d: ", i + 1);
        get_string_input("", players[i].name, sizeof(players[i].name));
        players[i].credits = INITIAL_CREDITS;
        players[i].in_game = 1;
    }
    
    printf("Players enterd:\n");
    for(int i=0;i<player_count;i++){
        printf("player %d:   Name: %s\n",i+1,players[i].name);
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

void play_hand(){ // Fake hand: randomly assign winner, transfer credits
    printf("\n--- Starting a new (fake) hand ---\n");

    int winner = -1;
    do {
        winner = rand() % player_count; // pick random player
    } while (!players[winner].in_game || players[winner].credits <= 0);

    int pot = 0;

    printf("\n🃏 Dealing cards...\n");
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue;
            printf("%s's hand: [X][X]\n", players[i].name);
    }

    // deduct credits
    for (int i = 0; i < player_count; i++) {
        if (i == winner || !players[i].in_game || players[i].credits <= 0) continue;
        
        /* Players who do NOT contribute to the pot:
           - the winner
           - players who have quit
           - players with no credits */

        int deduction = rand() % 11 + 5; // 5–15 credits
        if (players[i].credits < deduction) deduction = players[i].credits;

        players[i].credits -= deduction;
        pot += deduction;
    }

    players[winner].credits += pot;

    printf("🏆 %s wins this round and collects %d credits!\n", players[winner].name, pot);

    printf("\n💰 Player Credits:\n");
    printf("\n$$$$$$$$$$$$$$$$$$\n");
    for (int i = 0; i < player_count; i++) {
        printf("%s: %d credits\n", players[i].name, players[i].credits);
    }
    printf("$$$$$$$$$$$$$$$$$$\n");
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

void run_prediction_round(){
    // prediction logic
}