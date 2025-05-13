#include "game.h"
#include "utils.h"

// test methods----------------- START
// test methods----------------- END

int main() {
    print_intro();
    setup_game();
    while (!game_over()) {
        play_hand();           // Fake hands for now
        remove_quitters();     // Ask each player if they want to quit
    }
    show_final_message();
    return 0;
}