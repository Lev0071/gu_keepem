#include "pot.h"
#include <stdio.h>

void init_pot(Pot *pot){
    pot->amount = 0;
    pot->num_players = 0;
    for(int i=0;i<MAX_ELIGIBLE;i++){
        pot->eligible_players[i] = NULL;
    }
}

void add_eligible_player(Pot *pot,Player *player){
    if(pot->num_players < MAX_ELIGIBLE){
        pot->eligible_players[pot->num_players++] = player;
    }
}

void print_pot(const Pot *pot){
    printf("Pot: %d credits | Eligible: ", pot->amount);
    for(int i = 0; i < pot->num_players;i++){
        printf("%s ",pot->eligible_players[i]->name);
    }
    printf("\n");
}