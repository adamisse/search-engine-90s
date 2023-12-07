#include "../include/Sort.h"

int partition(Page *p, int lo, int hi) {
  int i = lo, j = hi+1;
  Page page = p[lo];
  Page aux;
  while(1){
    while (p[++i].pageRank > page.pageRank)
      if (i == hi) break;
    while (page.pageRank > p[--j].pageRank)
      if (j == lo) break;
    if (i >= j) break;
    aux = p[i];
    p[i] = p[j];
    p[j] = aux;
  }
  aux = p[lo];
  p[lo] = p[j];
  p[j] = aux;
  return j;
}

void shuffle(Page *p, int N){
  struct timeval tv;
  Page aux;
  gettimeofday(&tv, NULL);
  srand48(tv.tv_usec);
  for (int i = N-1; i > 0; i--){
    int j = (unsigned int) (drand48()*(i+1));
    aux = p[i];
    p[i] = p[j];
    p[j] = aux;
  }
}

void quickSort(Page *p, int lo, int hi){
  if (hi <= lo){
    return;
  }
  int j = partition(p, lo, hi);
  quickSort(p, lo, j-1);
  quickSort(p, j+1, hi);
}

Page* sort(Page *p, int lo, int hi){
  shuffle(p, hi-lo+1);
  quickSort(p, lo, hi);
  return p;
}