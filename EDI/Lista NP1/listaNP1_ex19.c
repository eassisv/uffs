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

Lista* separa(Lista *l, int n){
	Lista *p = l, *ant;
	for(ant = p, p = p->p; p; ant = p, p = p->p)
		if(p->x == n){
			ant->p = NULL;
			return p;
		}
	return NULL;
}


int main(void){
  Lista *l1, *l2;

  l1 = cria_lista();
  l1 = insere_lista(l1, 9);
  l1 = insere_lista(l1, 5); 
  l1 = insere_lista(l1, 12);  
  l1 = insere_lista(l1, 7);
  imprime(l1);
  
  l2 = cria_lista();
  l2 = separa(l1, 5);

	imprime(l2);	
	imprime(l1);
	
	libera_lista(l1);
	libera_lista(l2);
  return 0;
}
