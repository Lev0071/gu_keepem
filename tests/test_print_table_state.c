#include <stdio.h>

typedef enum {
    STATUS_ACTIVE,
    STATUS_FOLDED,
    STATUS_ALL_IN
} PlayerStatus;

typedef struct {
    char rank;
    char suit;
} Card;

typedef struct {
    int credits;
    int current_bet;
    PlayerStatus status;
    char name[20];
    Card hand[2];
} Player;

typedef enum {
    STAGE_PREFLOP,
    STAGE_FLOP,
    STAGE_TURN,
    STAGE_RIVER,
    STAGE_SHOWDOWN
} RoundStage;

typedef struct {
    int big_blind;
    int small_blind;
    int current_bet;
    int last_raise_amount;
    int pot;
    RoundStage stage;
} GameState;

#define MAX_PLAYERS 4
int dealer_index = 1;
// Globals
int player_count = MAX_PLAYERS;
Card table[5] = {
    {'5', 'H'}, {'7', 'D'}, {'J', 'S'},
    {'Q', 'C'}, {'3', 'S'}
};

void print_card(Card card) {
    printf("[%c%c]", card.rank, card.suit);
}

void print_player_line(Player *p, int is_current,int is_dealer) {
    const char *status_str;
    switch (p->status) {
        case STATUS_ACTIVE: status_str = "Active"; break;
        case STATUS_FOLDED: status_str = "Folded"; break;
        case STATUS_ALL_IN: status_str = "All-In"; break;
        default: status_str = "Unknown"; break;
    }

    // Prefixes
    char prefix[4] = "   ";
    if (is_dealer) prefix[0] = 'D';
    if (is_current) prefix[1] = '*';

    printf("%s %-10s | 💰 %3d | Bet %3d | %s | ",
           prefix,
           p->name,
           p->credits,
           p->current_bet,
           status_str
    );

    if (p->status == STATUS_FOLDED) {
        printf("[Folded]\n");
    } else {
        print_card(p->hand[0]);
        printf(" ");
        print_card(p->hand[1]);
        printf("\n");
    }
}

const char* stage_to_string(RoundStage stage) {
    switch (stage) {
        case STAGE_PREFLOP: return "Pre-Flop";
        case STAGE_FLOP: return "Flop";
        case STAGE_TURN: return "Turn";
        case STAGE_RIVER: return "River";
        case STAGE_SHOWDOWN: return "Showdown";
        default: return "Unknown";
    }
}

void print_table_state(GameState *g, Player players[], int current_index) {
    printf("\n========= TABLE STATE: %s =========\n", stage_to_string(g->stage));
    for (int i = 0; i < player_count; i++) {
        print_player_line(&players[i], i == current_index,i==dealer_index);
    }
    printf("Community Cards: ");
    int cards_to_show = 0;
    if (g->stage == STAGE_FLOP) cards_to_show = 3;
    else if (g->stage == STAGE_TURN) cards_to_show = 4;
    else if (g->stage == STAGE_RIVER || g->stage == STAGE_SHOWDOWN) cards_to_show = 5;

    for (int i = 0; i < cards_to_show; i++) {
        print_card(table[i]);
        printf(" ");
    }
    printf("\nPot: %d\n", g->pot);
    printf("=======================================\n");
}

int main() {
    GameState g = { .stage = STAGE_FLOP, .pot = 150 };
    Player players[MAX_PLAYERS] = {
        { .credits = 100, .current_bet = 10, .status = STATUS_ACTIVE, .name = "Alice", .hand = {{'A', 'H'}, {'K', 'S'}} },
        { .credits = 80, .current_bet = 20, .status = STATUS_FOLDED, .name = "Bob", .hand = {{'9', 'D'}, {'2', 'C'}} },
        { .credits = 90, .current_bet = 30, .status = STATUS_ALL_IN, .name = "Carol", .hand = {{'9', 'D'}, {'9', 'C'}} },
        { .credits = 70, .current_bet = 0, .status = STATUS_ACTIVE, .name = "Dave", .hand = {{'5', 'C'}, {'4', 'D'}} }
    };

    print_table_state(&g, players, 2);
    return 0;
}


// gcc -o test_print_table_state test_print_table_state.c