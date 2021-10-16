#include <stdio.h>
#include <stdlib.h>

typedef struct _lista{
	int info;
	struct _lista *prox;
}Lista;

Lista* cria_lista(){
	return NULL;
}

Lista* insere(Lista *l, int x){
	Lista *p, *ant, *novo = (Lista *) malloc(sizeof(Lista));
	novo->info = x;
	if(!l){
		novo->prox = novo;
		return novo;
	}
	ant = p = l;
	if(p->prox != p){
		if(p->info < x){
			do{
				ant = p;
				p = p->prox;
			}while(p != l && p->info < x);
			ant->prox = novo;
			novo->prox = p;
			return l;
		}
		else{
			do{
				ant = p;
				p = p->prox;
			}while(p != l);
			ant->prox = novo;
			novo->prox = p;
			return novo	;			
		}
	}
	novo->prox = p;
	p->prox = novo;
	return (p->info > x)? novo : p;
}

void imprime(Lista *l){
	Lista *p = l;
	if(p)
		do{
			printf("%d\n", p->info);
			p = p->prox;
		}while(p != l);
	else
		printf("\nA lista esta vazia\n");
}

void libera_lista(Lista *l){
	Lista *aux, *p = l->prox;
	while(p != l){
			aux = p;
			free(p);
			p = aux->prox;
	}
	free(l);
}

int main(void){
	Lista *l = cria_lista();
	
	l = insere(l, 10);
	l =	insere(l, 19);
	l =	insere(l, 8);
	l = insere(l, 5);
	l = insere(l, 6);
	l = insere(l, 1);
	l = insere(l, 89);
	l = insere(l, 8);
	l = insere(l, 13);
	imprime(l);
	libera_lista(l);

	return 0;
}
