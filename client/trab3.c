#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/ReadContent.h"
#include "../include/PageRank.h"


// Função principal
int main() {
    // TODO: Função de pageRank, Algoritmo de ordenação usando o pageRank,
    // Processar saída, Finalizar (Verificar vazamentos de memória e otimização), Makefile
    char *graph_path = "graph.txt";
    char *stopwords_path = "stopwords.txt";
    char *pages_path = "pages/";

    int numPages = countFileLines(graph_path);
    TST* stopwords = read_stopwords(stopwords_path);
    Page* pages = malloc(sizeof(Page)*numPages);
    readGraphAndCalculatePageRank(graph_path, pages, numPages);
    read_pages(pages_path, pages, numPages, stopwords);
    int tam = strlen("maria");
    String* word_to_be_searched = create_word("maria", tam);
    for(int i=0; i < numPages; i++){
        printf("%s\n\n", pages[i].name);
        printf("%d\n\n", TST_search(pages[i].content, word_to_be_searched));
    }
    //readAndInsertContents(graph_path, pages, numPages);

    return 0;
}
