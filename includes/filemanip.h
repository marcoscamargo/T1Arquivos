/*	Gabriel Pinto de Camargo - 9293456
	Gabriel Simmel Nascimento - 9050232
	Marcos Cesar Ribeiro de Camargo - 9278045
	Victor Luiz Roquete Forbes - 9293394 	*/

#ifndef FILE_MANIP_H
#define FILE_MANIP_H

/* Insere um registro no final do arquivo. */
void insert(FILE *, const void *, unsigned int);

/* Recupera o registro na posição atual do arquivo. */
void *retrieve_data(FILE *);

#endif