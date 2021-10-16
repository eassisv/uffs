#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _nodo { // estrutura nó.
	int *chaves; // ponteiro para as chaves do nodo
	struct _nodo **filhos; // ponteiro para os filhos dos nodos
	int numChaves; // numero de chaves que existe em cada nodo
	bool folha; // booleana que verifica se o nodo é folha
}TpNodo;

typedef struct _arvore{ // estrutura da árvore.
	struct _nodo *raiz; // ponteiro para raiz
}TpArvore;

void imprimeMenu();
bool insereElemento(TpArvore *arvore, int N, int T);
TpArvore* inicializaArvore();
void imprimeElementos(TpNodo *raiz, int n);

int main(){
	int T, opcao, valor;
	system("cls");
	//system("clear");
	printf("Digite o valor de T seu arrombado!: ");
	scanf("%d", &T);

	TpArvore *BArvore = inicializaArvore();
	do{
    	imprimeMenu();
    	scanf("%d", &opcao);
    	system("cls");
    	//system("clear");
    	switch(opcao){
    	case 0:
    		exit(0);
    	case 1:
    		printf("Digite o valor que deseja inserir: ");
    		scanf("%d", &valor);
    		getchar();
    		if(!insereElemento(BArvore, valor, T))
				printf("\nElemento ja inserido\n");
    		else
				printf("\nElemento inserido com sucesso\n");
    		break;
    	case 2:
    		system("cls");
    		//system("clear");
    		imprimeElementos(BArvore->raiz, 0);
    		getchar();
    		break;
    	default:
    		printf("Opcao invalida, digite novamente\n");
    	}
    	puts("\nAperte ENTER para voltar ao menu.");
    	getchar();
  	}while(opcao != 0);
}


void imprimeMenu(){
	system("cls");
	//system("clear");
	printf("1 - Inserir elemento\n");
	printf("2 - Imprimir elementos\n");
	printf("0 - Sair\n");
	printf("\nOpcao: ");
}

void imprimeElementos(TpNodo *raiz, int n){
	char *espacos = (char *) malloc(sizeof(char) * n);
	memset(espacos, 0, sizeof(espacos));
	for(int i = 0; i < n; i++) strcat(espacos, " ");
		printf("%s", espacos);
	for(int i = 0; i < raiz->numChaves; i++)
		printf("%d ", raiz->chaves[i]);
	free(espacos);
	printf("\n");
	if(!raiz->folha)
	    for(int i = 0; i < raiz->numChaves + 1; i++)
    		imprimeElementos(raiz->filhos[i], n + 2);
}

TpArvore* inicializaArvore(){
	TpArvore *novo = (TpArvore *) malloc(sizeof(TpArvore));
	novo->raiz = NULL;
	return novo;
}

TpNodo* inicializaNodo(int *valores, int qtd, int T){
	TpNodo *novoNodo = (TpNodo *) malloc(sizeof(TpNodo));
	int tChaves = 2 * T - 1, tFilhos = 2 * T;
	novoNodo->chaves = (int *) malloc(sizeof(int) * tChaves);
	for(int i = 0; i < qtd; i++){
		novoNodo->chaves[i] = valores[i];
	}
	novoNodo->numChaves = qtd;
	novoNodo->filhos = (TpNodo **) malloc(sizeof(TpNodo *) * tFilhos);
	novoNodo->folha = true;

	return novoNodo;
}

TpNodo* divideNodo(TpNodo *nodo, TpNodo *filho, int pos, int T){
	TpNodo *fdir = inicializaNodo(filho->chaves + T, T - 1, T);
	for(int i = T; i < 2 * T; i++)
	    fdir->filhos[i - T] = filho->filhos[i];
	filho->numChaves = T-1;
	fdir->folha = filho->folha;
	if(nodo == filho){ // É raiz
    	TpNodo *raiz = inicializaNodo(nodo->chaves + T - 1, 1, T);
    	raiz->filhos[0] = nodo;
    	raiz->filhos[1] = fdir;
    	raiz->folha = false;
    	return raiz;
	}else{
    	for(int i = nodo->numChaves; i > pos; i--){
    		nodo->chaves[i] = nodo->chaves[i-1];
    		nodo->filhos[i + 1] = nodo->filhos[i];
    	}
    	nodo->numChaves++;
    	nodo->chaves[pos] = filho->chaves[T-1];
    	nodo->filhos[pos+1] = fdir;
    	nodo->folha = false;
    	return nodo;
	}
}

int* buscaPosicao(TpNodo *nodo, int N, int *indice, int T){
	int i;
	for(i = 0; i < nodo->numChaves; i++){
		if(nodo->chaves[i] > N) break;
		else if(nodo->chaves[i] == N) return NULL;
	}
  	if(nodo->folha){
		*indice = i;
		nodo->numChaves++;
		return nodo->chaves;
  	}
  	TpNodo *filho = nodo->filhos[i];
  	if(filho->numChaves == 2 * T - 1)
		filho = divideNodo(nodo, filho, i, T);
	return buscaPosicao(filho, N, indice, T);
}

bool insereElemento(TpArvore *arvore, int N, int T){
  	if(arvore->raiz){
		if(arvore->raiz->numChaves == 2*T - 1) // Caso raiz esteja cheia, fazemos split
			arvore->raiz = divideNodo(arvore->raiz, arvore->raiz, 0, T);
		int indice, *posicao = buscaPosicao(arvore->raiz, N, &indice, T); // Procura posicao para inserir o elemento
		if(!posicao) return false;
		for(int i = 2*T-1; i >= indice ; i--)
			posicao[i+1] = posicao[i];
		posicao[indice] = N;
		return true;
	}
	arvore->raiz = inicializaNodo(&N, 1, T);
	return true;
}
