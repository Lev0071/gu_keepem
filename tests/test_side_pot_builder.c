#include "../src/pot.h"
#include "../src/player.h"
#include <stdio.h>
#include <string.h>

int main() {
    Player players[3] = {
        {.name = "Alice", .current_bet = 100 },
        {.name = "Bob", .current_bet = 200 },
        {.name = "Yasin", .current_bet = 300 },
    };

    Pot pots[MAX_POTS];
    int pot_count = 0;

    build_side_pots(pots,&pot_count,players,3);

    printf("\n==== Scenario 1: Uniform Layered Stack ====\n");

    for(int i = 0;i<pot_count;i++){
        printf("Side Pot %d: ",i );
        print_pot(&pots[i]);
    }

    Player players_group2[3] = {
        {.name = "Alice", .current_bet = 100 },
        {.name = "Bob", .current_bet = 150 },
        {.name = "Yasin", .current_bet = 300 },
    };

    pot_count = 0;

    build_side_pots(pots,&pot_count,players_group2,3);

    printf("\n==== Scenario 2: Uneven Contribution (Bob = 150) ====\n");
    for(int i = 0;i<pot_count;i++){
        printf("Side Pot %d: ",i );
        print_pot(&pots[i]);
    }

    return 0;
}

// gcc -o test_side_pot_builder tests/test_side_pot_builder.c src/pot.c src/player.c -Isrc
// ./test_side_pot_builder        # Linux/macOS
// test_side_pot_builder.exe      # Windows

// gcc -o test_side_pot_builder test_side_pot_builder.c ../src/pot.c ../src/player.c -Isrc
// ./test_side_pot_builder        # Linux/macOS
// test_side_pot_builder.exe      # Windows