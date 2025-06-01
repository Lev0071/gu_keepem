#include "pot.h"
#include <stdio.h>
#include <limits.h> // for INT_MAX
#include "constants.h"

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
        if(i==pot->num_players - 1){
            printf("%s.",pot->eligible_players[i]->name);
        }else{
            printf("%s, ",pot->eligible_players[i]->name);
        }
    }
    printf("\n");
}

void build_side_pots(Pot pots[], int *pot_count, Player players[], int num_players){
    int contributions[MAX_PLAYERS];
    for(int i=0;i<num_players;i++){
        contributions[i] = players[i].current_bet;
    }

    int remaining_players = num_players;
    *pot_count = 0;

    while(remaining_players > 0){
        int main_contribution = INT_MAX;

        // Fin smallest non zero contribution
        for (int i = 0; i < num_players; i++) {
            if(contributions[i]>0 && contributions [i] < main_contribution){
                main_contribution = contributions[i];
            }
        }
        if(main_contribution == INT_MAX) break;

        Pot *pot = &pots[(*pot_count)];
        init_pot(pot);
    }
}