#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _lista{
	int info;
	struct _lista *ant, *prox;
}lista;

lista* criaLista(){
	return NULL;
}

lista* insereElemento(lista *l, int x){
	lista *novo = (lista *) malloc(sizeof(lista));
	novo->info = x;
	novo->ant = NULL;
	if(l == NULL)
		novo->prox = NULL;
	else
		novo->prox = l;
	return novo;
}

lista* removeElemento(lista *l){
	lista *aux;
	aux = l->prox;
	aux->ant = NULL;
	free(l);
	return aux;
}

lista* liberaLista(lista *l){
	lista *aux = l;
	while(aux){
		l = l->prox;
		free(aux);
		aux = l;
	}
	return NULL;
}

void imprimeLista(lista *l){
	lista *p = l;
	while(p){
		printf("%d\n", p->info);
		p = p->prox;
	}
}

lista* selSort(lista *l){
	lista *i, *j, *aux, *key = l;
	if(l){
		for(i = l->prox; i; i = i->prox){
			key = i;
			for(j = i->ant; j; j = j->ant)
				if(j->info > key->info){
					j->prox = key;
					break;
				}else{
					if(key->prox){
						aux = key->prox;
						aux->ant = j;
					}
					key->prox = j;
					key->ant = j->ant;
					j->ant = key;
				}
		}
	}
	return (!l->ant)? l: key;
}

int main(void){
	lista *list;
	time_t now;
	int n = 11, i;
	double tempo;
	list = criaLista();
	for(i = 0; i < n; i++)
		list = insereElemento(list, rand()%999+1);
	imprimeLista(list);
	time(&now);
	printf("Ordenando\n");
	list = selSort(list);
	imprimeLista(list);
	tempo = difftime(time(NULL), now);
	printf("%.3lf\n", tempo);
	list = liberaLista(list);
	return 0;
}