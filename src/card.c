#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"

void init_deck(Card *deck, int *deck_size) {
    int index = 0;
    for (int suit = HEARTS; suit <= SPADES; suit++) {
        for (int rank = TWO; rank <= ACE; rank++) {
            deck[index].suit = (Suit)suit;
            deck[index].rank = (Rank)rank;
            index++;
        }
    }
    *deck_size = index;
    // printf("\n===== DECK DUMP BEFORE EXIT =====\n");
    // printf("Cards in deck\n");
    // for(int i = 0; i < index; i++){

    //     if((i+1) % 13 == 0){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }
    //     else if(i == index){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }else{
    //         print_card(deck[i]);
    //         printf(", ");
    //     }
    // }
    // printf("==================================\n");
    // exit(0);
}

void shuffle_deck(Card *deck, int deck_size) { // Fisher-Yates (Knuth Shuffle), more random
    for (int i = deck_size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // j in [0, i]
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void print_card(Card card) {
    
    const char *rank_names[] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "J", "Q", "K", "A"
    };

    #if USE_UNICODE
        const char *suit_symbols[] = {"♥", "♦", "♣", "♠"};
    #else
        const char *suit_symbols[] = {"[H]", "[D]", "[C]", "[S]"};
    #endif

    // Ranks start from 2 → rank - 2 gives correct index
    printf("%s%s", rank_names[card.rank - 2], suit_symbols[card.suit]);
}
