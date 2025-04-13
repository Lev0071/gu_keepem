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