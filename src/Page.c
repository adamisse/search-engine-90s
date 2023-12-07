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

    // Inicializa os elementos de outLinks
    for (int i = 0; i < outCount; ++i) {
        setName(&page->outLinks[i], "");  // Você pode ajustar o nome inicial conforme necessário
    }

    page->pageRank = 0.0L;

    return page;
}

void setName(Page *page, char *name) {
    strncpy(page->name, name, sizeof(page->name) - 1);
    page->name[sizeof(page->name) - 1] = '\0'; 
}

char *getName(Page *p) {
    return p->name;
}

void freePage(Page *page) {
    for (int i = 0; i < page->outCount; ++i) {
        free(page->outLinks[i].name);
    }
    free(page->outLinks);
    free(page->name);
    free(page);
}
