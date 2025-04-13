#include "utils.h"
#include <stdio.h>
#include <string.h>

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