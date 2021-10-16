#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int info;
	struct lista *prox;
}Lista;

Lista* lista_cria(){
	return NULL;
}

Lista* insere(Lista *l, int x){
	Lista *p, *ant, *novo = (Lista *) malloc(sizeof(Lista));
	novo->info = x;
	for(p = l, ant = NULL; p != NULL; ant = p, p = p->prox)
		if(p->info >= x){
			novo->prox = p;
			if(!ant)
				return novo;
			ant->prox = novo;	
			return l;
		}
	if (ant && !p){
		ant->prox = novo;
		novo->prox = NULL;
		return l;
	}
	novo->prox = NULL;
	return novo;
}

void imprime_lista(Lista *l){
	Lista *p;
	for(p = l; p != NULL; p = p->prox)
		printf("%d ", p->info);
	printf("\n");
}

void libera_lista(Lista *l){
	Lista *p;
	while(l != NULL){
	 p = l;
	 l = p->prox;
	 free(p);
	 }
}

int main(void){
	Lista *l;
		
	l = lista_cria();
	l = insere(l, 5);
	l = insere(l, 7);
	l = insere(l, 3);
	l = insere(l, 8);
	l = insere(l, 9);
	l = insere(l, 0);
	l = insere(l, 1);
	imprime_lista(l);
	libera_lista(l);						
	
	return 0;
}
