#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

void swap(void *v, int size, int x, int y){
    void *aux;

    if (x != y){
        aux = malloc(size);

        memcpy(aux, v + x * size, size);
        memcpy(v + x * size, v + y * size, size);
        memcpy(v + y * size, aux, size);

        free(aux);
    }
}

char *read_line(FILE *fp, char terminator){
    char *stretch = NULL;
    int i = 0;

    do{
        stretch = (char *)realloc(stretch, (i + 1) * sizeof(char));
        fscanf(fp, "%c", stretch + i);
        i++;
    }while (!feof(fp) && stretch[i - 1] != terminator);
    // Lendo até o final do arquivo ou até um '\n'

    stretch[i - 1] = '\0';

    return stretch;
}

void randomize_vector(void *v, int size, int n){
    int i, pos;

    for (i = 0; i < n; i++){
        pos = rand() % n;

        swap(v, size, i, pos);
    }
}