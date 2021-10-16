#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 112

typedef struct pilha{
	char c[MAX];
	int topo;
}Pilha;



Pilha* cria_pilha(){
	Pilha *P = (Pilha *) malloc(sizeof(Pilha));
	P->topo = 0;
	memset(P->c, 0, sizeof(P->c));
	return P;
}

void push(Pilha *P, char c){
	P->c[P->topo] = c;
	P->topo++;
}

void pop(Pilha *P){
	P->c[P->topo] = 0;
	P->topo--;
}

int empty(Pilha *P){
	return (!P->topo);
}

int main(void){
	Pilha *P;
	char c;	
		
	P = cria_pilha();
	while(scanf("%c", &c) && c != '\n'){
		if(c == '(')
			push(P, c);
		if(c == ')'){
			if(empty(P)){
				printf("Expressao invalida\n");
				free(P);
				return 0;
			}else{
				pop(P);
			}
		}
	}
	printf("%s\n", (empty(P))? "Expressao Valida" : "Expressao invalida");		
	free(P);

	return 0;
}
