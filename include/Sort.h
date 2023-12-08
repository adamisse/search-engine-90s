#ifndef SORT_H
#define SORT_H

#include "Page.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int comparePages(const void *a, const void *b);

void quickSort(Page *p, int lo, int hi);

Page *sort(Page *p, int lo, int hi);

#endif