#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

char *read_line(FILE *fp){
    char *stretch = NULL;
    int i = 0;

    do{
        stretch = (char *)realloc(stretch, (i + 1) * sizeof(char));
        fscanf(fp, "%c", stretch + i);
        i++;
    }while (!feof(fp) && stretch[i - 1] != '\n');
    // Lendo até o final do arquivo ou até um '\n'

    stretch[i - 1] = '\0';

    return stretch;
}