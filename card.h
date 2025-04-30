#ifndef CARD_H
#define CARD_H

// Enum for the suit of a card
typedef enum suit{
    HEARTS,     // ♥
    DIAMONDS,   // ♦
    CLUBS,      // ♣
    SPADES      // ♠
} Suit;

// Enum for the rank/value of a card
typedef enum rank{
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

typedef struct card {
    Rank rank;  // 2-14 (where 11=Jack, 12=Queen, 13=King, 14=Ace)
    Suit suit;  // 0–3 (0=Hearts, 1=Diamonds, 2=Clubs, 3=Spades)
} Card;

void init_deck(Card *deck, int *deck_size); // Initialize a 52-card deck in order
void shuffle_deck(Card *deck, int deck_size); // Randomly shuffle a deck of cards
void print_card(Card card); // Print a card like "J♥" or "10♣"

#endif // CARD_H