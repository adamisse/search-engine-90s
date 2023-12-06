#ifndef PAGE_H
#define PAGE_H

typedef struct page Page;

struct page {
    char name[20];
    int outCount;
    Page *outLinks;
    long double pageRank;
};

Page *initPage(char *name, int outCount);
void setName(Page *page, char *name);
char *getName(Page *p);
void freePage(Page *page);

#endif
