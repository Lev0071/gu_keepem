#ifndef CONSTANTS_H
#define CONSTANTS_H

// Game configuration
#define MAX_PLAYERS 8
#define MAX_NAME_LENGTH 50

// Betting configuration
#define MAX_POTS 5
#define MAX_ELIGIBLE 8

// Card configuration
#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_RANKS 13

// Game stages
typedef enum {
    STAGE_PREFLOP,
    STAGE_FLOP,
    STAGE_TURN,
    STAGE_RIVER,
    STAGE_SHOWDOWN
} RoundStage;

#endif // CONSTANTS_H