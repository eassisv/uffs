#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define consoante p->c != 'a' && p->c != 'e' && p->c != 'i' && p->c != 'o' && p->c != 'u' && p->c != 'A' && p->c != 'E' && p->c != 'I' && p->c != 'O' && p->c != 'U'

typedef struct _lista{
  char c;
  struct _lista *prox;
  struct _lista *ant;
}Lista;

Lista* cria_lista(){
  return NULL;
}

Lista* insere_char(Lista *l, char c){
  Lista *p = l, *novo = (Lista *) malloc(sizeof(Lista));
  novo->c = c;
  novo->prox = NULL;
  if(!p){
    novo->ant = NULL;
    return novo;
  }
  while(p->prox){
    p = p->prox;
  }
  p->prox = novo;
  novo->ant = p;
  return l;
}

void libera_lista(Lista *l){
  Lista *p = l;
  while(p){
    l = l->prox;
    free(p);
    p = l;
  }
}

Lista* criptografa(Lista *l){
  Lista *p = l, *aux1, *aux2;
  int i = 0;
  char res;
  while(p){
    i = 0;
    aux1 = p;
    while(consoante)
      {
        p = p->prox;
        i++;
        if(!p->prox){
          i++;
          break;
        }
      }
    if(i > 1){
      printf("%c\n", p->c);
      if(!p->prox)
        aux2 = (consoante) ? p : p->ant;
      else
        aux2 = p->ant;
      for(; i > 1; aux1 = aux1->prox, aux2 = aux2->ant){
        res = aux2->c;
        aux2->c = aux1->c;
        aux1->c = res;
        i -= 2;
      }
    }
    if(p)
      p = p->prox;
  }
  for(p = l, i = 0; p->prox; p = p->prox, i++);
  aux1 = l;
  aux2 = p;
  for(; i > 2; i -= 2){
    res = aux1->c;
    aux1->c = aux2->c;
    aux2->c = res;
    aux2 = aux2->ant;
    aux1 = aux1->prox;
  }
  return l;
}

void imprime_lista(Lista *l){
  Lista *p = l;
  while(p){
    printf("%c", p->c);
    p = p->prox;
  }
  printf("\n");
}

int main(void){
  char c[112];
  Lista *l;
  int i;

  l = cria_lista();

  if(fgets(c, 112, stdin) == NULL)
    return 0;

  for(i = 0; i < (int) strlen(c)-1; i++){
    l = insere_char(l, c[i]);
  }
  imprime_lista(l);
  printf("criptografia\n");
  l = criptografa(l);
  printf("imprime\n");
  imprime_lista(l);
  libera_lista(l);

  return 0;
}
