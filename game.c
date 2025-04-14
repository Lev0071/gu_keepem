#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "utils.h"

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration

int player_quits[3] = {1, 0, 1}; // DEL
static Player players[MAX_PLAYERS];  // players array private to the file (game.c)
int player_count = 0;

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator, make it truly random each time program is executed (based on time)
    
    do{
        player_count = get_integer_input("Enter number of players [2-8]: ");
    }while(player_count<2||player_count>MAX_PLAYERS);
    
    for(int i=0;i<player_count;i++){
        printf("Enter name for player %d: \n",i+1);
        get_string_input("",players[i].name,sizeof(players[i].name));
    }
    
    printf("Players enterd:\n");
    for(int i=0;i<player_count;i++){
        printf("player %d:   Name: %s\n",i+1,players[i].name);
    }
    
}

void remove_quitters(){    // Ask if players wnat to continue
    for(int i=0;i<player_count;i++){
        if (player_quits[i] == 1){
            printf("Player %d has quit...BOOOOO!\n",i);
        }
    }
}

void play_hand(){ // Fake hand: randomly assign winner, transfer credits
    // Enter 3 or more players so this does not break the array
    player_count = 3;                                                          //Test# 1
    players[0] = (Player){"Alice", 50, 1};                                     //Test# 1
    players[1] = (Player){"Bob", 100, 1};                                      //Test# 1
    players[2] = (Player){"Charlie", 75, 1};                                   //Test# 1
    printf("\n--- Starting a new (fake) hand ---\n");

    int winner = -1;
    do {
        winner = rand() % player_count; // pick random player
        printf("Broke Fella: %d\n", players[winner].credits <= 0); // DEBUG     //Test# 1
        printf("Broke Fella: %d\n", !players[winner].in_game);// DEBUG          //Test# 1
    } while (!players[winner].in_game || players[winner].credits <= 0);

    printf("\n--- %s was the randomy selected winner ---\n",players[winner].name); // DEBUG

    int pot = 0;

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
    for (int i = 0; i < player_count; i++) {
        if (players[i].in_game||players[i].credits<=0)continue;
            printf("%s now has %d credits\n", players[i].name, players[i].credits);
    }
    exit(0);                                                    // DEBUG          //Test# 1
}


int game_over(){
    int active = 0;
    for(int i =0;i<player_count;i++){
        if(players[i].in_game && players[i].credits > 0) active++; // as long as all players in the game have credit --> active
    }
    return active <= 1;  
}

void show_final_message(){
    printf("GAME OVER!");
}