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

int comprimento(Lista *l){
	int i = 0;
	Lista *p = l;
	while(p){
		i++;
		p = p->p;
	}
	return i;
}


int main(void){
  Lista *l;
  int ans;

  l = cria_lista();
  l = insere_lista(l, 5);
  l = insere_lista(l, 12); 
  l = insere_lista(l, 7);  
  l = insere_lista(l, 9);
  imprime(l);
  ans = comprimento(l);
  printf("%d\n", ans);
	libera_lista(l);

  return 0;
}
