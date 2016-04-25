#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Serie{
	unsigned int id; // Campo de tamanho fixo - 4 bytes.
	unsigned int year; // Campo de tamanho fixo - 4 bytes.
	unsigned int season; // Campo de tamanho fixo - 4 bytes.
	char *title; // Campo de tamanho variável.
	char *description; // Campo de tamanho variável.
	char *genre; // Campo de tamanho variável.
	char *production; // Campo de tamanho variável.
};




void retrieve_series(FILE *fp){
/*	char* string = NULL;
	size_t size;

	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';



	printf("%s\n", string);
	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';
	printf("%s\n", string);
	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';
	printf("%s\n", string);
	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';
	printf("%s\n", string);
	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';
	printf("%s\n", string);
	getline(&string, &size, fp);
	string[strlen(string)-1] = '\0';
	printf("%s\n", string);*/


	char string[200];
	fscanf(fp, "title=%s", string);
	printf("%s\n", string);
	fscanf(fp, "description=%s", string);
	printf("%s\n", string);
	// fscanf(fp, "year=\"%[^\"]s", string);
	fscanf(fp, "%s", string);
	printf("%s\n", string);
	// fscanf(fp, "genre=\"%[^\"]s", string);
	fscanf(fp, "%s", string);
	printf("%s\n", string);
	// fscanf(fp, "production=\"%[^\"]s", string);
	fscanf(fp, "%s", string);
	printf("%s\n", string);

}




int main(int argc, char* argv[]){
	
	FILE *fp = fopen(argv[1], "r");

	retrieve_series(fp);



	fclose(fp);
	return 0;
}