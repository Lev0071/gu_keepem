#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "playerStatus.h"
#include "player.h"
#include "gamestate.h"
#include "pot.h"


extern Player players[MAX_PLAYERS];
extern int player_count;

typedef struct {
    Player *player;
    HandScore score;
} RankedPlayer;

const char* stage_name(RoundStage stage);

// Setup and Game Flow
void setup_game();
void play_hand();
void remove_quitters();
int game_over();
void show_final_message();

// Rounds and Actions
void run_prediction_round(RoundStage stage, GameState *g);
bool is_valid_action(Player *p, GameState *g, ActionType action);
void post_blinds(int sb_index, int bb_index, GameState *g);

// Dealing and Evaluation
void deal_hole_cards();
void deal_community_cards();
int rank_active_players(Player players[], int num_players, Card table[5], RankedPlayer ranked[]);
void resolve_betting_round(Player players[], int num_players, Card table[5]);
void resolve_pots_by_rank(Pot pots[], int pot_count, RankedPlayer ranked[], int ranked_count);

// Display Helpers
void print_table_cards(int count); 
void print_player_line(Player *p, int is_current, int is_dealer);
void print_table_state(GameState *g, Player players[], int current_index);
void print_valid_actions(Player *p, GameState *g, int call_amount);

// Utilities
const char* stage_to_string(RoundStage stage);



#endif