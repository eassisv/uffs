#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _nodo{
  int chave, altdir, altesq, nivel, altura;
  struct _nodo *esq, *dir, *pai;
}Nodo;

typedef struct _arvore{
  Nodo *raiz;
}Arvore;

Arvore* inicializa_arvore();
int insere_elemento(Arvore *tree, int valor);
void lista_elementos(Arvore *tree);
void limpa_arvore(Arvore *tree);
int remove_elemento(Arvore *tree, int chave);

int main(void){
  int opcao, valor;
  Arvore *tree = inicializa_arvore();

  do{
    printf("Digite a opção\n1. Inserir elemento.:\n2. Listar valores da árvore.:\n3. Liberar a arvore.:\n0. Sair.:\n");
    scanf("%d", &opcao);
    switch(opcao){
    case 1:
      scanf("%d", &valor);
      insere_elemento(tree, valor);
      break;
    case 2:
      lista_elementos(tree);
      break;
		case 3:
	  	limpa_arvore(tree);
	  	break;
    case 0:
      break;
    default:
      printf("Opcão inválida\n\n");
    }
  }while(opcao);
  limpa_arvore(tree);
  return 0;
}

Arvore* inicializa_arvore(){
  Arvore *novo = (Arvore *) malloc(sizeof(Arvore));
  novo->raiz = NULL;
  return novo;
}

void libera_nodo(Nodo* nodo){
  if(!nodo) return;
  libera_nodo(nodo->dir);
  libera_nodo(nodo->esq);
  free(nodo);
}

void limpa_arvore(Arvore *tree){
  libera_nodo(tree->raiz);
  tree->raiz = NULL;
}

int max(int a, int b){
  return (a > b)? a : b;
}

void atualiza_nivel(Nodo *nodo){
  if(!nodo) return;
  nodo->nivel = (nodo->pai == nodo)? 0 : nodo->pai->nivel + 1;
  atualiza_nivel(nodo->dir);
  atualiza_nivel(nodo->esq);
}

Nodo* atualiza_altura(Nodo *nodo){
  nodo->altdir = (!nodo->dir) ? 0 : nodo->dir->altura + 1;
  nodo->altesq = (!nodo->esq) ? 0 : nodo->esq->altura + 1;
  nodo->altura = max(nodo->altesq, nodo->altdir);

  //Se encontrei um nodo desbalanceado eu retorno o seu endereço para rebalancear
  if(abs(nodo->altesq - nodo->altdir) > 1) return nodo;

  if(nodo->pai != nodo)	return atualiza_altura(nodo->pai);
  return NULL;
}

Nodo* busca_pai(Nodo *pai, Nodo *novo){
  if(pai->chave < novo->chave){
    if(pai->dir)
      return busca_pai(pai->dir, novo);
    pai->dir = novo;
    return pai;
  }
  if(pai->chave > novo->chave){
    if(pai->esq)
      return busca_pai(pai->esq, novo);
    pai->esq = novo;
    return pai;
  }
  //Retorna nulo caso o elemente seja repetido
  return NULL;
}

void rotacao_simples_esquerda(Nodo *subtree, Arvore *tree){
  Nodo *aux = subtree->dir, *pai = subtree->pai;

  if(pai == subtree) tree->raiz = pai = subtree->dir;
  else{
    if(pai->chave < aux->chave) pai->dir = aux;
    else pai->esq = aux;
  }
  subtree->pai = aux;
  subtree->dir = aux->esq;
  if(aux->esq) aux->esq->pai = subtree;
  aux->esq = subtree;
  aux->pai = pai;
  atualiza_altura(subtree);
  atualiza_nivel(aux);
}

void rotacao_simples_direita(Nodo *subtree, Arvore *tree){
  Nodo *aux = subtree->esq, *pai = subtree->pai;
  if(pai == subtree) tree->raiz = pai = subtree->esq;
  else{
    if(pai->chave < aux->chave) pai->dir = aux;
    else pai->esq = aux;
  }
  subtree->pai = aux;
  subtree->esq = aux->dir;
  if(aux->dir) aux->dir->pai = subtree;
  aux->dir = subtree;
  aux->pai = pai;
  atualiza_altura(subtree);
  //atualiza_nivel(aux);
}

void balanceia_arvore(Nodo *subtree, Arvore *tree){
  if(!subtree) return;
  Nodo* aux;
  if(subtree->altesq - subtree->altdir < 0){
    aux = subtree->dir;
    //Verifica se precisa de rotação dupla (joelho)
    if(aux->altesq - aux->altdir > 0) rotacao_simples_direita(aux, tree);
    rotacao_simples_esquerda(subtree, tree);
  }else{
    aux = subtree->esq;
    //Verifica se precisa de rotação dupla (joelho)
    if(aux->altesq - aux->altdir < 0) rotacao_simples_esquerda(aux, tree);
    rotacao_simples_direita(subtree, tree);
  }
}


int insere_elemento(Arvore *tree, int chave){
  Nodo *novo = (Nodo*) malloc(sizeof(Nodo));

  novo->chave = chave;
  novo->esq = novo->dir = NULL;

  if(tree->raiz){
    novo->pai = busca_pai(tree->raiz, novo);
    novo->nivel = novo->pai->nivel + 1;

    //Se não encontrei um pai é porque o elemente é repetido
    if(!novo->pai){
      free(novo);
      return 0;
    }
    //atualiza_nivel(novo);
    balanceia_arvore(atualiza_altura(novo), tree);
    return 1;
  }

  novo->pai = novo;
  novo->nivel = 0;
  //atualiza_nivel(novo);
  atualiza_altura(novo);
  tree->raiz = novo;
  return 1;
}

int calcula_nivel(Arvore *tree, Nodo *nodo){
  return tree->raiz->altura - nodo->altura;
}

void pre_fixa(Arvore *tree, Nodo *nodo){
  if(!nodo) return;
  printf("Chave: %3d, Nivel: %3d, Altura(e/d): %d/%d, Pai: %3d\n", nodo->chave, calcula_nivel(tree, nodo), nodo->altesq, nodo->altdir, nodo->pai->chave);
  pre_fixa(tree, nodo->esq);
  pre_fixa(tree, nodo->dir);
}

void lista_elementos(Arvore *tree){
  if(tree->raiz)
    pre_fixa(tree, tree->raiz);
  printf("\n");
}
