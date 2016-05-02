/*	Gabriel Pinto de Camargo - 9293456
	Gabriel Simmel Nascimento - 9050232
	Marcos Cesar Ribeiro de Camargo - 9278045
	Victor Luiz Roquete Forbes - 9293394 	*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "series.h"

struct Serie{
	unsigned int id; // Campo de tamanho fixo - 4 bytes.
	unsigned int year; // Campo de tamanho fixo - 4 bytes.
	unsigned int season; // Campo de tamanho fixo - 4 bytes.
	char *title; // Campo de tamanho variável.
	char *description; // Campo de tamanho variável.
	char *genre; // Campo de tamanho variável.
	char *production; // Campo de tamanho variável.

	unsigned int title_len; // Auxiliar.
	unsigned int description_len; // Auxiliar.
	unsigned int genre_len; // Auxiliar.
	unsigned int production_len; // Auxiliar.
	unsigned int size; // Auxiliar.
};

/* Recupera uma string em um offset passado por parâmetro. */
char *get_string(const void *, int *);

Serie *read_serie(){
	Serie *s = (Serie *)malloc(sizeof(Serie));

	printf("ID: ");
	scanf("%u%*c", &(s->id));

	printf("Nome: ");
	s->title = read_line(stdin, '\n');
	s->title_len = strlen(s->title);

	printf("Descricao: ");
	s->description = read_line(stdin, '\n');
	s->description_len = strlen(s->description);

	printf("Genero: ");
	s->genre = read_line(stdin, '\n');
	s->genre_len = strlen(s->genre);

	printf("Producao: ");
	s->production = read_line(stdin, '\n');
	s->production_len = strlen(s->production);

	printf("Ano de lancamento: ");
	scanf("%u%*c", &(s->year));

	printf("Temporada: ");
	scanf("%u%*c", &(s->season));

	// 3 inteiros + 4 cadeias de caracteres + 4 terminadores ('\0').
	s->size = NUMERO_DE_CAMPOS_INTEIROS * sizeof(unsigned int)
	+ s->title_len + s->description_len + s->genre_len + s->production_len
	+ NUMERO_DE_CAMPOS_STRINGS * sizeof(char);

	return s;
}

void erase_serie(Serie *s){
	free(s->title);
	free(s->description);
	free(s->genre);
	free(s->production);
	free(s);
}

void *get_data(const Serie *s){
	void *data = malloc(s->size);
	int offset = 0;

	// Concatenando os inteiros.
	memcpy(data + offset, &(s->id), sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(data + offset, &(s->year), sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(data + offset, &(s->season), sizeof(unsigned int));
	offset += sizeof(unsigned int);

	// Concatenando as strings.
	memcpy(data + offset, s->title, (s->title_len + 1) * sizeof(char));
	offset += (s->title_len + 1) * sizeof(char);
	memcpy(data + offset, s->description, (s->description_len + 1) * sizeof(char));
	offset += (s->description_len + 1) * sizeof(char);
	memcpy(data + offset, s->genre, (s->genre_len + 1) * sizeof(char));
	offset += (s->genre_len + 1) * sizeof(char);
	memcpy(data + offset, s->production, (s->production_len + 1) * sizeof(char));

	return data;
}

Serie *get_serie(const void *data){
	Serie *s = (Serie *)malloc(sizeof(Serie));
	int offset = 0;

	// Recuperando os inteiros.
	memcpy(&(s->id), data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(&(s->year), data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);
	memcpy(&(s->season), data + offset, sizeof(unsigned int));
	offset += sizeof(unsigned int);

	// Recuperando as strings.
	s->title = get_string(data, &offset);
	s->description = get_string(data, &offset);
	s->genre = get_string(data, &offset);
	s->production = get_string(data, &offset);

	return s;
}

unsigned int get_size(const Serie *s){
	return s->size;
}

unsigned int get_id(const Serie *s){
	return s->id;
}

void set_id(Serie *s, unsigned int id){
	s->id = id;
}

void print_serie(const Serie *s){
	printf("ID: %09u\n", s->id);
	printf("Nome: %s\n", s->title);
	printf("Descricao: %s\n", s->description);
	printf("Genero: %s\n", s->genre);
	printf("Producao: %s\n", s->production);
	printf("Ano de lancamento: %u\n", s->year);
	printf("Temporada: %u\n", s->season);
}

Serie **read_generated_series(const char *filename, FILE *fp_data, int n){
	Serie **s = (Serie **)malloc(n * sizeof(Serie *));
	bool flag;
	int i, j;

	// Abrindo o arquivo que contém as séries.
	FILE *fp = fopen(filename, "r");

	// Lendo n séries e gerando IDs aleatórios e únicos para cada uma.
	for (i = 0; i < n; i++){
		s[i] = (Serie *)malloc(sizeof(Serie));

		fscanf(fp, "title=\"");
		s[i]->title = read_line(fp, '\"');
		s[i]->title_len = strlen(s[i]->title);
		fscanf(fp, "%*c");
		
		fscanf(fp, "description=\"");
		s[i]->description = read_line(fp, '\"');
		s[i]->description_len = strlen(s[i]->description);
		fscanf(fp, "%*c");

		fscanf(fp, "year=\"");
		fscanf(fp, "%d", &(s[i]->year));
		fscanf(fp, "%*c%*c");

		fscanf(fp, "season=\"");
		fscanf(fp, "%d", &(s[i]->season));
		fscanf(fp, "%*c%*c");

		fscanf(fp, "genre=\"");
		s[i]->genre = read_line(fp, '\"');
		s[i]->genre_len = strlen(s[i]->genre);
		fscanf(fp, "%*c");

		fscanf(fp, "production=\"");
		s[i]->production = read_line(fp, '\"');
		s[i]->production_len = strlen(s[i]->production);
		fscanf(fp, "%*c%*c");

		// 3 inteiros + 4 cadeias de caracteres + 4 terminadores ('\0').
		s[i]->size = NUMERO_DE_CAMPOS_INTEIROS * sizeof(unsigned int)
		+ s[i]->title_len + s[i]->description_len + s[i]->genre_len
		+ s[i]->production_len + NUMERO_DE_CAMPOS_STRINGS * sizeof(char);

		flag = true;

		// Gerando um ID aleatório e único.
		while (flag){
			s[i]->id = (rand() % (MAX_ID + 1 - MIN_ID)) + MIN_ID;

			flag = false;

			// Verificando no próprio vetor se esse ID já foi gerado.
			for (j = i - 1; j >= 0; j--){
				if (s[j]->id == s[i]->id){
					flag = true;
					break;
				}
			}

			// Verificando no arquivo de dados se esse ID já pertence a outro registro.
			if (!flag and id_already_used(fp_data, s[i]->id)){
				flag = true;
			}
		}
	}

	// Aleatorizando o vetor.
	randomize_vector(s, sizeof(Serie *), n);

	// Fechando o arquivo.
	fclose(fp);

	return s;
}

void erase_generated_series(Serie **s, int n){
	int i;

	for (i = 0; i < n; i++){
		erase_serie(s[i]);
	}

	free(s);
}

char *get_string(const void *data, int *offset){
	char *str = NULL;
	int i = 0;

	do{
		str = (char *)realloc(str, (i + 1) * sizeof(char));
		memcpy(str + i, data + (*offset) + i, sizeof(char));
		i++;
	}while (str[i - 1]);
	// Copiando de data para str até alcançar o caractere '\0'.

	// Atualizando o offset.
	*offset += i;

	return str;
}