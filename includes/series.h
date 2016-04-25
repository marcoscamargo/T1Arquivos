#ifndef SERIES_H
#define SERIES_H

#include "filemanip.h"

typedef struct Serie Serie;

/* Lê os dados de uma Série da stdin. */
Serie *read_serie();

/* Apaga a memória alocada para armazenar os dados de uma Série. */
void erase_serie(Serie *);

/* Concatena os dados de uma Série. */
Data *get_data(const Serie *);

Serie *get_serie(const Data *);

/* Imprime os dados de uma série. */
void print_serie(const Serie *);

Serie **read_generated_series(int);

void free_generated_series(Serie **, int);

#endif