#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Page.h"

#include "../include/LLRBArch.h"
#include "../include/LLRBPage.h"

#define RED 1
#define BLACK 0

struct llrbtpage {
    Page page;
    LLRBT * words;
    LLRBTPage * in, * out;
    int color;
    LLRBTPage *l, *r;
};

LLRBTPage *create_node_pages(char *name, int color, LLRBT *words) {
    LLRBTPage *new_node = (LLRBTPage *)malloc(sizeof(LLRBTPage));
    if (new_node == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    initPage(name, 0);

    new_node->words = words;
    new_node->color = color;
    new_node->l = NULL;
    new_node->r = NULL;
    new_node->in = NULL;
    new_node->out = NULL;

    return new_node;
}

int is_red_pages(LLRBTPage *x) {
    if (x == NULL) return BLACK;
    return x->color; //RED == true
}

LLRBTPage* rotate_left_pages(LLRBTPage *h) {
    LLRBTPage *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

LLRBTPage* rotate_right_pages(LLRBTPage *h) {
    LLRBTPage *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors_pages(LLRBTPage *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

LLRBTPage* RBT_insert_pages(LLRBTPage * h, char * term, LLRBT * words) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        return create_node_pages(term, RED, words);
    }
    int cmp = strcmp(term, h->page.name);
    if (cmp < 0) {
        h->l = RBT_insert_pages(h->l, term, words); 
    }
    else if (cmp > 0) { 
        h->r = RBT_insert_pages(h->r, term, words);
    }
    else /*cmp == 0*/ { 
        setName(&h->page, term);
    }
    // Lean left.
    if (is_red_pages(h->r) && !is_red_pages(h->l)) {
         h = rotate_left_pages(h); 
    }
    // Balance 4-node.
    if (is_red_pages(h->l) && is_red_pages(h->l->l)) {
         h = rotate_right_pages(h);
    }
    // Split 4-node.
    if (is_red_pages(h->l) && is_red_pages(h->r)) {
        flip_colors_pages(h); 
    }
    return h;
}

int search_pages(LLRBTPage * h, char * term){
    while (h != NULL) {
      int cmp;
      cmp = strcmp(term, h->page.name);
      if (cmp < 0) h = h->l;
      else if (cmp > 0) h = h->r;
      else return 1;
    }
  return 0;
}

void free_tree_pages(LLRBTPage*rbt){
  if(rbt!=NULL){
    free_tree_pages(rbt->l);
    free_tree_pages(rbt->r);
    free(rbt->page.name);
    free(rbt);
  }
}

LLRBT * get_words(LLRBTPage*l){
  return l->words;
}

LLRBTPage * procura_arvore(LLRBTPage*l, char*s, LLRBTPage * resp){
  
  if(l!=NULL){
    if(search(l->words, s)){
      resp = RBT_insert_pages(resp, l->page.name, l->words);
    }
    procura_arvore(l->l, s, resp);
    procura_arvore(l->r, s, resp);
  }
  return resp;
}

void printTree(LLRBTPage*l){
  if(l!=NULL){
    printf("%s ", l->page.name);
    //printf("left: ");
    printTree(l->l);
    //printf("right: ");
    printTree(l->r);
  }
}

void printNode(LLRBTPage*l){
  if(l!=NULL){
    printf("%s ", l->page.name);
  }
}

LLRBTPage * get_in(LLRBTPage*l){
  return l->in;
}

LLRBTPage * set_in(LLRBTPage*l, LLRBTPage*n){
  l->in = n;
}

LLRBTPage * get_out(LLRBTPage*l){
  return l->out;
}

LLRBTPage * set_out(LLRBTPage*l, LLRBTPage*n){
  l->in = n;
}

LLRBTPage * get_node(LLRBTPage*h, char * term){
  while (h != NULL) {
      int cmp;
      cmp = strcmp(term, h->page.name);
      if (cmp < 0) h = h->l;
      else if (cmp > 0) h = h->r;
      else return h;
    }
  return NULL;
}

void set_linkCount(LLRBTPage*l, int linkCount){
  l->page.outCount = linkCount;
}

LLRBTPage* RBT_insert_existed_pages(LLRBTPage * h, LLRBTPage * page) {
    // Insert at bottom and color it red.
    if (h == NULL) {
        h = page;
    }
    int cmp = strcmp(page->page.name, h->page.name);
    if (cmp < 0) {
        h->l = RBT_insert_existed_pages(h->l, page); 
    }
    else if (cmp > 0) { 
        h->r = RBT_insert_existed_pages(h->r, page);
    }
    else /*cmp == 0*/ { 
        setName(&h->page, page->page.name);
    }
    // Lean left.
    if (is_red_pages(h->r) && !is_red_pages(h->l)) {
         h = rotate_left_pages(h); 
    }
    // Balance 4-node.
    if (is_red_pages(h->l) && is_red_pages(h->l->l)) {
         h = rotate_right_pages(h);
    }
    // Split 4-node.
    if (is_red_pages(h->l) && is_red_pages(h->r)) {
        flip_colors_pages(h); 
    }
    return h;
}

char * get_name(LLRBTPage * l){
  return l->page.name;
}

void printInOut(LLRBTPage * arquivos){
  if(arquivos != NULL){
    printNode(arquivos);
    printf(":\n");
    printf("In: ");
    printTree(arquivos->in);
    printf("\nOut: ");
    printTree(arquivos->out);
    printf("\n");
    printInOut(arquivos->l);
    printInOut(arquivos->r);
  }
}

Page* initPageRank(Page * pages, int n){
  for(int i = 0; i < n; i++){
    pages[i].pageRank = 1/n;
  }
  return pages;
}