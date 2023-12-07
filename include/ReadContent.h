#ifndef READCONTENT_H
#define READCONTENT_H

#include "Page.h"
#include <stdio.h>
#include <stdlib.h>

TST* read_stopwords(char* stopwords_path);
Page* read_pages(char* pages_path, Page *pages, int numPages, TST* stopwords);
char *concatStrings(char *str1, char *str2);
char *caseInsensitive(char *str);

#endif