#include "../include/Page.h"
#include <stdlib.h>
#include <string.h>

Page *initPage(char *name, int outCount) {
  Page *page = malloc(sizeof(Page));
  if (page == NULL) {
    exit(EXIT_FAILURE);
  }

  setName(page, name);
  page->outCount = outCount;

  // Aloca espaço para o array de outLinks
  page->outLinks = malloc(outCount * sizeof(Page));
  if (page->outLinks == NULL) {
    free(page->name);
    free(page);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < outCount; ++i) {
    setName(&page->outLinks[i], "");
  }

  page->pageRank = 0.0L;

  return page;
}

void setName(Page *page, char *name) {
  strncpy(page->name, name, sizeof(page->name) - 1);
  page->name[sizeof(page->name) - 1] = '\0';
}

char *getName(Page *p) { return p->name; }

TST *getContent(Page *p) { return p->content; }

void setContent(Page *p, TST *tst) { p->content = tst; }

void freePage(Page *page) {
  //for (int i = 0; i < page->outCount; ++i) {
  //  free(getName(&page->outLinks[i]));
  //}

  //free(page->outLinks);
  //free(page->name);
  //freeTST(page->content);
  //free(page);
}

void freeAllPages(Page *pages, int numPages) {
  for (int i = 0; i < numPages; ++i) {
    freePage(&pages[i]);
  }
  free(pages);
}