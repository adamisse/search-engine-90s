#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/LLRBArch.h"
#include "../include/LinkedList.h"
#include "../include/LLRBPage.h"
#include "../include/PageRank.h"

// Declarações de funções
void readFiles();
void readStopwords(LLRBT **stopwords);
int readPages(LLRBTPage **arquivos, LLRBT *stopwords);
void performSearch(LLRBTPage *arquivos);
void printOutput(LLRBTPage *a, char *s);
char *concatStrings(char *str1, char *str2);
char *caseInsensitive(char *str);

// Função principal
int main() {
    // TODO: Função de pageRank, Algoritmo de ordenação usando o pageRank,
    // Processar saída, Finalizar (Verificar vazamentos de memória e otimização), Makefile
    
    readGraphAndCalculatePageRank();

    return 0;
}

// Função principal para leitura de arquivos
void readFiles() {
    LLRBTPage *arquivos = NULL;
    LLRBT *stopwords = NULL;

    // Lê stopwords
    readStopwords(&stopwords);

    // Lê páginas
    int pageCount = readPages(&arquivos, stopwords);

    // Realiza pesquisa
    performSearch(arquivos);

    // Libera memória
    free_tree(stopwords);
}

// Função para leitura e inserção de stopwords na árvore
void readStopwords(LLRBT **stopwords) {
    FILE *sw = fopen("stopwords.txt", "r");
    if (sw == NULL) {
        printf("Falha ao encontrar stopwords.txt");
        exit(EXIT_FAILURE);
    }

    char *stopword = malloc(50 * sizeof(char));
    while (fscanf(sw, "%s", stopword) != EOF) {
        caseInsensitive(stopword);
        *stopwords = RBT_insert(*stopwords, stopword);
    }

    free(stopword);
    fclose(sw);
}

// Função para leitura e processamento das páginas
int readPages(LLRBTPage **arquivos, LLRBT *stopwords) {
    FILE *index = fopen("index.txt", "r");
    if (index == NULL) {
        printf("Falha ao encontrar index.txt");
        exit(EXIT_FAILURE);
    }

    char *fileName = NULL;
    size_t len;

    int pageCount = 0;

    while (getline(&fileName, &len, index) != EOF) {
        char *token = strtok(fileName, "\n");
        char *dir = concatStrings("pages/", token);
        FILE *page = fopen(dir, "r");
        free(dir);

        if (page == NULL) {
            printf("arquivo %s não encontrado\n", dir);
        }

        LLRBT *actualPage = NULL;
        char *word = malloc(50 * sizeof(char));

        while (fscanf(page, "%s", word) != EOF) {
            caseInsensitive(word);
            if (!search(stopwords, word)) {
                actualPage = RBT_insert(actualPage, word);
            }
        }

        *arquivos = RBT_insert_pages(*arquivos, token, actualPage);
        pageCount++;

        fclose(page);
        free(word);
    }

    free(fileName);
    fclose(index);

    return pageCount;
}

// Função para realizar a pesquisa
void performSearch(LLRBTPage *arquivos) {
    char *searchTerm = malloc(200 * sizeof(char));
    if (scanf("%[^\n]", searchTerm)) {}
    caseInsensitive(searchTerm);

    char *originalTerm = malloc(200 * sizeof(char));
    strcpy(originalTerm, searchTerm);

    char *delim = " \n\t";
    char *token = strtok(searchTerm, delim);
    LLRBTPage *resposta = NULL;

    resposta = procura_arvore(arquivos, token, resposta);

    while (1) {
        token = strtok(NULL, delim);
        if (token == NULL) {
            break;
        }

        LLRBTPage *newA = NULL;
        resposta = procura_arvore(resposta, token, newA);
    }

    printOutput(resposta, originalTerm);

    free(originalTerm);
    free(searchTerm);
}

// Função para imprimir a saída
void printOutput(LLRBTPage *a, char *s) {
    printf("search:%s\n", s);
    printf("pages:");
    printTree(a);
    printf("\n");
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
