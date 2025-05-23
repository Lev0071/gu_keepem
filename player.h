#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "playerStatus.h"
#include "inGame.h"
#include "handscore.h"


typedef struct player {
    char name[50];
    int credits;
    InGame in_game;       // replaces int: 1 = playing, 0 = quit
    int current_bet;
    Card hand[2];
    PlayerStatus status;
    HandScore best_score;
} Player;


void init_players(int count);
Player* get_players();
int get_player_count();
void remove_player(int index);  // Used to mark as quit

#endif // PLAYER_H

// typedef struct player {
//     char name[50]; // Name of player
//     int credits;
//     int in_game;         // 1 = playing, 0 = quit
//     int current_bet;    // much they’ve assigned during the current hand.
//     Card hand[2];  // holds 2 cards
//     Status status;         //  states: 0 = Out/Quit, 1 = Active, 2 = Folded.
// } Player;