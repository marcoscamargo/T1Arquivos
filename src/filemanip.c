/*	Gabriel Pinto de Camargo - 9293456
	Gabriel Simmel Nascimento - 9050232
	Marcos Cesar Ribeiro de Camargo - 9278045
	Victor Luiz Roquete Forbes - 9293394 	*/

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "series.h"
#include "filemanip.h"

void insert(FILE *fp, const void *data, unsigned int size){
	// Indo para o final do arquivo.
	fseek(fp, 0, SEEK_END);

	// Escrevendo os dados no arquivo.
	fwrite(data, size, 1, fp);
}

void *retrieve_data(FILE *fp){
	void *data = malloc(NUMERO_DE_CAMPOS_INTEIROS * sizeof(unsigned int));
	int offset, i;

	// Lendo os 3 inteiros.
	fread(data, sizeof(unsigned int), NUMERO_DE_CAMPOS_INTEIROS, fp);
	offset = NUMERO_DE_CAMPOS_INTEIROS * sizeof(unsigned int);

	// Lendo as 4 strings.
	for (i = 0; i < NUMERO_DE_CAMPOS_STRINGS; i++){
		do{
			data = realloc(data, (offset + sizeof(char)));
			fread(data + offset, sizeof(char), 1, fp);
			offset += sizeof(char);
		}while (*((char *)(data + offset - sizeof(char))));
	}

	return data;
}