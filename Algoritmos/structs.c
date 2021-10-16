#include <stdio.h>
#include <string.h>

#define NBANDAS 5

struct Banda{
	char nome[20];
	char estilo[20];
	int integrantes;
	int posicao;
};

typedef struct Banda Banda;

void exibeInfo (Banda g[], int x);
void procuraPos (Banda g[], int x);
void procuraEstilo (Banda g[], char estilo[]);
void procuraBanda (Banda g[], char banda[]);

void exibeInfo (Banda g[], int x){
	printf("Banda: %sEstilo: %s", g[x].nome, g[x].estilo);
	printf("Integrantes: %d\nPosicao: %d\n", g[x].integrantes, g[x].posicao);
}

void procuraPos (Banda g[], int x){
	int i;
	for (i = 0; i < NBANDAS; i++)
		if (g[i].posicao == x){
			printf("Banda: %sEstilo: %s", g[i].nome, g[i].estilo);
			printf("Integrantes: %d\n", g[i].integrantes);
		}
}

void procuraEstilo (Banda g[], char estilo[]){
	int i, existe = 0;
	for (i = 0; i < NBANDAS && !existe; i++)
		if (!strcmp(g[i].estilo, estilo)){
			exibeInfo(g, i);
			existe = 1;
		}
	if (!existe)
		printf("Nao existe banda desse estilo nos favoritos\n");
}

void procuraBanda (Banda g[], char banda[]){
	int i, existe = 1;
	for (i = 0; i < NBANDAS && existe; i++)
		existe = strcmp(g[i].nome, banda);
		
	if (!existe)
		printf("A banda existe nos favoritos\n");
	else 
		printf("A banda nao existe nos favoritos\n");		
}

int main (void){
	int i, x, caso;
	char s[20];
	Banda grupo[NBANDAS];

	memset (grupo, 0, sizeof(grupo));
	
	for (i = 0; i < NBANDAS; i++){
		printf ("Digite o nome da banda: ");
		fgets (grupo[i].nome, 20, stdin);
		printf ("Digite o estilo da banda: ");
		fgets (grupo[i].estilo, 20, stdin);
		printf ("Digite o numero de integrantes da banda: ");
		scanf("%d", &grupo[i].integrantes);
		printf ("Digite a posicao da banda: ");
		scanf("%d", &grupo[i].posicao);
		getchar();
	}
	for (i = 0; i < NBANDAS; i++){
		printf ("Banda: %sEstilo: %s",grupo[i].nome, grupo[i].estilo);
		printf ("N. integrantes: %d\nPosicao: %d\n", grupo[i].integrantes, grupo[i].posicao);
	}
	do {
		printf("------------------------------\n");
		printf("Digite 1 para procurar a banda por posicao\n");
		printf("Digite 2 para procurar as bandas pelo estilo\n");
		printf("Digite 3 para procurar a banda pelo nome\n");
		printf("Digite 0 para sair\n");
		scanf("%d", &caso);
		getchar();
		switch (caso){
			case 0:
				break;
			case 1:
				printf("Digite o valor da posicao de 1 a 5\n");
				scanf("%d", &x);
				getchar();
				procuraPos(grupo, x);
				break;
			case 2:
				printf("Digite o estilo para a busca\n");
				fgets(s, 20, stdin);
				procuraEstilo(grupo, s);
				break;
			case 3:
				printf("Digite o nome da banda para a busca\n");
				fgets(s, 20, stdin);
				printf("%s", s);
				procuraBanda(grupo, s);
				break;
			default:
				printf("Opcao invalida\n");
		}
	} while (caso);
				
	return 0;
}
