#ifndef PLAYER_STATUS_H
#define PLAYER_STATUS_H

typedef enum playerStatus {
    OUT = 0,
    ACTIVE = 1,
    FOLDED = 2
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