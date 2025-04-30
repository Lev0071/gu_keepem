#ifndef STATUS_H
#define STATUS_H

typedef enum playerStatus{
    STATUS_OUT = 0,     // Quit or out of credits
    STATUS_ACTIVE = 1,  // Currently in the hand
    STATUS_FOLDED = 2   // Folded during this hand
} Status;      

#endif