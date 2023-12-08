#include "../include/ReadContent.h"
#include <ctype.h>

TST *read_stopwords(char *stopwords_path) {
  FILE *sw = fopen(stopwords_path, "r");
  TST *stopwords = initTST();
  char *stopword = malloc(50 * sizeof(char));
  while (fscanf(sw, "%49s", stopword) != EOF) {
    caseInsensitive(stopword);
    int tam = strlen(stopword);
    String *word = create_word(stopword, tam);
    TST_insert(stopwords, word, 0);
    freeString(word);
  }

  free(stopword);
  fclose(sw);

  return stopwords;
}

void read_pages(char *pages_path, Page *pages, int numPages, TST *stopwords) {
  char *name;
  char *word = malloc(50 * sizeof(char));
  for (int i = 0; i < numPages; i++) {
    int j = 0;
    name = concatStrings(pages_path, pages[i].name);
    FILE *sw = fopen(name, "r");
    TST *tst = initTST();
    while (fscanf(sw, "%49s", word) != EOF) {
      caseInsensitive(word);
      int tam = strlen(word);
      String *word_to_be_inserted = create_word(word, tam);
      if (TST_search(stopwords, word_to_be_inserted) == -1) {
        tst = TST_insert(tst, word_to_be_inserted, i);
      }
      j++;
      freeString(word_to_be_inserted);
    }
    pages[i].content = tst;
    fclose(sw);
    // freeTST(tst);
  }
  free(name);
  free(word);
}

// Função para concatenar strings
char *concatStrings(char *str1, char *str2) {
  char *ns = (char *)malloc(strlen(str1) + strlen(str2) + 1);
  strcpy(ns, str1);
  strcat(ns, str2);
  return ns;
}

// Função para tornar as strings minúsculas
char *caseInsensitive(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (isalpha(str[i])) {
      str[i] = tolower(str[i]);
    }
  }
  return str;
}
