// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/PageRank.h"
#include "../include/ReadContent.h"
#include "../include/Sort.h"

void searchAndPrintResults(Page *pages, int numPages);

int main(int argc, char **argv) {
  if (argc == 1) {
    argv[1] = "input";
  }

  char *graph_path = concatStrings(argv[1], "/graph.txt");
  char *stopwords_path = concatStrings(argv[1], "/stopwords.txt");
  char *pages_path = concatStrings(argv[1], "/pages/");

  int numPages = countFileLines(graph_path);
  TST *stopwords = read_stopwords(stopwords_path);
  Page *pages = malloc(sizeof(Page) * numPages);

  readGraphAndCalculatePageRank(graph_path, pages, numPages);
  read_pages(pages_path, pages, numPages, stopwords);

  searchAndPrintResults(pages, numPages);

  freeAllPages(pages, numPages);
  free(stopwords_path);
  free(pages_path);
  free(graph_path);
  freeTST(stopwords);

  return 0;
}

// Função para realizar a busca e imprimir os resultados
void searchAndPrintResults(Page *pages, int numPages) {
  size_t size = 0;
  char *word = NULL;
  int numPagesAux = numPages;

  while (getline(&word, &size, stdin) != EOF) {
    int filteredPagesSize;
    printf("search:%s", word);

    char delim[] = "\n ";
    char *token = strtok(word, delim);

    Page *filteredPages = pages;

    while (token != NULL) {
      filteredPagesSize = 0;
      Page *auxFilteredPages = malloc(sizeof(Page) * numPages);

      int tokenSize = strlen(token);
      caseInsensitive(token);

      String *word_to_be_searched = create_word(token, tokenSize);

      for (int i = 0; i < numPagesAux; i++) {
        int tstValue =
            TST_search(filteredPages[i].content, word_to_be_searched);

        if (tstValue != -1) {
          auxFilteredPages[filteredPagesSize] = filteredPages[i];
          filteredPagesSize++;
        }
      }

      filteredPages = auxFilteredPages;

      token = strtok(NULL, delim);
      freeString(word_to_be_searched);
    }

    sort(filteredPages, 0, filteredPagesSize - 1);

    printf("pages:");
    for (int i = 0; i < filteredPagesSize; i++) {
      printf("%s", filteredPages[i].name);
      if (i + 1 != filteredPagesSize) {
        printf(" ");
      }
    }
    printf("\npr:");
    for (int i = 0; i < filteredPagesSize; i++) {
      printf("%.16Lf", filteredPages[i].pageRank);
      if (i + 1 != filteredPagesSize) {
        printf(" ");
      }
    }
    printf("\n");
  }

  free(word);
}