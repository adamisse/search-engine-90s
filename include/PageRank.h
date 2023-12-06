#ifndef PAGERANK_H
#define PAGERANK_H

#include "Page.h"

void readGraphAndCalculatePageRank();
void readGraphFile(char *filename, Page pages[], int numLines);
int countFileLines(char *filename);
void initializePageRanks(Page pages[], int numPages);
void calculatePageRank(Page pages[], int numPages);
int checkConvergence(Page pages[], long double newPageRanks[], int numPages, double epsilon);
void printPageRanks(Page pages[], int numPages);
void freeMemory(Page pages[], int numPages);

#endif