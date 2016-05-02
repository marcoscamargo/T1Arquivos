/*	Gabriel Pinto de Camargo - 9293456
	Gabriel Simmel Nascimento - 9050232
	Marcos Cesar Ribeiro de Camargo - 9278045
	Victor Luiz Roquete Forbes - 9293394 	*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "series.h"
#include "filemanip.h"

// Definindo a quantidade de registros a serem lidos do arquivo "series.dat"
#define N 100

void print_data(FILE *fp){
	void *data;
	Serie *s;

	// Posicionando o ponteiro no começo do arquivo.
	fseek(fp, 0, SEEK_SET);

	// Forçando a flag EOF.
	fscanf(fp, "%*c");

	printf("Pressione enter para ver a proxima serie.\n\n");

	while (!feof(fp)){
		// Voltando um byte atrás.
		fseek(fp, -sizeof(char), SEEK_CUR);

		// Recuperando o registro na posição atual.
		data = retrieve_data(fp);

		// Transformando os dados em uma struct Série.
		s = get_serie(data);

		// Ignorando um caractere da stdin (o enter a ser pressionado).
		scanf("%*c");

		// Imprimindo a Série lida.
		print_serie(s);
		printf("\n");

		// Liberando a memória alocada nessa iteração.
		erase_serie(s);
		free(data);

		// Forçando a flag EOF a ser setada.
		fscanf(fp, "%*c");
	}
}

void print_data_by_id(FILE *fp, unsigned int id){
	void *data;
	Serie *s;

	// Posicionando o ponteiro no começo do arquivo.
	fseek(fp, 0, SEEK_SET);

	// Forçando a flag EOF.
	fscanf(fp, "%*c");

	while (!feof(fp)){
		// Voltando um byte atrás.
		fseek(fp, -sizeof(char), SEEK_CUR);

		// Recuperando o registro na posição atual.
		data = retrieve_data(fp);

		// Transformando os dados em uma struct Série.
		s = get_serie(data);

		// Se achou a Série com o ID buscado.
		if (get_id(s) == id){
			// Imprimindo a série lida.
			print_serie(s);
			printf("\n");

			// Liberando memória.
			erase_serie(s);
			free(data);
			
			return;
		}

		// Liberando a memória alocada nessa iteração.
		erase_serie(s);
		free(data);

		// Forçando a flag EOF a ser setada.
		fscanf(fp, "%*c");
	}

	// Se não encontrou a Série buscada em nenhuma iteração.
	printf("Serie nao encontrada.\n");
}

int main(int argc, char *argv[]){
	char *filename; // Nome do arquivo.
	int op, id, i; // Opção do menu, ID de uma Série, iterador.
	void *data; // Dados.
	FILE *fp; // Ponteiro de arquivo.
	Serie **gen; // Vetor de Séries geradas.
	Serie *s; // Série.

	// Setando uma seed de acordo com o horário do sistema.
	srand(time(NULL));

	// Lendo o nome do arquivo de dados.
	printf("Nome do arquivo de dados: ");
	filename = read_line(stdin, '\n');

	// Abrindo o arquivo para leitura e escrita.
	fp = open_file(filename);
	free(filename);

	op = 1;

	// Loop principal.
	while (op){
		printf("\n");
		printf("1 - Gerar series.\n");
		printf("2 - Inserir serie.\n");
		printf("3 - Buscar serie.\n");
		printf("4 - Imprimir series.\n");
		printf("0 - Sair.\n");
		scanf("%d%*c", &op);
		printf("\n");

		switch (op){
			case 1:
				// Lê as Séries do arquivo "series.dat".
				gen = read_generated_series("series.dat", fp, N);
				
				// Inserindo os registros no arquivo.
				for (i = 0; i < N; i++){
					data = get_data(gen[i]);
					insert(fp, data, get_size(gen[i]));
					free(data);
				}

				printf("Series geradas com sucesso.\n");

				// Liberando a memória alocada para armazenar as séries.
				erase_generated_series(gen, N);
				break;
			case 2:
				// Lendo a série da stdin.
				s = read_serie();

				// Impedindo que o usuário digite um ID já presente no arquivo de dados.
				while (id_already_used(fp, get_id(s))){
					printf("\nID invalido, digite novamente: ");
					scanf("%d%*c", &id);
					set_id(s, id);
				}

				// Concatenando os dados da Série.
				data = get_data(s);

				// Inserindo os dados da Série no arquivo.
				insert(fp, data, get_size(s));

				printf("\nSerie inserida no arquivo de dados com sucesso.\n");

				// Apagando a struct Serie.
				erase_serie(s);

				// Apagando a Série concatenada.
				free(data);
				break;
			case 3:
				// Recebendo o ID a ser buscado.
				printf("ID: ");
				scanf("%d%*c", &id);
				printf("\n");

				// Buscando o ID inserido pelo usuário.
				print_data_by_id(fp, id);

				break;
			case 4:
				// Imprimindo todos os registros presentes no arquivo.
				print_data(fp);
				break;
			default:
				break;
		}
	}

	// Fechando o arquivo de dados.
	fclose(fp);

	return 0;
}