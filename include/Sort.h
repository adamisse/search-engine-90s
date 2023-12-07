#ifndef SORT_H
#define SORT_H

#include "Page.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int partition(Page *p, int lo, int hi);

void shuffle(Page *p, int N);

void quickSort(Page *p, int lo, int hi);

Page* sort(Page *p, int lo, int hi);


#endif