#ifndef TST_H
#define TST_H

#include "String.h"

typedef struct node TST;

struct TST;
    struct node {
    int val;
    unsigned char c;
    TST *l, *m, *r;
};

TST* rec_insert(TST* t, String* key, int val, int d);
TST* TST_insert(TST* t, String* key , int val);
TST* rec_search(TST* t, String* key, int d);
int TST_search(TST* t, String* key);
TST* initTST();


#endif