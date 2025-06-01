#ifndef POT_H
#define POT_H

#include "player.h"
#define MAX_POTS 5
#define MAX_ELIGIBLE 8

typedef struct {
    int amount;
    Player *eligible_players[MAX_ELIGIBLE];
    int num_players;
} Pot;

// Pot API
void init_pot(Pot *pot);
void add_eligible_player(Pot *pot,Player * player);
void print_pot(const Pot *pot);
void build_side_pots(Pot pots[], int *pot_count, Player players[], int num_players);

#endif // POT_H