#include <stdio.h>
#include <stdlib.h>

typedef struct _lista{
  int info;
  struct _lista *prox;
}lista;

lista* cria_lista(){
  return NULL;
}

void insere_esq(lista **l, int x){
  lista *p = *l, *novo = (lista *) malloc(sizeof(lista));
  novo->info = x;
  if(!p)
    *l = novo->prox = novo;
  else{
    while(p->prox != *l) //Percorre a lista até encontrar o ultimo elemento
      p = p->prox;
    p->prox = novo;
    novo->prox = (*l);
    *l = novo;
  }
}

void imprime(lista *l){
  lista *p = l;
  if(p){
    do{
      printf("%d ", p->info);
      p = p->prox;
    }while(p != l);
    printf("\n");
  }
  else
    printf("A lista esta vazia\n");
}

int conta_elementos(lista *l){
  lista *p = l;
  if(!l) return 0;
  int num = 1;
  while(p->prox != l){
    num++;
    p = p->prox;
  }
  return num;
}

int exclui_elemento(lista **l, int x){
  lista *p = *l, *ant = NULL;
  if(p){
    if(p->prox == *l){
      if(x == p->info){
	free(p);
	*l = NULL;
	return 1;
      }
      else
	return 0;
    }
    do{
      ant = p;
      p = p->prox;
    }while(p != *l && p->info != x);
    if(p->info != x) return 0;
    if(*l == p) *l = p->prox;
    ant->prox = p->prox;
    free(p);
    return 1;
  }
  return 0;
}

void libera_lista(lista **l){
  lista *p = *l, *aux;
  if(*l){
    p = p->prox;
    while(p != *l){
      aux = p;
      p = p->prox;
      free(aux);
    }
    free(*l);
    *l = NULL;
  }
}

void insere(lista **l, int x){
  lista *p = *l, *novo = (lista *) malloc(sizeof(lista));
  novo->info = x;
  if(*l){
    novo->prox = *l;
    while(p->prox != *l)
      p = p->prox;
    p->prox = novo;
  }
  else{
  novo->prox = novo;
  *l = novo;
  }
}

void concatenar_lista(lista *l1, lista *l2){
  lista *p = l2;
  if(l2)
    do{
      insere(&l1, p->info);
      p = p->prox;
    }while(p != l2);
}

lista * intercalar_lista(lista *l1, lista *l2){
  lista *p1 = l1, *p2 = l2, *nova = cria_lista();
  if(p1 && p2){
    do{
      if(p1){
        insere(&nova, p1->info);
        p1 = p1->prox;
        if(p1 == l1) p1 = NULL;
      }
      if(p2){
        insere(&nova, p2->info);
        p2 = p2->prox;
        if(p2 == l2) p2 = NULL;
      }
    }while(p1 || p2);
    return nova;
  }
    return NULL;
}

lista * copia_lista(lista *l){
  lista *p = l, *nova = cria_lista();
  if(p){
    do{
      insere(&nova, p->info);
      p = p->prox;
    }while(p != l);
    return nova;
  }
  return NULL;
}

int main(void){
  lista *l1, *l2, *l3;
  int ans;

  l1 = cria_lista(); l2 = cria_lista();

  insere_esq(&l1, 1);
  insere_esq(&l1, 3);
  insere_esq(&l1, 5);
  imprime(l1);
  ans = conta_elementos(l1);
  printf("A lista 2 tem %d elementos\n\n", ans);

  insere_esq(&l2, 2);
  insere_esq(&l2, 4);
  insere_esq(&l2, 6);
  imprime(l2);
  ans = conta_elementos(l2);
  printf("A lista 2 tem %d elementos\n\n", ans);


  concatenar_lista(l1, l2);
  printf("Lista 1 e 2 concatenadas\n");
  imprime(l1);
  ans = conta_elementos(l1);
  printf("A lista 1 e 2 concatenadas tem %d elementos\n\n", ans);

  l3 = intercalar_lista(l1, l2);
  printf("Lista 1 e 2 intercaladas\n");
  imprime(l3);
  ans = conta_elementos(l3);
  printf("A lista 1 e 2 intercalada tem %d elementos\n\n", ans);
  libera_lista(&l3);

  l3 = copia_lista(l1);
  printf("Copia da lista 1\n");
  imprime(l3);
  ans = conta_elementos(l3);
  printf("A copia da lista 1 tem %d elementos\n\n", ans);
  libera_lista(&l3);

  libera_lista(&l1);
  libera_lista(&l2);

  return 0;
}

