/*  Gabriel Pinto de Camargo - 9293456
    Gabriel Simmel Nascimento - 9050232
    Marcos Cesar Ribeiro de Camargo - 9278045
    Victor Luiz Roquete Forbes - 9293394    */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "series.h"
#include "filemanip.h"

/* Troca dois elementos de posição em um vetor. */
void swap(void *, int, int, int);

char *read_line(FILE *fp, char terminator){
    char *stretch = NULL;
    int i = 0;

    do{
        stretch = (char *)realloc(stretch, (i + 1) * sizeof(char));
        fscanf(fp, "%c", stretch + i);
        i++;
    }while (!feof(fp) && stretch[i - 1] != terminator);
    // Lendo até o final do arquivo ou até um caractere terminador
    // passado por parâmetro.

    stretch[i - 1] = '\0';

    return stretch;
}

FILE *open_file(const char *filename){
    char *path = (char *)malloc((strlen(filename) + strlen("bin/") + strlen(".bin") + 1) * sizeof(char));
    FILE *fp;

    sprintf(path, "bin/%s.bin", filename);

    fp = fopen(path, "a+");

    free(path);

    return fp;
}

void randomize_vector(void *v, int size, int n){
    int i, pos;

    // Trocando o elemento na posição i com o elemento em uma posição aleatória.
    for (i = 0; i < n; i++){
        pos = rand() % n;

        swap(v, size, i, pos);
    }
}

bool id_already_used(FILE *fp, unsigned int id){
    void *data;
    Serie *s;

    // Começando um byte a frente.
    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%*c");

    while (!feof(fp)){
        // Voltando um byte atrás.
        fseek(fp, -sizeof(char), SEEK_CUR);

        // Recuperando o registro na posição atual.
        data = retrieve_data(fp);

        // Transformando os dados em uma struct Série.
        s = get_serie(data);

        // Se o ID buscado for encontrado.
        if (get_id(s) == id){
            erase_serie(s);
            free(data);

            return true;
        }

        // Liberando a memória alocada nessa iteração.
        erase_serie(s);
        free(data);

        // Forçando a flag EOF a ser setada.
        fscanf(fp, "%*c");
    }

    return false;
}

void swap(void *v, int size, int x, int y){
    void *aux;

    // Troca os elementos de posição apenas se a posição deles no vetor for diferente.
    if (x != y){
        aux = malloc(size);

        memcpy(aux, v + x * size, size);
        memcpy(v + x * size, v + y * size, size);
        memcpy(v + y * size, aux, size);

        free(aux);
    }
}