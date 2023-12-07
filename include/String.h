#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char *c;
int len;
} String;


String* create_word(char* string, int len);
char* return_word(String* str);
int return_length(String* str);

#endif