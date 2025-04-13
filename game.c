#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "utils.h"

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration

int player_quits[3] = {1, 0, 1}; // DEL
int gameOver = 0; // DEL
static Player players[MAX_PLAYERS];  // players array private to the file (game.c)
int player_count = 0;

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator
    
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

void remove_quitters(){
    for(int i=0;i<sizeof(player_quits)/sizeof(player_quits[0]);i++){
        if (player_quits[i] == 1){
            printf("Player %d has quit...BOOOOO!\n",i);
        }
    }
}

void play_hand(){
    char c;
    printf("game over ? (y/n):");
    scanf(" %c", &c);
    if(c=='y')
        gameOver = 0;
    else if(c=='n')
        gameOver = 1;
}
int game_over(){
    return gameOver;
}

void show_final_message(){
    printf("GAME OVER!");
}

void print_intro() {
    printf("Welcome to GU-Keep'Em!!\n");
    printf("=========================================\n\n");

    printf("    .------.    .------.    .------.\n");
    printf("   |A_  __ |  |A_  _  |  |A_  _  |\n");
    printf("   |( \\/ )|  |( \\/ )|  |( . ) |\n");
    printf("   | \\  / |  | \\  / |  | \\ /  |\n");
    printf("   |  \\/ A|  |  \\/ A|  |  v  A|\n");
    printf("   `------'  `------'  `------'\n");

    printf("\n=========================================\n");
    printf("🛠️  BETA VERSION - Week 1: Interface Scaffold Only\n");
    printf("=========================================\n\n");

    printf("Press Enter to start...\n");
    getchar(); // Wait for Enter
}