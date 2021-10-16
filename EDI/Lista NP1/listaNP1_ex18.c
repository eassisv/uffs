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

int compara(Lista *l, Lista *p){
	Lista *l1 = l, *p1 = p;
	while(p1 && l1){
		if(p1->x != l1->x)
			return 0;
		p1 = p1->p;
		l1 = l1->p;		
	}
	return (!p1 && !l1);
}


int main(void){
  Lista *l1, *l2;
  int ans;

  l1 = cria_lista();
  l1 = insere_lista(l1, 9);
  l1 = insere_lista(l1, 5); 
  l1 = insere_lista(l1, 12);  
  l1 = insere_lista(l1, 7);
  imprime(l1);
  
  l2 = cria_lista();
  l2 = insere_lista(l2, 5);
  l2 = insere_lista(l2, 12); 
  l2 = insere_lista(l2, 7);  
  imprime(l2);
  
  ans = compara(l1, l2);
  printf("%s\n", (ans)? "Listas iguais": "Lista diferentes");
	libera_lista(l1);
	libera_lista(l2);
  return 0;
}
