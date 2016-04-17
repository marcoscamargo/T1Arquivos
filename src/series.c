#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "series.h"
#include "filemanip.h"

struct Serie{
	unsigned int id; // Campo de tamanho fixo - 4 bytes.
	unsigned int year; // Campo de tamanho fixo - 4 bytes.
	unsigned int season; // Campo de tamanho fixo - 4 bytes.
	char *title; // Campo de tamanho variável.
	char *description; // Campo de tamanho variável.
	char *genre; // Campo de tamanho variável.
	char *production; // Campo de tamanho variável.
};

Serie *read_serie(){
	Serie *s = (Serie *)malloc(sizeof(Serie));

	printf("ID: ");
	scanf("%u%*c", &(s->id));

	printf("Nome: ");
	s->title = read_line(stdin);

	printf("Descricao: ");
	s->description = read_line(stdin);

	printf("Genero: ");
	s->genre = read_line(stdin);

	printf("Producao: ");
	s->production = read_line(stdin);

	printf("Ano de lancamento: ");
	scanf("%u%*c", &(s->year));

	printf("Temporada: ");
	scanf("%u%*c", &(s->season));

	return s;
}

void erase_serie(Serie *s){
	free(s->title);
	free(s->description);
	free(s->genre);
	free(s->production);
	free(s);
}

Data *get_data(const Serie *s){
	Data *d = create_data();
	int len1, len2, len3, len4;
	int offset = 0;

	// Tamanho das strings.
	len1 = strlen(s->title) + 1;
	len2 = strlen(s->description) + 1;
	len3 = strlen(s->genre) + 1;
	len4 = strlen(s->production) + 1;

	// Tamanho dos 3 inteiros e das 4 strings (com seus '\0's).
	d->size = 3 * sizeof(unsigned int) + (len1 + len2 + len3 + len4) * sizeof(char);

	d->data = malloc(d->size);

	// Concatenando os inteiros.
	memcpy(d->data + offset, &(s->id), sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(d->data + offset, &(s->year), sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(d->data + offset, &(s->season), sizeof(unsigned int));
	offset += sizeof(unsigned int);

	// Concatenando as strings.
	memcpy(d->data + offset, s->title, len1 * sizeof(char));
	offset += len1 * sizeof(char);
	memcpy(d->data + offset, s->description, len2 * sizeof(char));
	offset += len2 * sizeof(char);
	memcpy(d->data + offset, s->genre, len3 * sizeof(char));
	offset += len3 * sizeof(char);
	memcpy(d->data + offset, s->production, len4 * sizeof(char));

	return d;
}

/* Recupera a string em um offset passado por parâmetro. */
char *get_string(const void *data, int *offset){
	char *str = NULL;
	int i = 0;

	do{
		str = (char *)realloc(str, (i + 1) * sizeof(char));
		memcpy(str + i, data + (*offset) + i, sizeof(char));
		i++;
	}while (str[i - 1]);

	*offset += i;

	return str;
}

Serie *get_serie(const Data *d){
	Serie *s = (Serie *)malloc(sizeof(Serie));
	int offset = 0;

	// Recuperando os inteiros.
	memcpy(&(s->id), d->data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(&(s->year), d->data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(&(s->season), d->data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);

	// Recuperando as strings.
	s->title = get_string(d->data, &offset);
	s->description = get_string(d->data, &offset);
	s->genre = get_string(d->data, &offset);
	s->production = get_string(d->data, &offset);

	return s;
}

void print_serie(const Serie *s){
	printf("ID: %u\n", s->id);
	printf("Nome: %s\n", s->title);
	printf("Descricao: %s\n", s->description);
	printf("Genero: %s\n", s->genre);
	printf("Producao: %s\n", s->production);
	printf("Ano de lancamento: %u\n", s->year);
	printf("Temporada: %u\n", s->season);
}