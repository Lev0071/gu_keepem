#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration

int player_quits[3] = {1, 0, 1};
int gameOver = 0;
int player_count;

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator
    
    do{
        player_count = get_integer_input("Enter number of players [2-8]: ");
    }while(player_count<2||player_count>MAX_PLAYERS);
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
