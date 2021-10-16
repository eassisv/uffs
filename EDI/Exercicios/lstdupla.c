#include <stdio.h>
#include <stdlib.h>

typedef struct _lst_dupla{
  int info;
  struct _lst_dupla *ant;
  struct _lst_dupla *prox;
}lst_dupla;

lst_dupla* cria_lista(){
  return NULL;
}

lst_dupla* insere_lista(lst_dupla *l, int x){
  lst_dupla *p = l, *novo = (lst_dupla *) malloc(sizeof(lst_dupla));
  novo->info = x;
  if(!l){
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
  }
  if(x < p->info){
    for(p = l; x < p->info; p = p->prox)
      if(!p->prox){
	novo->ant = p;
	novo->prox = p->prox;
	p->prox = novo;
	return l;
      }
    novo->prox = p;
    novo->ant = p->ant;
    p->ant = novo;
    p = novo->ant;
    p->prox = novo;
    return l;
  }
  novo->prox = p;
  novo->ant = NULL;
  p->ant = novo;
  return novo;
}

lst_dupla* remove_lista(lst_dupla *l, int x){
  lst_dupla *p = l, *aux;
  if(!l){
    printf("Elemento nao encontrado\n");
    return l;
  }
  if(p->info != x){
    for(; p; p = p->prox)
      if(p->info == x){
	aux = p->ant;
	p = p->prox;
	aux->prox = p;
	p->ant = aux;
	return l;
      }
    printf("Elemento nao encontrado\n");
    return l;
  }
  p = p->prox;
  p->ant = NULL;
  free(l);
  return p;
}

void imprime_lista(lst_dupla *l){
  lst_dupla *p;
  for(p = l; p; p = p->prox)
    printf("%d ", p->info);
  printf("\n");
}

lst_dupla* libera_lista(lst_dupla *l){
  lst_dupla *p;
  while(l){
    p = l;
    l = l->prox;
    free(p);
  }
  return NULL;
}

int main(void){
  lst_dupla *l;

  l = cria_lista();
  l = insere_lista(l, 5);
  l = insere_lista(l, 10); 
  l = insere_lista(l, -4);
  l = insere_lista(l, 56);
  l = insere_lista(l, -8);
  imprime_lista(l);
  l = remove_lista(l, -4);
  imprime_lista(l);
  l = remove_lista(l, -8);
  l = remove_lista(l, 56);
  imprime_lista(l);
  l = libera_lista(l);
  imprime_lista(l);
  l = remove_lista(l, -4);
 
  return 0;
}
