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
        if(i != pot->num_players -1){
            printf("%s, ",pot->eligible_players[i]->name);
        }else{
            printf("%s.",pot->eligible_players[i]->name);
        }
    }
    printf("\n");
}

void build_side_pots(Pot pots[], int *pot_count, Player players[], int num_players){
    /*
    Simulates layered pot creation using players' current bets
    Supports side pots in all-in situations
    Builds pots fairly by peeling off contributions in smallest slices
    Tracks who is eligible to win each pot
    */
    int contributions[MAX_PLAYERS];
    for(int i=0;i<num_players;i++){
        contributions[i] = players[i].current_bet;
    }                                                                                           // Copy player bets into local array

    int remaining_players = num_players;
    *pot_count = 0;                                                                             //Initialize loop conditions

    while(remaining_players > 0){                                                               //Main pot-building loop
        int min_contribution = INT_MAX;

        // Find smallest non zero contribution
        for (int i = 0; i < num_players; i++) {
            if(contributions[i]>0 && contributions [i] < min_contribution){
                min_contribution = contributions[i];
            }
        }                                                                                      //Find the minimum non-zero contribution

        if(min_contribution == INT_MAX) break;                                                // Break if no more contributions exist

        Pot *pot = &pots[(*pot_count)];                                                        //Create a new pot
        init_pot(pot);

        for(int i=0;i<num_players;i++){
            if(contributions[i]>0){
                pot->amount += min_contribution;
                add_eligible_player(pot,&players[i]);
                contributions[i] -= min_contribution;
            }
        }                                                                                       // Collect min_contribution from each contributing player

        (*pot_count)++;                                                                         //Move to the next pot

        // Update remianing players
        remaining_players=0;                                                                    //Repeat if more contributions exist
        for(int i = 0; i < num_players;i++){
            if(contributions[i] > 0){
                remaining_players++;
            }
        }
    }
}