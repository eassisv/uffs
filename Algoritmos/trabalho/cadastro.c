#include <stdio.h>

int cadastra(struct user usuario){
	FILE *fila;

	fila = fopen("cadastros.txt", "w");
	if(fila == NULL) return 0;
	
}