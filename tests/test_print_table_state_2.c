#include "../src/game.h"
#include "../src/player.h"
#include "../src/gamestate.h"
#include "../src/utils.h"
#include <stdio.h>

int main() {
    // Setup minimal game state
    GameState g = { .stage = STAGE_FLOP, .pot = 100, .small_blind = 10, .big_blind = 20 };
    Player test_players[3] = {
        {.name = "Alice", .credits = 100, .current_bet = 10, .status = STATUS_ACTIVE, .hand = {{.rank='A', .suit='H'}, {.rank='K', .suit='S'}}},
        {.name = "Bob", .credits = 80, .current_bet = 20, .status = STATUS_FOLDED},
        {.name = "Carol", .credits = 90, .current_bet = 30, .status = STATUS_ALL_IN, .hand = {{.rank='9', .suit='D'}, {.rank='9', .suit='C'}}}
    };
    
    // Set up community cards
    Card table[5] = {
        {.rank='5', .suit='S'}, {.rank='7', .suit='D'}, {.rank='J', .suit='H'},
        {.rank='Q', .suit='C'}, {.rank='3', .suit='S'}
    };
    for (int i = 0; i < 5; i++) {
        extern Card table[5];
        table[i] = table[i]; // Copy to global if needed
    }

    // Simulate being Carol's turn (index 2)
    print_table_state(&g, test_players, 2);
    return 0;
}
