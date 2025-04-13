#include "utils.h"
#include <stdio.h>
#include <string.h>

int get_integer_input(const char *prompt){
    int value;
    printf("%s",prompt);
    scanf("%d",&value);
    int c;
    while((c=getchar()) != '\n' && c!= EOF);
    printf("Inside: get_integer_input|| player ccount returned: %d",value);
    return value;
}