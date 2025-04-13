#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration

int player_quits[3] = {1, 0, 1};
int gameOver = 0;
void setup_game(){
    srand(time(NULL)); //Seed randon generator
    printf("Inside setup_game");
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
    printf("Inside setup_game\n\n");
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
