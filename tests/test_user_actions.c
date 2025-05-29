// #include "../src/player.h"
// #include "../src/gamestate.h"
// #include "../src/playerStatus.h"

// #include "../src/handscore.h"
// #include "../src/card.h"
// #include "../src/utils.h"
// #include "../src/player.h"


// #include <assert.h>
// #include <stdio.h>
// #include <assert.h>
// #include <stdio.h>
// #include <time.h>
// #include <string.h>
// #include <stdlib.h>
#include "../src/player.h"
#include "../src/game.h"
#include "../src/gamestate.h"
#include "../src/playerStatus.h"
#include <assert.h>
#include <stdio.h>

// ACTION_CHECK
void test_action_check() {
    // ✅ Case: No current bet
    Player anna = {
        .credits = 500,
        .current_bet = 0,
        .in_game = PLAYING,
        .status = STATUS_ACTIVE
    };
    GameState game_state = {
        .current_bet = 0
    };
    printf("Player: Anna\n");
    printf("credits: %i\n",anna.credits);
    printf("her current bet: %i\n",anna.current_bet);
    printf("latest bet in hand: %i\n",game_state.current_bet);
    printf("in the game: %s\n",anna.in_game == PLAYING ? "yes":"no");
    printf("in the hand: %s\n",anna.in_game == STATUS_ACTIVE ? "yes":"no");
    printf("Can Anna Check ? %s\n",is_valid_action(&anna, &game_state, ACTION_CHECK) ? "yes":"no");
    assert(is_valid_action(&anna, &game_state, ACTION_CHECK) == true);
    

    // ❌ Case: There's a bet to match
    game_state.current_bet = 50; // Now there's a bet on the table
    printf("latest bet in hand: %i\n",game_state.current_bet);
    assert(is_valid_action(&anna, &game_state, ACTION_CHECK) == false);
    // ⚠️ Edge: Player already matched bet exactly (call_amount == 0)
    anna.current_bet = 50;
    printf("Anna's current bet: %i\n",anna.current_bet);
    printf("latest bet in hand: %i\n",game_state.current_bet);
     printf("Can Anna Check ? %s\n",is_valid_action(&anna, &game_state, ACTION_CHECK) ? "yes":"no");
     assert(is_valid_action(&anna, &game_state, ACTION_CHECK) == true);

}

// ACTION_CALL
void test_action_call() {
    // ✅ Case: call_amount > 0, player has enough credits
    Player anna = {
        .credits = 500,
        .current_bet = 0,
        .in_game = PLAYING,
        .status = STATUS_ACTIVE
    };
    GameState game_state = {
        .current_bet = 99
    };
    printf("Player: Anna\n");
    printf("credits: %i\n",anna.credits);
    printf("her current bet: %i\n",anna.current_bet);
    printf("latest bet in hand: %i\n",game_state.current_bet);
    printf("in the game: %s\n",anna.in_game == PLAYING ? "yes":"no");
    printf("in the hand: %s\n",anna.in_game == STATUS_ACTIVE ? "yes":"no");
    printf("Can Anna CALL ? %s\n",is_valid_action(&anna, &game_state, ACTION_CALL) ? "yes":"no");
    assert(is_valid_action(&anna, &game_state, ACTION_CALL) == true);
    // ❌ Case: call_amount > 0, not enough credits
    // ⚠️ Edge: call_amount == player's credits exactly (Call = All-in)
}

// ACTION_BET
void test_action_bet() {
    // ✅ Case: current_bet == 0, player has credits
    // ❌ Case: current_bet > 0 (someone already bet)
    // ⚠️ Edge: credits == 1 (minimum bet possible)
}

// ACTION_RAISE
void test_action_raise() {
    // ✅ Case: current_bet > 0, player has enough for call + raise
    // ❌ Case: player has just enough to call but not raise
    // ⚠️ Edge: player raise = all-in but doesn’t meet minimum raise
}

// ACTION_ALL_IN
void test_action_all_in() {
    // ✅ Case: all-in used as a bet (current_bet == 0)
    // ✅ Case: all-in used to call exactly
    // ⚠️ Case: all-in < call (can’t raise, but still allowed)
}

// ACTION_FOLD
void test_action_fold() {
    // ✅ Case: Player is active
    // ❌ Case: Player already folded or out
}

// Main
int main() {
    test_action_check();
    test_action_call();
    test_action_bet();
    test_action_raise();
    test_action_all_in();
    test_action_fold();

    printf("All tests passed.\n");
    return 0;
}

// from gu_keepem/ root
//gcc -o run_user_actions.exe tests/test_user_actions.c src/player.c src/game.c src/card.c src/utils.c src/handscore.c \-Isrc

// from inside tests/
// gcc -o run_user_actions.exe test_user_actions.c ../src/player.c ../src/game.c ../src/card.c ../src/utils.c ../src/handscore.c -I../src
