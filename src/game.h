#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "playerStatus.h"

void setup_game();
void play_hand();
void remove_quitters();
int game_over();
void show_final_message();
void run_prediction_round();
void print_table_cards(int count); 
void deal_community_cards();   
bool is_valid_action(Player *p, GameState *g, ActionType action);


#endif