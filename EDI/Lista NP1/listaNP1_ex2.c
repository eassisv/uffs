#include <stdio.h>
#include <stdlib.h>

typedef struct _Polinomio{
  float a;
  int exp;
  struct _Polinomio *prox;
}Polinomio;

Polinomio* le_polinomio(Polinomio *p, int x, float a){
  Polinomio *aux, *ant, *novo = (Polinomio *) malloc(sizeof(Polinomio));
  novo->a = a;
  novo->exp = x;
  if(p){
    if(p->exp < x){
      novo->prox = p;
      return novo;
    }
    if(p->exp == x){
        p->a += a;
        return p;
    }
    for(aux = p->prox, ant = p; aux && aux->exp >= x; ant = aux, aux = aux->prox){
      if(aux->exp > x) continue;
      if(aux->exp == x){
        aux->a += a;
        return p;
      }
    }
    ant->prox = novo;
    novo->prox = aux;
    return p;
  }
  novo->prox = NULL;
  return novo;
}

void imprime_polinomio(Polinomio *p){
  Polinomio *aux = p;
  while(aux){
    printf("%s", (aux->a >= 0)? "+" : "");
    printf("%.2f", aux->a);
    printf("%s", (aux->exp)? "x" : "");
    (aux->exp)? printf("^%d ", aux->exp): printf(" ");
    aux = aux->prox;
  }
  printf("\n");
}

Polinomio* soma_polinomio(Polinomio *p1, Polinomio *p2){
  Polinomio *aux, *p3 = NULL;
  for(aux = p1; aux; aux = aux->prox)
    p3 = le_polinomio(p3, aux->exp, aux->a);
  for(aux = p2; aux; aux = aux->prox)
    p3 = le_polinomio(p3, aux->exp, aux->a);
  return p3;
}

Polinomio* mult_polinomio(){

}

Polinomio* libera_polinomio(Polinomio *p){
  Polinomio *aux;
  for(aux = p; aux;){
    p = p->prox;
    free(aux);
    aux = p;
  }
  return NULL;
}

int main(void){
  Polinomio *P1 = NULL, *P2 = NULL, *P3 = NULL;

  P1 = le_polinomio(P1, 2, 2.5);
  P1 = le_polinomio(P1, 3, 3);
  P1 = le_polinomio(P1, 2, -5);
  P1 = le_polinomio(P1, 4, 2);
  P1 = le_polinomio(P1, 0, 4);
  P1 = le_polinomio(P1, 4, 3);
  imprime_polinomio(P1);

  P2 = le_polinomio(P2, 2, 3);
  P2 = le_polinomio(P2, 3, 1);
  P2 = le_polinomio(P2, 1, -5);
  P2 = le_polinomio(P2, 4, 4);
  P2 = le_polinomio(P2, 0, 4);
  P2 = le_polinomio(P2, 4, 3);
  imprime_polinomio(P2);

  P3 = soma_polinomio(P1, P2);
  imprime_polinomio(P3);

  P1 = libera_polinomio(P1);
  P2 = libera_polinomio(P2);
  P3 = libera_polinomio(P3);

  imprime_polinomio(P1);
  return 0;
}
