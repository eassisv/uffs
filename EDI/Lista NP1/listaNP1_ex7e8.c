#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
  int x;
  struct lista *p;
}Lista;

Lista *cria_lista(){
  return NULL;
}
Lista* insere_lista(Lista *l, int n){
  Lista *novo = (Lista *) malloc(sizeof(Lista));
  novo->x = n; novo->p = l;
  return novo;
}

void libera_lista(Lista *l){
  Lista *p = l;
  while(!p){
    l = p->p;
    free(p);
    p = l;
  }
}

void imprime(Lista *l){
  Lista *p;
  for(p = l; p != NULL; p = p->p)
    printf("%d ", p->x);
  printf("\n");
}

void imprime_circ(Lista *l){
  Lista *p = l;
  if(p)
  	do{
  		printf("%d ", p->x);
  		p = p->p;
  	}while(p != l);
  printf("\n");
}

void simples_to_circ(Lista *l){
	Lista *p = l;
	if(p){
		for(; p->p; p = p->p);
		p->p = l;
	}
}

void circ_to_simples(Lista *l){
	Lista *p = l;
	if(p){
		for(; p->p != l; p = p->p);
		p->p = NULL;
	}
}

int main(void){
  Lista *l;

  l = cria_lista();
  l = insere_lista(l, 5);
  l = insere_lista(l, 12);   
  imprime(l);
 
 	simples_to_circ(l);
	imprime_circ(l);
	
	circ_to_simples(l);
	imprime(l);
	
  return 0;
}
