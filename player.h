#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    int credits;
    int in_game;         // 1 = playing, 0 = quit
    int current_bet;    // much they’ve assigned during the current hand.
    //CardCollection hand;  // holds 2 cards
    int status;         //  states: 0 = Out/Quit, 1 = Active, 2 = Folded.
} Player;

void init_players(int count);
Player* get_players();
int get_player_count();
void remove_player(int index);  // Used to mark as quit

#endif // PLAYER_H