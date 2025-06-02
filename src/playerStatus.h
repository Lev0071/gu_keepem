#ifndef PLAYER_STATUS_H
#define PLAYER_STATUS_H

typedef enum playerStatus{
    STATUS_OUT = 0,     // Quit or out of credits
    STATUS_ACTIVE = 1,  // Currently in the hand
    STATUS_FOLDED = 2,   // Folded during this hand
    STATUS_ALL_IN = 3   // All-in and waiting for showdown
} PlayerStatus;   

typedef enum {
    ACTION_CHECK,
    ACTION_CALL,
    ACTION_BET,
    ACTION_RAISE,
    ACTION_ALL_IN,
    ACTION_FOLD
} ActionType;

#endif // PLAYER_STATUS_H