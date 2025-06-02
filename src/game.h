#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "playerStatus.h"
#include "player.h"
#include "gamestate.h"

typedef struct {
    Player *player;
    HandScore score;
} RankedPlayer;

void setup_game();
void play_hand();
void remove_quitters();
int game_over();
void show_final_message();
void run_prediction_round();
void print_table_cards(int count); 
void deal_community_cards();   
bool is_valid_action(Player *p, GameState *g, ActionType action);
void resolve_betting_round(Player players[], int num_players, Card table[5]);


#endif