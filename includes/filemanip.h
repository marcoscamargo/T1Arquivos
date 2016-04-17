#ifndef FILE_MANIP_H
#define FILE_MANIP_H

typedef struct Data Data;

struct Data{
	void *data;
	int size;
};


/* Aloca memória para armazenar Data. */
Data *create_data();

/* Insere um registro (com seu indicador de tamanho) em um arquivo. */
void insert(FILE *, const Data *);

Data *retrieve_data(FILE *, int);

/* Libera memória de Data. */
void erase_data(Data *);

#endif