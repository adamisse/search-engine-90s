#include "../include/String.h"

String* create_word(char* string, int len){
    printf("%s\n", string);
    String* str = malloc(sizeof(String));
    str->c = malloc(sizeof(char)*len+1);
    strcpy(str->c, string);
    str->len = len;
    return str;
}

char* return_word(String* str){
    return str->c;
}

int return_length(String* str){
    return str->len;
}