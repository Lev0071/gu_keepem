// handscore.c
#include "handscore.h"
#include "card.h"
#include <stdlib.h>  // for qsort if needed
#include <string.h> // for memset

int descending_card_rank(const void *a, const void *b) {
    Card *cardA = (Card *)a;
    Card *cardB = (Card *)b;
    return (cardB->rank - cardA->rank);
}

HandScore evaluate_5_card_hand(Card cards[5]) {
    HandScore score;
    memset(&score, 0, sizeof(score));  // set everything to 0

    // Step 1: count ranks and suits
    int rank_count[15] = {0};  // index 2–14 (ACE=14)  // 0 & 1 not counted
    int suit_count[4] = {0};  // index 2–14 (ACE=14)  // 0 & 1 not counted

    for (int i = 0; i < 5; i++) {
        rank_count[cards[i].rank]++;
        suit_count[cards[i].suit]++;
    }

    // Step 2: sort cards in decending order
    qsort(cards,5,sizeof(Card),descending_card_rank);


    // Step 3 : search for each hand type

    // Step 3.1 : search for Straight Flush or Royal Flush
    // Step 3.1.1 : Is it a flush?
    int high_card_of_straight = 0;

    int flush_suit = -1;
    for(int s=0;s<4;s++){
        if(suit_count[s]==5){
            flush_suit = s; // return one of  HEARTS(♥) = 0, DIAMONDS(♦) =1,CLUBS(♣)=2,SPADES(♠)=3
            break;
        }
    }

    int consecutive = 0;
    for(int r=14;r>=2;r--){
        if(rank_count[r]>0){
            consecutive++;
            if(consecutive == 5){
                break;
            }
        }else{consecutive=0;}
    }
    int is_straight = (consecutive == 5);

    if (is_straight) {
    // Find the highest card in the straight
    for (int r = 14; r >= 5; r--) {
        if (rank_count[r] && rank_count[r-1] && rank_count[r-2] && rank_count[r-3] && rank_count[r-4]) {
            high_card_of_straight = r;
            break;
        }
    }
}

    // Step 3.1.2 : Is it a special case, Ace=1: A-2-3-4-5:
    if(!is_straight && rank_count[14] == 1 && rank_count[2] == 1 && rank_count[3] == 1 && rank_count[4] == 1 && rank_count[5] == 1){
        is_straight = 1;
        high_card_of_straight = 5;
    }

    if (flush_suit != -1 && is_straight){
        score.hand_rank=HAND_STRAIGHT_FLUSH;
        score.main_values[0] = high_card_of_straight;
        return score;
    }

    // Step 3.2 : search for Four of a Kind
    for(int r=14;r>=2;r--){
        if(rank_count[r]==4){
            score.hand_rank=HAND_FOUR_OF_A_KIND;
            score.main_values[0]=r;
            for(int r2=14;r2>=2;r2--){
                if(r2!=r && rank_count[r2]>0){
                    score.kicker_values[0] = r2;
                    break; // Only one kicker, save time
                }
            }
            return score;
        }
    }

    // Step 3.3 : search for Full House hand
    int is_trip_rank = 0;
    int is_pair_rank = 0;
    for(int r=14;r>=2;r--){
        if(rank_count[r]==3){
            is_trip_rank = r;
        }
        if(rank_count[r]==2){
            is_pair_rank = r;
        }
    }
    if(is_trip_rank && is_pair_rank){
        score.hand_rank=HAND_FULL_HOUSE;
        score.main_values[0]=is_trip_rank;
        score.main_values[1]=is_pair_rank;
        return score;
    }

    // Step 3.4 : Flush?
    flush_suit = -1;
    for(int s=0;s<4;s++){
        if(suit_count[s]==5){
            flush_suit = s; // return one of  HEARTS(♥) = 0, DIAMONDS(♦) =1,CLUBS(♣)=2,SPADES(♠)=3
            break;
        }
    }
    if(flush_suit != -1){
        score.hand_rank = HAND_FLUSH;
        for (int i = 0; i < 5; i++) {
            score.main_values[i] = cards[i].rank;
        }
        return score;
    }

    // Step 3.5 : Straight?
    consecutive = 0;
    is_straight = 0;
    high_card_of_straight = 0;
    for(int r=14;r>=2;r--){
        if(rank_count[r]>0){
            consecutive++;
            if(consecutive == 5){
                is_straight =1;
                high_card_of_straight = r + 4; // currently r is pointing to the lowest of the straights
                break;
            }
        }else{consecutive=0;}
    }

    // Special case: A-2-3-4-5
    if(!is_straight && rank_count[14]==1 && rank_count[2]==1 && rank_count[3]==1 && rank_count[4]==1 && rank_count[5]==1){
        is_straight =1;
        high_card_of_straight = 5;
    }

    if(is_straight){
        score.hand_rank = HAND_STRAIGHT;
        score.main_values[0] = high_card_of_straight;
        return score;
    }


    // Step 3.6 : search for Three of a Kind
    int index = 0;
    for(int r=14;r>=2;r--){
        if(rank_count[r]==3){
            score.hand_rank=HAND_THREE_OF_A_KIND;
            score.main_values[0]=r;
            for(int r2=14;r2>=2;r2--){
                if(r2!=r && rank_count[r2]>0 && index < 2){
                    score.kicker_values[index] = r2;
                    index++; // // Two kickers
                }
            }
            return score;
        }
    }

    // Step 3.6: search for Two Pair
    int pair_one = 0;
    int pair_two = 0;

    for (int r = 14; r >= 2; r--) {
        if (rank_count[r] == 2) {
            if (pair_one == 0) {
                pair_one = r;
            } else if (pair_two == 0) {
                pair_two = r;
                break;  // Found two pairs, no need to continue
            }
        }
    }

    if (pair_one && pair_two) {
        score.hand_rank = HAND_TWO_PAIR;
        score.main_values[0] = pair_one > pair_two ? pair_one : pair_two;
        score.main_values[1] = pair_one < pair_two ? pair_one : pair_two;

        // Add one kicker (highest card not part of either pair)
        for (int r = 14; r >= 2; r--) {
            if (r != pair_one && r != pair_two && rank_count[r] > 0) {
                score.kicker_values[0] = r;
                break;
            }
        }

        return score;
    }

    // Step 3.7 search for a pair
    int pair_rank = 0;
    for (int r = 14; r >= 2; r--) {
        if (rank_count[r] == 2) { // If you have: K♠ K♦ 9♣ 5♥ 2♠ → pair_rank = 13 (King)
            pair_rank = r;
            break;
        }
    }

    if (pair_rank) {
        /// Found a pair
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
    index = 0;
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
    memset(&best_score, 0, sizeof(best_score)); // All elements of all members initialised to zero

    int combo[5];  // indices of selected cards

    // Generate all 21 combinations of 5 cards out of 7 (indices 0–6)
    for (int a = 0; a < 3; a++) { // (7_5) = 21
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

// -HAND_STRAIGHT_FLUSH
// -HAND_FOUR_OF_A_KIND
// -HAND_FULL_HOUSE
// -HAND_HIGH_CARD
// -HAND_ONE_PAIR
// -HAND_FLUSH



// HAND_TWO_PAIR
// HAND_THREE_OF_A_KIND
// HAND_STRAIGHT