#include "../include/Sort.h"

int comparePages(const void *a, const void *b) {
  Page *pageA = (Page *)a;
  Page *pageB = (Page *)b;

  if (pageA->pageRank > pageB->pageRank) {
    return -1;
  } else if (pageA->pageRank < pageB->pageRank) {
    return 1;
  } else {
    return strcmp(pageA->name, pageB->name);
  }
}

void quickSort(Page *p, int lo, int hi) {
  qsort(p + lo, hi - lo + 1, sizeof(Page), comparePages);
}

Page *sort(Page *p, int lo, int hi) {
  quickSort(p, lo, hi);
  return p;
}
