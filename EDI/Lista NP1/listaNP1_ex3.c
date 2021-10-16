#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _lista{
	char c;
	struct _lista *prox;
}lista;

lista* cria_lista(){
	return NULL;
}

lista* insere_elemento(lista *l, char c){
	lista *p, *novo = (lista *) malloc(sizeof(lista));
	novo->c = c;
	novo->prox = NULL;
	if(!l) return novo;
	for(p = l; p->prox; p = p->prox);
	p->prox = novo;
	return l;
}

void libera_lista(lista *l){
	lista *p = l;
	while(p){
		l = l->prox;
		free(p);
		p = l;
	}
}

void troca_palavra(lista *l1, lista *l2){
	lista *p1 = l1, *p2 = l2;
	char aux;
	while(p1 && p2){
		aux = p1->c;
		p1->c = p2->c;
		p2->c = aux;
		p1 = p1->prox;
		p2 = p2->prox;
	}
}

void imprime(lista *l){
	lista *p = l;
	while(p){
		printf("%c", p->c);
		p = p->prox;
	}
	printf("\n");
}

int main(void){
	lista *l1, *l2;
	char s[112];
	int i;
	
	l1 = l2 = cria_lista();
	if(!fgets(s, 112, stdin))
		return 0;
	for(i = 0; i < (int)strlen(s) - 1; i++)
		l1 = insere_elemento(l1, s[i]);
	if(!fgets(s, 112, stdin))
		return 0;
	for(i = 0; i < (int)strlen(s) - 1; i++)
		l2 = insere_elemento(l2, s[i]);

	troca_palavra(l1, l2);

	imprime(l1);
	imprime(l2);
	
	return 0;
}
