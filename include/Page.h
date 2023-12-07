#ifndef PAGE_H
#define PAGE_H

#include "TST.h"

typedef struct page Page;

struct page {
    char name[20];
    int outCount;
    TST *content;
    Page *outLinks;
    long double pageRank;
};

Page *initPage(char *name, int outCount);
void setName(Page *page, char *name);
char *getName(Page *p);
void freePage(Page *page);
void setContent(Page* p, TST* tst);

#endif
