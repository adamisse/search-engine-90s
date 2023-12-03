#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LLRBArch.h"
#include "../include/LLRBPage.h"

#define RED 1
#define BLACK 0

struct page{
  char * name;
  int inCount;
  int outCount; // Out
  double pageRank;
  Page * in;
  Page * out;
};

struct llrbtpage {
    Page page;
    LLRBT * words;
    LLRBTPage * in, * out;
    int color;
    LLRBTPage *l, *r;
};

Page * inicPage(){
  Page * page = malloc(sizeof(Page));
  return page;
}

void setName(Page*p, char*name){
  p->name = name;
}

char * getName(Page * p){
  return p->name;
}

LLRBTPage * create_node_pages(char * name, int color, LLRBT * words){
    LLRBTPage * new_node = (LLRBTPage*) malloc (sizeof(LLRBTPage));
    new_node->page.name = malloc(50*sizeof(char));
    strcpy(new_node->page.name, name);
    new_node->words = words;
    new_node->color = color;
    new_node->l = NULL;
    new_node->page.inCount = 0;
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
        h->page.name = term; 
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
        h->page.name = page->page.name; 
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

LLRBTPage * readGraph(char * line, char * delim,  LLRBTPage *arquivos, FILE * graph, int n){
  Page * pages = malloc(sizeof(pages) * n);
  
  size_t len;
  int i = 0;
  while (getline(&line, &len, graph) != EOF)
  {
    char* token = strtok(line, delim);
    pages[i].name = malloc(sizeof(token) + 1);
    strcpy(pages[i].name, token);
    int linkCount = atoi(strtok(NULL, delim));
    pages[i].outCount = linkCount;
    pages[i].out = malloc(sizeof(Page)*linkCount);
    LLRBTPage * target = get_node(arquivos, token);

    
    target->page.outCount = linkCount;
    pages[i].out = malloc(sizeof(pages) * linkCount);
    for(int j = 0; j < linkCount; j++){
      token = strtok(NULL, delim);
      
      LLRBTPage * out = get_node(arquivos, token);
      
      target->out = RBT_insert_pages(target->out, out->page.name, out->words);
      
      out->in = RBT_insert_pages(out->in, target->page.name, target->words);
      out->page.inCount++;
      
    }

    //printNode(target);
    
    //printTree(targetOut);

    //set_out(target, targetOut);
    
    
    //printNode(target);
    //printf(": ");
    //printTree(target->in);
    //printf("\n");
    i++;
  }
  
  for(int i = 0; i < n; i++){
      int index;
      LLRBTPage* target = get_node(arquivos, pages[i].name);
      pages[i].outCount = target->page.outCount;
      pages[i].inCount = target->page.inCount;
      pages[i].in = malloc(sizeof(Page)*pages[i].inCount);
      for(int j = 0; j < pages[i].inCount; j++){
        pages[i].in[j].name = NULL;
      }
      pages[i] = iterateIn(pages[i], target->in, pages[i].inCount);
    }

    pages = initPageRank(pages, n);
  //printInOut(arquivos);
  return arquivos;
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

//• PR(i) denota o PageRank da i-esima pagina (ou seja, da pagina/documentos di);
//• n é o numero total de paginas/documentos;
//• α e um parametro, entre 0 e 1. Normalmente, α vale 0.85, sendo este o valor a ser usado neste trabalho;
//• In(k) e o conjunto de todas as paginas que tem um link para a pagina k;
//• Out(k) e o conjunto de todas as paginas com um link saindo da pagina k;
//• |Y| denota o numero de elementos de um conjunto qualquer Y.

/*Page* calculatePageRank(Page * pages, int n, int iteration){
  double stopDelim = 0.000001;
  double change = 1; //apenas para rodar os primeiros whiles, após isto, seu valor será alterado;
  double alpha = 0.8500;

  if(iteration == 0){
    for(int i = 0; i < n; i++){
      pages[i].pageRank = 1/n;
    }
    return pages;
  }
  else{
    
  }
}*/

Page* initPageRank(Page * pages, int n){
  for(int i = 0; i < n; i++){
    pages[i].pageRank = 1/n;
  }
  return pages;
}

LLRBTPage * define_pageRank(LLRBTPage* arquivos,int n){
  if(arquivos!=NULL){
    arquivos->page.pageRank = 1/n;
    define_pageRank(arquivos->l, n);
    define_pageRank(arquivos->r, n);
  }
}

Page iterateIn(Page page, LLRBTPage * in, int index){
  if(in!=NULL){
    for(int i = 0; i < index; i++){
      if(page.in[i].name == NULL){
        page.in[i] = in->page;
        break;
      }
    }
    page = iterateIn(page, in->l, index);
    page = iterateIn(page, in->r, index);
  }
  return page;
}

/*LLRBTPage * calculatePageRank(LLRBTPage * arquivos, int n){
  double stopDelim = 0.000001;
  double change = 1; //apenas para rodar os primeiros whiles, após isto, seu valor será alterado;
  int i = 0;
  double alpha = 0.8500;
  LLRBTPage * pagesArray[n];
  
  while(change > stopDelim)
  {
    double sum = 0.00;
    if(i == 0)
    {
      arquivos = define_pageRank(arquivos, n);
    }
    else
    {
      if(page[i].linkCount != 0)
      {
        for(int j = 0; j < page[i].linkCount; j++){
          sum += (page[i - 1].linkedPages[j].pageRank)/page[i].linkedPages[j].linkCount;
        }
        page[i].pageRank = ((1-alpha)/n) + (alpha * sum);
      }
      else
      {
        for(int j = 0; j < page[i].linkCount; j++){
          sum += (page[i - 1].linkedPages[j].pageRank)/page[i].linkedPages[j].linkCount;
        }
        page[i - 1].pageRank = ((1-alpha)/n) + (alpha * page[i].pageRank) + (alpha * sum);
      }
    }
    sum = 0.00;
    double module = 0.00;
    if(i >= 1)
    {
      for(int j = 0; i < n -1; i++)
      {
        module = page[i].linkedPages[j].pageRank - page[i - 1].linkedPages[j].pageRank;
        if(module < 0) module = module * (-1);
        sum += module;
      }
      change = (1/n) * sum;
      i++;
    }
  } 
}*/