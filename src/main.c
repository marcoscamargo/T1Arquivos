#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "series.h"
#include "filemanip.h"

// Indicador de tamanho para registros.

// indicador de tamanho | int | int | int | strlen(1) + 1 | strlen(2) + 1
// strlen(3) + 1 | strlen(4) + 1

// Criar uma struct com o Header, o fp e indicador da última posição acessada.

FILE *open_file(const char *filename){
	FILE *fp = fopen(filename, "a+");
	int aux = 0;

	if (!ftell(fp)){
		fwrite(&aux, sizeof(unsigned int), 1, fp);
	}

	return fp;
}

int main(int argc, char *argv[]){
	char *filename;
	int op = 1;
	FILE *fp;
	Serie *s;
	Serie **gen;
	Data *d;
	int i, n;

	srand(time(NULL));

	printf("Nome do arquivo: ");
	filename = read_line(stdin, '\n');

	fp = open_file(filename);

	while (op){
		printf("1 - Gerar series.\n");
		printf("2 - Inserir serie.\n");
		printf("3 - Buscar serie.\n");
		printf("4 - Imprimir series.\n");
		scanf("%d", &op);

		switch (op){
			case 1:
				n = 100;

				gen = read_generated_series(n);
				
				for (i = 0; i < n; i++){
					print_serie(gen[i]);
					printf("\n");
				}

				free_generated_series(gen, n);
				break;
			case 2:
				s = read_serie();
				d = get_data(s);
				insert(fp, d);
				erase_serie(s);
				erase_data(d);
				break;
			case 3:

				break;
			case 4:
				// Uma por vez?
				// ("Aperte enter para ir para á próxima série.").
				fseek(fp, 0, SEEK_SET);

				while (!feof(fp)){
					d = retrieve_data(fp, i);
					s = get_serie(d);
					print_serie(s);
					printf("\n");
					erase_data(d);
					erase_serie(s);
				}

				break;
			default:
				break;
		}
	}

	free(filename);
	fclose(fp);

	return 0;
}