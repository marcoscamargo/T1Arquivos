# Gabriel Pinto de Camargo - 9293456
# Gabriel Simmel Nascimento - 9050232
# Marcos Cesar Ribeiro de Camargo - 9278045
# Victor Luiz Roquete Forbes - 9293394

all: clean
	@gcc -o main src/*.c -I./includes

debug: clean
	@gcc -o main src/*.c -I./includes -g -Wall

clean:
	@rm bin/*.bin main -f

run: main
	@./main

test: main
	@./main < teste.in

fullrun: debug
	@valgrind -v --track-origins=yes --leak-check=full ./main

fulltest: debug
	@valgrind -v --track-origins=yes --leak-check=full ./main < teste.in

zip:
	@zip -r Grupo_6.zip *
