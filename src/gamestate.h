#ifndef GAMESTATE_H
#define GAMESTATE_H

extern int last_raise_amount;  // size of last raise made this round

typedef enum {
    STAGE_PREFLOP,
    STAGE_FLOP,
    STAGE_TURN,
    STAGE_RIVER,
    STAGE_SHOWDOWN
} RoundStage;

typedef struct {
    RoundStage stage;
    int pot;
    int dealer_index;
    int current_bet;
    int small_blind;
    int big_blind;
    int last_raise;
} GameState;

#endif // GAMESTATE_H