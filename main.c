#include "game.h"
#include "utils.h"

// test methods----------------- START
#include "player.h"
#include <stdio.h>
int player_countt = 3;
static Player playerss[3] = {
    {"Alice", 50, 1},
    {"Bob", 100, 1},
    {"Charlie", 75, 1}
};

int game_over2(){
    int active = 0;
    for(int i =0;i<player_countt;i++){
        if(playerss[i].in_game && playerss[i].credits > 0) active++; // as long as all players in the game have credit --> active
    }
    return active <= 1;  
}

void run_game_over_test() {
    for (int round = 0; round < player_countt; round++) {
        printf("\n--- Round %d ---\n", round + 1);
        printf("Active players before: %d\n", 3 - round);

        int over = game_over2();
        printf("game_over() returned: %d\n", over);

        // Simulate one player quitting
        for (int i = 0; i < player_countt; i++) {
            if (playerss[i].in_game) {
                playerss[i].in_game = 0;
                printf("%s has quit the game.\n", playerss[i].name);
                break; // ensures each quit at each run oof the loop
            }
        }
    }
}
// test methods----------------- END

int main() {
    print_intro();
    //setup_game();
    while (!game_over2()) {
        run_game_over_test();
        continue;
        play_hand();           // Fake hands for now
        remove_quitters();     // Ask each player if they want to quit
    }
    show_final_message();
    return 0;
}