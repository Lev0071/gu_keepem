#include "../src/pot.h"
#include "../src/player.h"
#include <stdio.h>
#include <string.h>

int main(){
    Player alice = {.name = "Alice", .credits = 0};
    Player bob = {.name = "Bob", .credits = 0};
    Player yasin = {.name = "Yasin", .credits = 0};

    Pot main_pot;
    init_pot(&main_pot);

    main_pot.amount = 300;
    add_eligible_player(&main_pot,&alice);
    add_eligible_player(&main_pot,&bob);
    add_eligible_player(&main_pot,&yasin);

    print_pot(&main_pot);
}
// gcc -o test_pot_contributions tests/test_pot_contributions.c src/pot.c src/player.c -Isrc
// ./test_pot_contributions
// test_pot_contributions.exe

// gcc -o test_pot_contributions test_pot_contributions.c ../src/pot.c ../src/player.c -Isrc
// ./test_pot_contributions
// test_pot_contributions.exe