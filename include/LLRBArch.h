#include <stdlib.h>
#include <stdio.h>


typedef struct llrbt LLRBT;

LLRBT * create_node(char*, int);

int is_red(LLRBT*);

LLRBT* rotate_left(LLRBT *);

LLRBT* rotate_right(LLRBT *);

void flip_colors(LLRBT *);

LLRBT* RBT_insert(LLRBT *, char * );

int search(LLRBT * , char * );

void free_tree(LLRBT*);