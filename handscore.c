#include "handscore.h"
#include "card.h"
#include <stdlib.h>  // for qsort if needed
#include <string.h> // for memset

HandScore evaluate_5_card_hand(Card cards[5]) {
    HandScore score;
    memset(&score, 0, sizeof(score));  // set everything to 0

    // Step 1: count ranks
    int rank_count[15] = {0};  // index 2–14 (ACE=14)

    for (int i = 0; i < 5; i++) {
        rank_count[cards[i].rank]++;
    }

    // Step 2: search for a pair
    int pair_rank = 0;
    for (int r = 14; r >= 2; r--) {
        if (rank_count[r] == 2) {
            pair_rank = r;
            break;
        }
    }

    if (pair_rank) {
        // Found a pair
        score.hand_rank = HAND_ONE_PAIR;
        score.main_values[0] = pair_rank;

        // Add kickers (3 highest remaining)
        int kicker_index = 0;
        for (int r = 14; r >= 2 && kicker_index < 3; r--) {
            if (r != pair_rank && rank_count[r] > 0) {
                for (int i = 0; i < rank_count[r] && kicker_index < 3; i++) {
                    score.kicker_values[kicker_index++] = r;
                }
            }
        }

        return score;
    }

    // No pair found, fallback to high card
    score.hand_rank = HAND_HIGH_CARD;

    // Fill top 5 card ranks as main_values (descending)
    int index = 0;
    for (int r = 14; r >= 2 && index < 5; r--) {
        for (int i = 0; i < rank_count[r] && index < 5; i++) {
            score.main_values[index++] = r;
        }
    }

    return score;
}

HandScore evaluate_best_hand(Card hole[2], Card table[5]) {
    Card all[7];
    memcpy(&all[0], hole, 2 * sizeof(Card));
    memcpy(&all[2], table, 5 * sizeof(Card));

    HandScore best_score;
    memset(&best_score, 0, sizeof(best_score));

    int combo[5];  // indices of selected cards

    // Generate all 21 combinations of 5 cards out of 7 (indices 0–6)
    for (int a = 0; a < 3; a++) {
        for (int b = a + 1; b < 4; b++) {
            for (int c = b + 1; c < 5; c++) {
                for (int d = c + 1; d < 6; d++) {
                    for (int e = d + 1; e < 7; e++) {
                        Card hand[5] = { all[a], all[b], all[c], all[d], all[e] };
                        HandScore score = evaluate_5_card_hand(hand);

                        // First run or if this score is better
                        if (best_score.hand_rank < score.hand_rank ||
                            (best_score.hand_rank == score.hand_rank &&
                            compare_hand_scores(score, best_score) > 0)) {
                            best_score = score;
                            memcpy(best_score.best_hand, hand, 5 * sizeof(Card));
                        }
                    }
                }
            }
        }
    }
    
    return best_score;
}

int compare_hand_scores(HandScore a, HandScore b) {
    for (int i = 0; i < 5; i++) {
        if (a.main_values[i] > b.main_values[i]) return 1;
        if (a.main_values[i] < b.main_values[i]) return -1;
    }
    for (int i = 0; i < 5; i++) {
        if (a.kicker_values[i] > b.kicker_values[i]) return 1;
        if (a.kicker_values[i] < b.kicker_values[i]) return -1;
    }
    return 0;
}


// HandScore evaluate_5_card_hand(Card cards[5]) {
//     HandScore score;
    
//     // Step 1: Initialize to High Card
//     score.hand_rank = HAND_HIGH_CARD;
//     for (int i = 0; i < 5; i++) {
//         score.main_values[i] = 0;
//         score.kicker_values[i] = 0;
//     }

//     // Later: sort cards, analyze hand, update score

//     return score;
// }