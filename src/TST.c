#include "../include/TST.h"

TST* rec_insert(TST* t, String* key, int val, int d) {
    unsigned char c = key->c[d];
    if (t == NULL) { t = initTST(); t->c = c;}
    if (c < t->c) { t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }
    else if (d < key->len - 1) {
    t->m = rec_insert(t->m, key, val, d+1);
    } else { t->val = val; }
    return t;
}

TST* TST_insert(TST* t, String* key , int val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = key->c[d];
    if (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < key->len - 1) {
    return rec_search(t->m, key, d+1);
    } else { return t; }
}

int TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) {
        return -1;
        }
    else { return t->val; }
}


TST* initTST() {
    TST *tst = (TST*)malloc(sizeof(TST));
    if (tst == NULL) {
        exit(EXIT_FAILURE);
    }
    tst->val = -1;
    tst->l = NULL;
    tst->r = NULL;
    tst->m = NULL;

    return tst;
}
