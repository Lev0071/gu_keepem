#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // for tolower()

int get_integer_input(const char *prompt){
    int value;
    printf("%s",prompt);
    scanf("%d",&value);
    int c;
    while((c=getchar()) != '\n' && c!= EOF);
    return value;
}

void get_string_input(const char *promt, char *buffer,int size){
    printf("%s",promt); //  prints nothing (for now)
    fgets(buffer,size,stdin); // read the name from the keyboard and stores into the array of player struct instance
    buffer[strcspn(buffer,"\n")] = 0; //(same as '\0') // returns the index (position) of the first character in buffer that matches \n
}

void print_intro() {
    printf("Welcome to GU-Keep'Em!!\n");
    printf("=========================================\n\n");

    printf("    .------.    .------.    .------.\n");
    printf("   |A_  __ |  |A_  _  |  |A_  _  |\n");
    printf("   |( \\/ )|  |( \\/ )|  |( . ) |\n");
    printf("   | \\  / |  | \\  / |  | \\ /  |\n");
    printf("   |  \\/ A|  |  \\/ A|  |  v  A|\n");
    printf("   `------'  `------'  `------'\n");

    printf("\n=========================================\n");
    printf("🛠️  BETA VERSION - Week 1: Interface Scaffold Only\n");
    printf("=========================================\n\n");

    printf("Press Enter to start...\n");
    getchar(); // Wait for Enter
}

void wait_for_enter(const char *message) {
    printf("%s", message);
    getchar();
}

char get_char_input(const char *prompt) {
    printf("%s", prompt);
    int ch = getchar();
    while (getchar() != '\n'); // flush
    return (char)ch;
}
// char get_char_input(const char *prompt) {
//     char input;
//     printf("%s", prompt);
//     scanf(" %c", &input);           // Read a single char, skip whitespace
//     while (getchar() != '\n');     // Flush remaining input
//     return tolower(input);         // Normalize to lowercase
// }