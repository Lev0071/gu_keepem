// handscore.h
#ifndef HAND_SCORE_H
#define HAND_SCORE_H
#include "card.h"

// Hand rank constants — higher number = stronger hand
#define HAND_HIGH_CARD         0   // No combination, just high card
#define HAND_ONE_PAIR          1   // One pair
#define HAND_TWO_PAIR          2   // Two different pairs
#define HAND_THREE_OF_A_KIND   3   // Three cards of the same rank
#define HAND_STRAIGHT          4   // Five cards in sequence
#define HAND_FLUSH             5   // Five cards of the same suit
#define HAND_FULL_HOUSE        6   // Three of a kind + a pair
#define HAND_FOUR_OF_A_KIND    7   // Four cards of the same rank
#define HAND_STRAIGHT_FLUSH    8   // Straight + Flush

typedef struct handscore {
    int hand_rank;
    /*
        One of the HAND_XXX constants above, e.g.:
        HAND_FULL_HOUSE, HAND_FLUSH, etc.
        Higher is better.
    */

    int main_values[5];
    /*
        Primary values that define the hand:
        - For One Pair:        [pair_rank]
        - For Two Pair:        [higher_pair, lower_pair]
        - For Three of a Kind: [trip_rank]
        - For Full House:      [trip_rank, pair_rank]
        - For Four of a Kind:  [quad_rank]
        - For Straight/Flush:  [highest_card_rank]
        - For High Card:       top 5 cards, descending
    */

    int kicker_values[5];
    /*
        Tie-breaker cards, if main_values are equal:
        - For One Pair:        highest 3 other cards
        - For Two Pair:        5th card (unpaired)
        - For Trips:           2 highest remaining
        - For Quads:           single kicker
        - For High Card:       already part of main_values, no kicker needed
    */
    Card best_hand[5];  // The winning hand
} HandScore;


HandScore evaluate_5_card_hand(Card cards[5]);
HandScore evaluate_best_hand(Card hole[2], Card table[5]);
int compare_hand_scores(HandScore a, HandScore b);
int descending(const void *a, const void *b); // for qsort in evaluate_5_card_hand
void print_hand_score(HandScore s);

#endif // HAND_SCORE_H
