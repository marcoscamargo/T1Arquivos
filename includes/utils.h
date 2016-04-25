#ifndef UTILS_H
#define UTILS_H

#define and &&
#define or ||
#define not !

#define true 1
#define false 0

typedef unsigned char bool;

/* Lê uma linha e transforma em uma string */
char *read_line(FILE *, char);

#endif