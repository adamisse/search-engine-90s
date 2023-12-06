#include <stdlib.h>
#include <stdio.h>

#include "LLRBArch.h"
#include "Page.h"

typedef struct llrbtpage LLRBTPage;

LLRBTPage * create_node_pages(char*, int, LLRBT*);

int is_red_pages(LLRBTPage*);

LLRBTPage* rotate_left_pages(LLRBTPage*);

LLRBTPage* rotate_right_pages(LLRBTPage*);

void flip_colors_pages(LLRBTPage*);

LLRBTPage* RBT_insert_pages(LLRBTPage*, char*, LLRBT*);

int search_pages(LLRBTPage*, char*);

void free_tree_pages(LLRBTPage*);

LLRBT * get_words(LLRBTPage*);

LLRBTPage * procura_arvore(LLRBTPage*, char*, LLRBTPage*);

void printTree(LLRBTPage*);

void printNode(LLRBTPage*l);

LLRBTPage * get_in(LLRBTPage*l);

LLRBTPage * set_in(LLRBTPage*l, LLRBTPage*n);

LLRBTPage * get_out(LLRBTPage*l);

LLRBTPage * set_out(LLRBTPage*l, LLRBTPage*n);

LLRBTPage * get_node(LLRBTPage*h, char * term);

void set_linkCount(LLRBTPage*, int);

LLRBTPage* RBT_insert_existed_pages(LLRBTPage * h, LLRBTPage * page);

char * get_name(LLRBTPage*);

void printInOut(LLRBTPage * arquivos);