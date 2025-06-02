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

// gcc -o gu_keepem main.c game.c player.c utils.c card.c handscore.c
// gcc -o gu_keepem src/main.c src/game.c src/player.c src/utils.c src/card.c src/handscore.c src/pot.c -Isrc -Wall -Wextra

