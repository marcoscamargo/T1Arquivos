/*	Gabriel Pinto de Camargo - 9293456
	Gabriel Simmel Nascimento - 9050232
	Marcos Cesar Ribeiro de Camargo - 9278045
	Victor Luiz Roquete Forbes - 9293394 	*/

#ifndef UTILS_H
#define UTILS_H

#define and &&
#define or ||
#define not !

#define true 1
#define false 0

typedef unsigned char bool;

/* Lê uma linha e a retorna como string */
char *read_line(FILE *, char);

/* Abre um arquivo ".dat" da pasta "bin/" com o nome passado por parâmetro. */
FILE *open_file(const char *);

/* Aleatoriza as posições dos elementos de um vetor. */
void randomize_vector(void *, int, int);

/* Retorna true caso o ID buscado esteja presente no arquivo de dados. */ 
bool id_already_used(FILE *, unsigned int);

#endif