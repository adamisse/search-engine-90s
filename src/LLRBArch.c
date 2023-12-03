#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LLRBArch.h"

#define RED 1
#define BLACK 0

struct llrbt {
    char * term;
    int color;
    LLRBT *l, *r;
};

LLRBT * create_node(char * term, int color){
    LLRBT * new_node = (LLRBT*) malloc (sizeof(LLRBT));
    new_node->term = malloc(50*sizeof(char));
    strcpy(new_node->term, term);
    new_node->color = color;
    new_node->l = NULL;
    new_node->r = NULL;
    return new_node;
}

int is_red(LLRBT *x) {
    if (x == NULL) return BLACK;
    return x->color; //RED == true
}

LLRBT* rotate_left(LLRBT *h) {
    LLRBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

LLRBT* rotate_right(LLRBT *h) {
    LLRBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(LLRBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

LLRBT* RBT_insert(LLRBT * h, char * term) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_node(term, RED);
    }
    int cmp = strcmp(term, h->term);
    if (cmp < 0) {
        h->l = RBT_insert(h->l, term); 
    }
    else if (cmp > 0) { 
        h->r = RBT_insert(h->r, term);
    }
    else /*cmp == 0*/ { 
        h->term = term; 
    }
    // Lean left.
    if (is_red(h->r) && !is_red(h->l)) {
         h = rotate_left(h); 
    }
    // Balance 4-node.
    if (is_red(h->l) && is_red(h->l->l)) {
         h = rotate_right(h);
    }
    // Split 4-node.
    if (is_red(h->l) && is_red(h->r)) {
        flip_colors(h); 
    }
    return h;
}

int search(LLRBT * h, char * term){
    while (h != NULL) {
      int cmp;
      cmp = strcmp(term, h->term);
      if (cmp < 0) h = h->l;
      else if (cmp > 0) h = h->r;
      else return 1;
    }
  return 0;
}

void free_tree(LLRBT*rbt){
  if(rbt!=NULL){
    free_tree(rbt->l);
    free_tree(rbt->r);
    free(rbt->term);
    free(rbt);
  }
}