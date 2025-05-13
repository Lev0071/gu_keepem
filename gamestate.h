#ifndef GAMESTATE_H
#define GAMESTATE_H

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
} GameState;

#endif // GAMESTATE_H