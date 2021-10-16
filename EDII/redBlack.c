#include <stdio.h>
#include <stdlib.h>

#define RED 'R'
#define BLACK 'B'
 
typedef struct _Nodo{
  int chave;
  char cor;
  struct _Nodo *esq, *dir, *pai;
}Nodo;
 
typedef struct _Arvore{
  Nodo *raiz;
}Arvore;
 
Arvore* inicializa();
int insere_elemento(Arvore *tree, int chave);
void imprime_arvore(Arvore *tree);
 
int main(void){
  Arvore *RBtree = inicializa();
  int opcao, chave;
  do{
    printf("\tEscolha a opcao\n");
    printf("1. Inserir elemento\n2. Exibir arvore\n0. Encerrar programa\nOpcao: ");
    scanf("%d", &opcao);
    switch(opcao){
    case 1: 
      printf("Digite o valor: ");
      scanf("%d", &chave);          
      printf("\nElemento %s\n\n", (insere_elemento(RBtree, chave)? "inserido" : "repetido"));
      break;
    case 2:
      imprime_arvore(RBtree);
      break;
		case 0:
			break;
    default:
      printf("Opcao invalida\n");
    }   
  }while(opcao != 0);
  return 0;
}
 
Arvore* inicializa(){
  Arvore *novo = (Arvore *) malloc(sizeof(Arvore));
  novo->raiz = NULL;
  return novo;
}
 
Nodo* busca_pai(Nodo *pai, Nodo *nodo){
  if(pai->chave > nodo->chave){
    if(pai->esq) return busca_pai(pai->esq, nodo);
    pai->esq = nodo;
    return pai;
  }
  if(pai->chave < nodo->chave){
    if(pai->dir) return busca_pai(pai->dir, nodo);
    pai->dir = nodo;
    return pai;
  }
  return NULL;
}
 
void pre_ordem(Nodo *nodo, int nivel){
  if(!nodo) return;
  pre_ordem(nodo->esq, nivel+1);
  printf("Chave: %d Cor: %s Pai: %d Nivel: %d %s\n", nodo->chave, nodo->cor == RED ? "RED" : "BLACK", nodo->pai->chave, nivel, nodo->pai == nodo ? " <- Raiz" : "" );
  pre_ordem(nodo->dir, nivel+1);
}
 
void imprime_arvore(Arvore *tree){
  printf("\n");  
  pre_ordem(tree->raiz, 0);
  printf("\n");
}
 
void inicializa_nodo(Nodo *nodo, int c){
  nodo->cor = RED;
  nodo->dir = nodo->esq = NULL;
  nodo->chave = c;
}
 
void muda_cor(Nodo *nodo){
  nodo->cor = nodo->cor == RED ? BLACK : RED;
}
 
void rotacao_esquerda(Nodo *subtree, Arvore *tree){
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
}
  
void rotacao_direita(Nodo *subtree, Arvore *tree){
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
}
 
void arvore_fix(Arvore *tree, Nodo *nodo){
  Nodo *tio, *avo;
  avo = nodo->pai->pai;
  tio = (nodo->chave < avo->chave) ? avo->dir : avo->esq;
  while(nodo->pai->cor == RED){
    if(tree->raiz == nodo){
      nodo->cor = BLACK;
    }
    else if(!tio || tio->cor == BLACK){
      if(nodo->chave < avo->chave){
				if(nodo->chave > nodo->pai->chave){
					rotacao_esquerda(nodo->pai, tree);
					avo = nodo->pai;
					nodo = nodo->esq;
				}
				muda_cor(nodo->pai);
				muda_cor(avo);
				rotacao_direita(avo, tree);	
      }else{
				if(nodo->chave < nodo->pai->chave){
					rotacao_direita(nodo->pai, tree);
					avo = nodo->pai;
					nodo = nodo->dir;
				}
				muda_cor(nodo->pai);
				muda_cor(avo);
				rotacao_esquerda(avo, tree);	
      }
    }else{
      muda_cor(nodo->pai);
      muda_cor(tio);
      muda_cor(avo);
      nodo = avo;
      avo = nodo->pai->pai;
      tio = (nodo->chave < avo->chave) ? avo->dir : avo->esq;
    }
  }
}
 
int insere_elemento(Arvore *tree, int chave){
  Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
  inicializa_nodo(nodo, chave);
     
  if(!tree->raiz){
    nodo->pai = nodo;
    tree->raiz = nodo;
  }else{
    nodo->pai = busca_pai(tree->raiz, nodo);
  }
  if(!nodo->pai){
		free(nodo);		
		return 0;
	}
  if(nodo->pai->cor == RED) arvore_fix(tree, nodo);
  return 1; 
}

