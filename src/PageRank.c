#include "../include/PageRank.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readGraphAndCalculatePageRank(char *filename, Page *pages, int numPages) {
  readGraphFile(filename, pages, numPages);
  initializePageRanks(pages, numPages);
  calculatePageRank(pages, numPages);
}

void readGraphFile(char *filename, Page *pages, int numPages) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < numPages; ++i) {
    fscanf(file, "%s %d", pages[i].name, &pages[i].outCount);
    pages[i].outLinks = malloc(pages[i].outCount * sizeof(Page));
    for (int j = 0; j < pages[i].outCount; ++j) {
      fscanf(file, "%s", pages[i].outLinks[j].name);
    }
  }

  fclose(file);
}

int countFileLines(char *filename) {
  int numLines = 0;
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int c;
  int lastChar = EOF;

  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      numLines++;
    }
    lastChar = c;
  }

  if (lastChar != '\n') {
    numLines++;
  }

  fclose(file);

  return numLines;
}

void initializePageRanks(Page pages[], int numPages) {
  for (int i = 0; i < numPages; ++i) {
    pages[i].pageRank = 1.0L / (long double)numPages;
  }
}

void calculatePageRank(Page pages[], int numPages) {
  const long double ALPHA = 0.85L;
  const long double EPSILON = 1e-6;

  long double *newPageRanks = malloc(numPages * sizeof(long double));
  if (newPageRanks == NULL) {
    perror("Error allocating memory");
    exit(EXIT_FAILURE);
  }

  while (1) {
    for (int i = 0; i < numPages; ++i) {
      long double sum = 0.0L;

      for (int j = 0; j < numPages; ++j) {
        for (int k = 0; k < pages[j].outCount; ++k) {
          if (strcmp(pages[j].outLinks[k].name, pages[i].name) == 0) {
            sum += pages[j].pageRank / pages[j].outCount;
            break;
          }
        }
      }

      if (pages[i].outCount != 0) {
        newPageRanks[i] =
            ((1.0L - ALPHA) / (long double)numPages) + ALPHA * sum;
      } else {
        newPageRanks[i] = ((1.0L - ALPHA) / (long double)numPages) +
                          (ALPHA * pages[i].pageRank) + ALPHA * sum;
      }
    }

    if (checkConvergence(pages, newPageRanks, numPages, EPSILON)) {
      break;
    }

    for (int i = 0; i < numPages; ++i) {
      pages[i].pageRank = newPageRanks[i];
    }
  }

  free(newPageRanks);
}

int checkConvergence(Page pages[], long double newPageRanks[], int numPages,
                     double epsilon) {
  for (int i = 0; i < numPages; ++i) {
    if (fabsl(newPageRanks[i] - pages[i].pageRank) > epsilon) {
      return 0;
    }
  }
  return 1;
}

void printPageRanks(Page pages[], int numPages) {
  for (int i = 0; i < numPages; ++i) {
    printf("page: %s\npr:: %.8Lf\n\n", pages[i].name, pages[i].pageRank);
  }
}

void freeMemory(Page pages[], int numPages) {
  for (int i = 0; i < numPages; ++i) {
    free(pages[i].name);
    free(pages[i].outLinks);
  }

  free(pages);
}
