#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "utils.h"
#include "card.h"
#include "config.h"
#include "gamestate.h"
#include "handscore.h"
#include "playerStatus.h"
#include "pot.h"
#include <stdbool.h>

#define MAX_PLAYERS 8 
#define INITIAL_CREDITS 100 // Can be provided by the user in the next iteration
#define SMALL_GUESS 5
#define BIG_GUESS 10

static Card deck[52];       // the full deck
static Card table[5];       // 5 cards: flop (3), turn (1), river (1)
static int deck_size = 0;   // number of cards remaining
static int big_blind = 0;   
static int small_blind = 0;   
Player players[MAX_PLAYERS];
int player_count = 0;
static int dealer_index = 0;
static GameState g;

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

void setup_game(){      // Ask number of players,names,assign credits
    srand(time(NULL)); //Seed randon generator, make it truly random each time program is executed (based on time)

    do{
        player_count = get_integer_input("Please enter the number of players [2-8]: ");
    }while(player_count<2||player_count>MAX_PLAYERS);
    if(player_count == 2)printf("Heads-Up game selected\n");
    else printf("%i player game selected\n",player_count);
    
    int player_credits = get_integer_input("How many credits will each player start with?: ");
    big_blind = get_integer_input("What should the big blind be set to: ");
    if(big_blind>player_credits){
        do{
            printf("Cannot be bigger that players initial credits\n");
            big_blind = get_integer_input("What should the big blind be set to: ");
        }while(small_blind>big_blind);
    }
    
    small_blind = get_integer_input("What should the small blind be set to: ");

    if(small_blind>big_blind){
        do{
            printf("Cannot be bigger that the big blind\n");
            small_blind = get_integer_input("What should the small blind be set to: ");
        }while(small_blind>big_blind);
    }
    
    for (int i = 0; i < player_count; i++) {
        printf("Enter name for Player %d: ", i + 1);
        get_string_input("", players[i].name, sizeof(players[i].name));
        players[i].credits = player_credits;
        players[i].in_game = PLAYING;
    }

    dealer_index = rand() % player_count;
    #if DEBUG
    printf("\n===== DEBUG DUMP BEFORE EXIT =====\n");
    printf("Big Blind: %d\n", big_blind);
    printf("Small Blind: %d\n", small_blind);
    printf("Player Count: %d\n", player_count);
    for (int i = 0; i < player_count; i++) {
        printf("Player %d:\n", i + 1);
        printf("  Name:    %s\n", players[i].name);
        printf("  Credits: %d\n", players[i].credits);
        printf("  In Game: %s\n", players[i].in_game == PLAYING ? "PLAYING" : "QUIT");
    }
    printf("==================================\n");
    #endif
    
    g.big_blind = big_blind;
    g.small_blind = small_blind;
}

void print_table_cards(int count) {
    printf("Table Cards: ");
    for (int i = 0; i < count; i++) {
        print_card(table[i]);
        printf(" ");
    }
    printf("\n");
}

void deal_community_cards() {
    // Deal flop
    table[0] = deck[--deck_size];
    table[1] = deck[--deck_size];
    table[2] = deck[--deck_size];

    // Deal turn
    table[3] = deck[--deck_size];

    // Deal river
    table[4] = deck[--deck_size];
}

void deal_hole_cards(){
    init_deck(deck, &deck_size);
    //////////////
    // printf("\n===== deal_hole_cards =====\n");
    // printf("\n===== deck[52] =====\n");
    // printf("Cards in deck\n");
    // int ind = sizeof(deck) / sizeof(deck[0]);
    // for(int i = 0; i < ind; i++){

    //     if((i+1) % 13 == 0){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }
    //     else if(i == ind-1){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }else{
    //         print_card(deck[i]);
    //         printf(", ");
    //     }
    // }
    // printf("==================================\n");
    ///////////////////////////
    shuffle_deck(deck, deck_size);
    ///////////////////////////
    // printf("\n\n");
    // printf("\n===== shuffle_deck =====\n");
    // printf("\n===== deck[52] =====\n");
    // printf("Cards in deck\n");
    // ind = sizeof(deck) / sizeof(deck[0]);
    // for(int i = 0; i < ind; i++){

    //     if((i+1) % 13 == 0){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }
    //     else if(i == ind-1){
    //         print_card(deck[i]);
    //         printf("\n");
    //     }else{
    //         print_card(deck[i]);
    //         printf(", ");
    //     }
    // }
    // printf("==================================\n");
    // exit(0);
    ///////////////////////////
    for (int i = 0; i < player_count; i++) {
        if (!players[i].in_game || players[i].credits <= 0) continue;
        // printf("\n===== DECK Before HAND=====\n");
        // printf("Cards in deck\n");
        // for(int i = 0; i < deck_size; i++){

        //     if((i+1) % 13 == 0){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }
        //     else if(i == deck_size-1){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }else{
        //         print_card(deck[i]);
        //         printf(", ");
        //     }
        // }
        // printf("==================================\n");
        players[i].hand[0] = deck[--deck_size];
        players[i].hand[1] = deck[--deck_size];
        // printf("\n===== DECK After HAND=====\n");
        // printf("Cards in deck\n");
        // for(int i = 0; i < deck_size; i++){

        //     if((i+1) % 13 == 0){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }
        //     else if(i == deck_size-1){
        //         print_card(deck[i]);
        //         printf("\n");
        //     }else{
        //         print_card(deck[i]);
        //         printf(", ");
        //     }
        // }
        // printf("==================================\n");
    }
}



void remove_quitters(){
    for(int i=0;i<player_count;i++){
        if(!players[i].in_game||players[i].credits <=0) continue;
        printf("%s, do you want to quit ? (1= Yes,0= No):",players[i].name);
        int choice = get_integer_input("");
        if(choice == 1){
            players[i].in_game = 0;
            printf("%s has left the game.\n",players[i].name);
        }
    }
}

void play_hand() { 
    printf("\n🎲 --- Starting a new hand ---\n");
    printf("🃏 Dealer: %s\n", players[dealer_index].name);
    wait_for_enter("\nPress Enter to begin...\n");

    // Step 1: Reset player statuses and bets
    for (int i = 0; i < player_count; i++) {
        players[i].current_bet = 0;
        players[i].status = STATUS_ACTIVE;
    }

    // Step 2: Post small and big blind (e.g., 10 and 20)
    int sb_index = (dealer_index + 1) % player_count;
    int bb_index = (dealer_index + 2) % player_count;
    post_blinds(sb_index, bb_index, &g);


    // Step 3: Deal hole cards to each active player
    deal_hole_cards();

    // Step 4: Deal all 5 community cards (flop, turn, river)
    deal_community_cards();

    
    // Step 5: Run prediction & betting rounds (to be implemented)
    run_prediction_round(STAGE_PREFLOP, &g);
    run_prediction_round(STAGE_FLOP, &g);
    run_prediction_round(STAGE_TURN, &g);
    run_prediction_round(STAGE_RIVER, &g);

    // Step 6: Resolve showdown
    resolve_betting_round(players, player_count, table);

    // Step 7: Rotate dealer
    dealer_index = (dealer_index + 1) % player_count;
}




int game_over(){
    int active = 0;
    for(int i =0;i<player_count;i++){
        if(players[i].in_game && players[i].credits > 0) active++; // as long as all players in the game have credit --> active
    }
    return active <= 1;  
}

void show_final_message(){     // Print game over message
    for (int i = 0; i < player_count; i++) {
        if (players[i].in_game && players[i].credits > 0) {
            printf("\n🎉 %s is the final winner with %d credits! 🎉\n", players[i].name, players[i].credits);
            return;
        }
    }
    printf("\nAll players have quit or lost. No winner this time!\n");
}

void run_prediction_round(RoundStage stage, GameState *g) {
    g->stage = stage;
    printf("\n🔔 Starting %s round!\n", stage_name(stage));

    int active_players = 0;
    for (int i = 0; i < player_count; i++) {
        if (players[i].status == STATUS_ACTIVE || players[i].status == STATUS_ALL_IN)
            active_players++;
    }

    if (active_players <= 1) {
        printf("Only one player remaining. Skipping betting.\n");
        return;
    }

    // Reset per-round variables
    g->current_bet = 0;
    g->last_raise_amount = g->big_blind;

    int starting_index = (dealer_index + 1) % player_count;

    int consecutive_calls = 0;
    int last_to_raise = -1;
    int current_turn = starting_index;

    while (consecutive_calls < active_players) {
        Player *p = &players[current_turn];

        if (p->in_game != PLAYING || p->status != STATUS_ACTIVE || p->credits == 0) {
            current_turn = (current_turn + 1) % player_count;
            continue;
        }

        int call_amount = g->current_bet - p->current_bet;
        //printf("\n%s's turn (Credits: %d)\n", p->name, p->credits);
        print_table_state(g, players, current_turn);
        printf("Current bet: %d | Your bet: %d | Call = %d\n", g->current_bet, p->current_bet, call_amount);
        printf("1. Call | 2. Raise | 3. All-In | 4. Fold\n");

        int choice = get_integer_input("Enter your action: ");
        if (choice == 1 && is_valid_action(p, g, ACTION_CALL)) {
            int amount = (call_amount > p->credits) ? p->credits : call_amount;
            p->credits -= amount;
            p->current_bet += amount;
            g->pot += amount;
            printf("%s calls %d.\n", p->name, amount);
            consecutive_calls++;
        }
        else if (choice == 2 && is_valid_action(p, g, ACTION_RAISE)) {
            int raise_amount = get_integer_input("Enter raise amount: ");
            if (raise_amount < g->last_raise_amount) raise_amount = g->last_raise_amount;
            int total_bet = g->current_bet + raise_amount;
            int diff = total_bet - p->current_bet;
            if (diff > p->credits) diff = p->credits;

            p->credits -= diff;
            p->current_bet += diff;
            g->pot += diff;

            g->last_raise_amount = raise_amount;
            g->current_bet = p->current_bet;
            last_to_raise = current_turn;
            consecutive_calls = 1;
            printf("%s raises by %d.\n", p->name, raise_amount);
        }
        else if (choice == 3 && is_valid_action(p, g, ACTION_ALL_IN)) {
            int amount = p->credits;
            p->current_bet += amount;
            g->pot += amount;
            p->credits = 0;
            p->status = STATUS_ALL_IN;
            printf("%s goes all-in with %d.\n", p->name, amount);
            if (p->current_bet > g->current_bet) {
                g->last_raise_amount = p->current_bet - g->current_bet;
                g->current_bet = p->current_bet;
                last_to_raise = current_turn;
                consecutive_calls = 1;
            } else {
                consecutive_calls++;
            }
        }
        else if (choice == 4 && is_valid_action(p, g, ACTION_FOLD)) {
            p->status = STATUS_FOLDED;
            printf("%s folds.\n", p->name);
            active_players--;
        } else {
            printf("Invalid choice or action not allowed.\n");
            continue;
        }

        if (active_players <= 1) break;
        current_turn = (current_turn + 1) % player_count;
    }

    printf("✅ Betting round complete. Pot: %d\n", g->pot);
}


bool is_valid_action(Player *p, GameState *g, ActionType action) {
    if (p->in_game != PLAYING || p->status != STATUS_ACTIVE || p->credits <= 0) {
        return false;
    }

    int call_amount = g->current_bet - p->current_bet;

    switch (action) {
        case ACTION_CHECK:
            return call_amount == 0;

        case ACTION_CALL:
            return call_amount > 0 && p->credits >= call_amount;

        case ACTION_BET:
            return g->current_bet == 0 && p->credits > 0;

        case ACTION_RAISE: {
            int max_possible_raise_amount = p->credits - call_amount;
            return g->current_bet > 0 && max_possible_raise_amount >= g->last_raise_amount;
        }

        case ACTION_ALL_IN:{
            if (p->credits <= 0) return false;

            if (g->current_bet == 0) {
                // All-in as a bet
                return true;
            } else if (p->credits + p->current_bet > g->current_bet) {
                // All-in as a raise
                return true;
            } else if (p->credits + p->current_bet == g->current_bet) {
                // All-in as a call
                return true;
            } else {
                // All-in is less than call — still allowed, but not re-raisable
                return true;
            }
        }

        case ACTION_FOLD:
            return p->status == STATUS_ACTIVE;

        default:
            return false;
    }
}

int rank_active_players(Player players[], int num_players, Card table[5], RankedPlayer ranked[]) {
    int count = 0;
    for (int i = 0; i < num_players; i++) {
        if (players[i].status == STATUS_ACTIVE || players[i].status == STATUS_ALL_IN) {
            ranked[count].player = &players[i];
            ranked[count].score = evaluate_best_hand(players[i].hand, table);
            count++;
        }
    }

    int cmp(const void *a, const void *b) { // see cmp tech-talk
        RankedPlayer *ra = (RankedPlayer *)a;
        RankedPlayer *rb = (RankedPlayer *)b;
        return -compare_hand_scores(ra->score, rb->score); // descending
    }

    qsort(ranked, count, sizeof(RankedPlayer), cmp);
    return count;
}

// cmp tech-talk
/*
 * This comparison approach is used because we're not comparing simple integers,
 * but rather complex hand score structures (HandScore), which may contain multiple
 * fields like rank, high card, kickers, etc. C does not allow direct comparison
 * of structs using operators like > or <, so we rely on a custom comparison function:
 *
 *     int compare_hand_scores(HandScore a, HandScore b);
 *
 * This function returns:
 *     > 0  → a is better than b
 *     == 0 → a and b are equal
 *     < 0  → b is better than a
 *
 * In the local cmp() function used for qsort, we negate the result:
 *
 *     return -compare_hand_scores(...);
 *
 * This reverses the order, so stronger hands appear first (descending order).
 *
 * qsort only cares about the sign of the return value, not the exact number.
 * So whether compare_hand_scores() returns -1/0/+1 or -42/0/+999 doesn't matter,
 * as long as the sign is consistent and meaningful.
 */


// Distributes chips from each pot to the top-ranked eligible players.
// It checks each pot, finds the winners, and splits the pot accordingly.
void resolve_pots_by_rank(Pot pots[], int pot_count, RankedPlayer ranked[], int ranked_count) {
    for (int p = 0; p < pot_count; p++) {
        Pot *pot = &pots[p];
        Player *winners[MAX_ELIGIBLE];  // Array to hold winners of this pot
        int winner_count = 0;

        // Iterate through players sorted by hand strength
        for (int i = 0; i < ranked_count; i++) {
            Player *candidate = ranked[i].player;

            // Check if candidate is eligible for this pot
            int eligible = 0;
            for (int j = 0; j < pot->num_players; j++) {
                if (pot->eligible_players[j] == candidate) {
                    eligible = 1;
                    break;
                }
            }

            // Skip players not eligible for this pot
            if (!eligible) continue;

            if (winner_count == 0) {
                // First eligible winner found
                winners[winner_count++] = candidate;
            } else {
                // Compare with the current top player's score
                HandScore top = ranked[0].score;
                if (compare_hand_scores(ranked[i].score, top) == 0) {
                    // Tie — add to winner list
                    winners[winner_count++] = candidate;
                } else {
                    // Lower score — stop looking, only top ties get the pot
                    break;
                }
            }
        }

        // Divide pot amount equally among winners
        int share = pot->amount / winner_count;
        for (int i = 0; i < winner_count; i++) {
            winners[i]->credits += share;

            // Output the result for this winner
            printf("🏆 %s wins %d from %s pot\n",
                   winners[i]->name,
                   share,
                   (p == 0) ? "main" : "side");
        }
    }
}

void print_player_line(Player *p, int is_current) {
    const char *status_str;
    switch (p->status) {
        case STATUS_ACTIVE: status_str = "Active"; break;
        case STATUS_FOLDED: status_str = "Folded"; break;
        case STATUS_ALL_IN: status_str = "All-In"; break;
        default: status_str = "Unknown"; break;
    }

    printf("%s%-10s | 💰 %3d | Bet %3d | %s | ",
           is_current ? "👉 " : "   ",
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

void print_table_state(GameState *g, Player players[], int current_index) {
    printf("\n========= TABLE STATE: %s =========\n", stage_to_string(g->stage));
    for (int i = 0; i < player_count; i++) {
        print_player_line(&players[i], i == current_index);
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



void resolve_betting_round(Player players[], int num_players, Card table[5]) {
    Pot pots[MAX_POTS];
    int pot_count = 0;

    // Build main + side pots
    build_side_pots(pots, &pot_count, players, num_players);

    // Rank players based on hand
    RankedPlayer ranked[MAX_PLAYERS];
    int ranked_count = rank_active_players(players, num_players, table, ranked);

    // Distribute pot(s)
    resolve_pots_by_rank(pots, pot_count, ranked, ranked_count);

    // Reset player bets for next round
    for (int i = 0; i < num_players; i++) {
        players[i].current_bet = 0;
    }
}

void post_blinds(int sb_index, int bb_index, GameState *g) {
    if (!players[sb_index].in_game || players[sb_index].credits <= 0) return;
    if (!players[bb_index].in_game || players[bb_index].credits <= 0) return;

    int sb_amount = (players[sb_index].credits >= g->small_blind) ? g->small_blind : players[sb_index].credits;
    players[sb_index].credits -= sb_amount;
    players[sb_index].current_bet += sb_amount;

    int bb_amount = (players[bb_index].credits >= g->big_blind) ? g->big_blind : players[bb_index].credits;
    players[bb_index].credits -= bb_amount;
    players[bb_index].current_bet += bb_amount;

    g->current_bet = bb_amount;
    g->last_raise_amount = g->big_blind;

    printf("💰 Small blind posted by %s (%d credits)\n", players[sb_index].name, sb_amount);
    printf("💰 Big blind posted by %s (%d credits)\n", players[bb_index].name, bb_amount);
}

void print_table_state(GameState *g, Player players[], int current_index) {
    printf("\n========= TABLE STATE: %s =========\n", stage_to_string(g->stage));
    for (int i = 0; i < player_count; i++) {
        print_player_line(&players[i], i == current_index);
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
