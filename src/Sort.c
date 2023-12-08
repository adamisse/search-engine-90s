#include "../include/Sort.h"

void sort(Page *p, int lo, int hi) {
  int i, j;
  for (i = lo + 1; i <= hi; i++) {
    Page key = p[i];
    j = i - 1;

    while (j >= lo && (key.pageRank > p[j].pageRank ||
                       (key.pageRank == p[j].pageRank &&
                        strcmp(key.name, p[j].name) > 0))) {
      p[j + 1] = p[j];
      j = j - 1;
    }
    p[j + 1] = key;
  }
}