#include <stdlib.h>
#include <stdio.h>
#include "LLRBArch.h"

typedef struct llrbtpage LLRBTPage;

typedef struct page Page;

Page * inicPage();

void setName(Page*, char*);

char * getName(Page* p);

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

LLRBTPage * readGraph(char * line, char * delim,  LLRBTPage *arquivos, FILE * graph, int n);

void printInOut(LLRBTPage * arquivos);

LLRBTPage * define_pageRank(LLRBTPage* arquivos,int n);

LLRBTPage * calculatePageRank(LLRBTPage * arquivos, int n);

Page iterateIn(Page page, LLRBTPage * in, int index);

Page* initPageRank(Page * pages, int n);