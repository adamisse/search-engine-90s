/*#include "../include/LinkedList.h"
#include "../include/LLRBArch.h"
#include "../include/Page.h"
#include "../include/LLRBArch.h"
#include <string.h>

typedef struct cel Celula;

struct cel {
  LLRBT * words;
  char * name;
  Celula* prox;
};

struct lista{
  Celula * prim;
  Celula * ult;
};

typedef struct lista Lista;

Lista* InicLista(){
  Lista * lista = (Lista*) malloc (sizeof(Lista));
  lista->prim = NULL;
  lista->ult=NULL;
  return lista;
}

void InsereLista(Lista* lista, LLRBT * words, char * name){
  Celula * nova = (Celula*) malloc (sizeof(Celula));
  nova->words = words;
  nova->prox = lista->prim;
  nova->name = malloc(sizeof(name));
  strcpy(nova->name, name);
  lista->prim = nova;
  if (lista->ult==NULL){
    lista->ult = nova;
  }
}

Lista * procura(Lista * l, char * s){
  Lista * resposta = InicLista();
  Celula * p;
  for(p = l->prim; p!=NULL; p = p->prox){
    if(search(p->words, s)){
      InsereLista(resposta, p->words, p->name);
    }
  }
  return resposta;
}

int size(Lista*l){
  int count = 0;
  Celula * p;
  for(p = l->prim; p!=NULL; p = p->prox){
    count++;
  }
  return count;
}

void printList(Lista * l){
  Celula * p;
  for(p = l->prim; p!=NULL; p = p->prox){
    printf("%s ", p->name);
  }
}

void free_list(Lista* lista){
  Celula * p = lista->prim;
  Celula * t;

  while (p!=NULL){
    t = p->prox;
    if(p->words!=NULL){
      free_tree(p->words);
    }
    if(p->name!=NULL){
      free(p->name);
    }
    free(p);
    p = t;
  }

  free(lista);
}

void free_answer(Lista * lista){
  Celula * p = lista->prim;
  Celula * t;

  while (p!=NULL){
    t = p->prox;
    if(p->name!=NULL){
      free(p->name);
    }
    free(p);
    p = t;
  }

  free(lista);
}

void setPagesNames(Lista * l, Page ** page, int pageCount){
  Celula * p;
  int i = pageCount - 1;
  for(p = l->prim; p!=NULL; p = p->prox){
    setName(page[i], p->name);
    i--;
  }
}*/