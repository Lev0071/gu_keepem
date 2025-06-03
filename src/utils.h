#ifndef UTILS_H
#define UTILS_H

int get_integer_input(const char *prompt);
void get_string_input(const char *promt, char *buffer,int size);
void print_intro();
void wait_for_enter(const char *message);
char get_char_input(const char *prompt);
void clearBuffer();

#endif