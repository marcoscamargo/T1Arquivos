#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "filemanip.h"

Data *create_data(){
	return malloc(sizeof(Data));
}

void insert(FILE *fp, const Data *d){
	fseek(fp, 0, SEEK_END);

	// Indicador de tamanho.
	fwrite(&(d->size), sizeof(int), 1, fp);

	// Registro.
	fwrite(d->data, d->size, 1, fp);

	// Update .idx
}

Data *retrieve_data(FILE *fp, int x){
	Data *d = create_data();
	int i, size;

	fseek(fp, sizeof(unsigned int), SEEK_SET); // Pulando o header

	for (i = 0; i < x; i++){
		fread(&size, sizeof(unsigned int), 1, fp); // Lendo o tamanho do registro
		fseek(fp, size, SEEK_CUR); // Pulando o registro
	}

	fread(&size, sizeof(unsigned int), 1, fp); // Lendo o tamanho do registro
	fread(d->data, size, 1, fp);
	d->size = size;

	return d;
}

void erase_data(Data *d){
	free(d->data);
	free(d);
}