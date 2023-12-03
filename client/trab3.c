#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/LLRBArch.h"
#include "../include/LinkedList.h"
#include "../include/LLRBPage.h"

//pesquisa case insensitive
//usar stopwords

void readFiles();

char *concatStrings(char *str1, char *str2);

void printOutput(LLRBTPage*a, char*s);

char * caseInsensitive(char* str);

int main()
{
  // TODO:
  // Função de pageRank
  // Algoritmo de ordenação usando o pageRank
  // Processar saída
  // Finalizar (Verificar vazamentos de memória e otimização)
  // Makefile

  readFiles();

  return 0;
}

void readFiles()
{
  LLRBTPage * arquivos = NULL;
  char delim[]=" \n\t";
  // Lê as stopwords---------------------------------------------------
  FILE *sw = fopen("stopwords.txt", "r");
  if (sw == NULL)
  {
    printf("Falha ao encontrar stopwords.txt");
    exit(0);
  }
  // Estrutura que contém as stopwords lidas
  LLRBT *stopwords = NULL;
  // Aloca espaço para colcoar a última stopword lida
  char *stopword = malloc(50 * sizeof(char));
  // Lê o arquivo até encontrar EOF
  while (fscanf(sw, "%s", stopword) != EOF)
  {
    caseInsensitive(stopword);
    stopwords = RBT_insert(stopwords, stopword);
  }
  free(stopword);
  fclose(sw);
  //---------------------------------------------------------------------

  // Leitura das páginas ------------------------------------------------
  FILE *index = fopen("index.txt", "r");
  if (index == NULL)
  {
    printf("Falha ao encontrar index.txt");
    exit(0);
  }
  char *fileName = NULL;
  size_t len;
  // Lê os arquivos contidos no index.txt
  int i = 0;
  int pageCount = 0;

  while (getline(&fileName, &len, index) != EOF)
  { 
    // remove quebra de linha no nome do arquivo
    char *token = strtok(fileName, "\n");
    char *dir = concatStrings("pages/", token);
    FILE *page = fopen(dir, "r");
    free(dir);
    if (page == NULL)
    {
      printf("arquivo %s não encontrado\n", dir);
    }
    
    char *word = malloc(50 * sizeof(char));
    // Lê o conteudo dos arquivos contidos no diretório pages
    LLRBT * actualPage = NULL;
    while (fscanf(page, "%s", word) != EOF)
    {
      caseInsensitive(word);
      if (!search(stopwords, word))
      {
        actualPage = RBT_insert(actualPage, word);
      }
    }
    arquivos = RBT_insert_pages(arquivos, token, actualPage);
    pageCount++;
    i++;
    fclose(page);
    free(word);
  }
  free(fileName);
  fclose(index);
  // ---------------------------------------------------------------------------
  
  // Leitura do grafo ----------------------------------------------------------
  FILE *graph = fopen("graph.txt", "r");
  if (graph == NULL)
  {
    printf("Falha ao encontrar graph.txt");
    exit(0);
  }

  char *line = NULL;
  i = 0;

  //lê graph.txt e armazena os Ins e Outs
  arquivos = readGraph(line, " \t\n", arquivos, graph, pageCount);

  fclose(graph);

  // Parte da pesquisa ---------------------------------------------------------
  char *searchTerm = malloc(200 * sizeof(char));
  if(scanf("%[^\n]", searchTerm)){}
  caseInsensitive(searchTerm);
  char * originalTerm = malloc(200 * sizeof(char));
  strcpy(originalTerm, searchTerm);
  /* get the first token */
  char * token = strtok(searchTerm, delim);
  LLRBTPage * resposta = NULL;
  resposta = procura_arvore(arquivos, token, resposta);
  while(1){
    token = strtok(NULL, delim);
    if(token==NULL){
      break;
    }
    LLRBTPage * newA = NULL;
    resposta = procura_arvore(resposta, token, newA);
  }

  printOutput(resposta, originalTerm);
  
  free(originalTerm);
  free(searchTerm);
  free_tree(stopwords);
}

void printOutput(LLRBTPage*a, char*s){
  printf("search:%s\n", s);
  printf("pages:");
  printTree(a);
  printf("\n");
}

char *concatStrings(char *str1, char *str2)
{
  char *ns = (char *)malloc(sizeof(str1) + sizeof(str2));
  strcpy(ns, str1);
  strcat(ns, str2);
  return ns;
}



char* caseInsensitive(char * str){
  for(int i = 0; i < strlen(str); i++){
    if(isalpha(str[i])) str[i] = tolower(str[i]);
  }
  return str;
}