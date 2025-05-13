#ifndef GAME_H
#define GAME_H

void setup_game();
void play_hand();
void remove_quitters();
int game_over();
void show_final_message();
void run_prediction_round();
void print_table_cards(int count); 
void deal_community_cards();         

#endif