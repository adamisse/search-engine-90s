#include "ReadContent.h"

TST* read_stopwords(char* stopwords_path){
    FILE *sw = fopen(stopwords_path, "r");
    TST* stopwords = initTST();
    char *stopword = malloc(50 * sizeof(char));
    int i = 0;
    while (fscanf(sw, "%s", stopword) != EOF){
        //caseInsensitive(stopword);
        int tam = strlen(stopword);
        //printf("%s\n", stopword);
        String* stopword = create_word(stopword, tam);
        //printf("%s", return_word(stopword));
        //stopwords = TST_insert(stopwords, stopword, i);
        i++;
    }
    return stopwords;
}

void read_pages(char* pages_path, Page* pages, int numPages, TST* stopwords){
    for(int i=0 ; i < numPages; i++){
        char* name = concatStrings(pages_path, pages[i].name);
        FILE *sw = fopen(concatStrings(pages_path, pages[i].name), "r");
        TST* tst = initTST();
        char *word = malloc(50 * sizeof(char));
        int i = 0;
        while(fscanf(sw, "%s", word) != EOF){
            if(!TST_search(stopwords, word)){
                caseInsensitive(word);
                tst = TST_insert(tst, word, i);
                i++;
            }
        }
        pages[i].content = tst;
    }
}


// Função para concatenar strings
char *concatStrings(char *str1, char *str2) {
    char *ns = (char *)malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(ns, str1);
    strcat(ns, str2);
    return ns;
}

// Função para tornar as strings minúsculas
char *caseInsensitive(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (isalpha(str[i])) {
            str[i] = tolower(str[i]);
        }
    }
    return str;
}