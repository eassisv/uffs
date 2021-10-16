#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct _produto{
  int codigo;
  char nome[50];
  float preco;
}Produto;

void mostraMenu();
void cadastraProduto();
void listaProdutos();
void erroNoArquivo(FILE *f);
void alterarProduto();

int main(void){
  FILE *f = fopen("lista_de_produtos.txt", "r");
  if(!f){
	f = fopen("lista_de_produtos.txt", "w");
  }
  fclose(f);

  int opcao;
  do{
	mostraMenu();
	scanf("%d", &opcao);
	system("clear");
	getchar();
	switch(opcao){
	case 1:
	  cadastraProduto();
	  break;
	case 2:
	  listaProdutos();
	  break;
	case 3:
	  alterarProduto();
	  break;
	case 0:
	  return 0;
	default:
	  puts("Opcao invalida.\n");
	  break;
	}
	puts("Aperte ENTER para voltar ao menu");
	getchar();
  }while(1);

  return 0;
}

void mostraProduto(Produto p){
  printf("Codigo do produto: %06d\n", p.codigo);
  printf("Codigo do produto: %s", p.nome);
  printf("Codigo do produto: %.2f\n\n", p.preco);
}

void mostraMenu(){
  system("clear");
  puts("\t\tMenu");
  puts("1. Cadastrar produto.");
  puts("2. Listar produtos cadastrados.");
  puts("3. Alterar produto");
  puts("0. Sair.");
  printf("\nDigite a opcao: ");
}

void stringInt(char *s, int n){
  int tam = strlen(s), i, j;
  for(i = tam, j = 100000; i < tam + 6; i++, j /= 10){
	s[i] = (n / j) % 10 + '0';
  }
  s[strlen(s)] = '\0';
}


void erroNoArquivo(FILE *f){
  if(!f){
	system("clear");
	puts("Ocorreu um erro ao ler o arquivo");
	puts("Aperte ENTER para encerrar");
	getchar();
	system("clear");
	exit(0);
  }
}

void geraNomeArquivo(char *arqNome, int codigo){
  memset(arqNome, 0, strlen(arqNome));
  strcpy(arqNome, "produtos/\0");
  stringInt(arqNome, codigo);
  strcat(arqNome, ".bin");
}

void cadastraProduto(){
  Produto p;
  FILE *f;
  puts("Digite o nome do produto.");
  printf("> ");
  fgets(p.nome, 50, stdin);
  puts("Digite o preco do produto.");
  printf("> ");
  scanf("%f", &p.preco);
  getchar();
  srand((unsigned)(time(NULL)));
  char arqNome[50], arqTmp[50];
  memset(arqTmp, 0, sizeof(arqTmp));
  srand((unsigned)time(NULL));
  p.codigo = rand() % 1000000;
  geraNomeArquivo(arqNome, p.codigo);
  f = fopen("lista_de_produtos.txt", "r");
  erroNoArquivo(f);
  while(fscanf(f, "%s", arqTmp) != EOF){
	if(!strcmp(arqTmp, arqNome)){
	  p.codigo =  rand() % 1000000;
	  stringInt(arqNome, p.codigo);
	  rewind(f);
	}
  }
  f = freopen("lista_de_produtos.txt", "a+", f);
  fprintf(f, "%s\n", arqNome);
  FILE *novoArquivo = fopen(arqNome, "wb+");
  erroNoArquivo(novoArquivo);
  fwrite((void *)&p, sizeof(Produto), 1, novoArquivo);
  system("clear");
  puts("Produto cadastrado com sucesso.\n");
  mostraProduto(p);
  fclose(novoArquivo);
  fclose(f);
}

void listaProdutos(){
  FILE *f1, *f2 = fopen("lista_de_produtos.txt", "r+");
  erroNoArquivo(f2);
  Produto p;
  char arq[50];
  puts("Lista de Produtos\n");
  while(fscanf(f2, "%s", arq) != EOF){
	f1 = fopen(arq, "r");
	erroNoArquivo(f1);
	fread(&p, sizeof(Produto), 1, f1);
	mostraProduto(p);
	fclose(f1);
  }
  fclose(f2);
}

void alterarProduto(){
  int codigo;
  char arqNome[50];
  FILE *f;
  Produto p;
  listaProdutos();
  puts("Digite o codigo do produto para alteracao.");
  printf("> ");
  scanf("%d", &codigo);
  getchar();
  geraNomeArquivo(arqNome, codigo);
  f = fopen(arqNome, "r+");
  if(!f){
	puts("Este produto nao esta cadastrado, ou ocorreu um erro ao abri-lo");
	return;
  }
  system("clear");
  puts("Produto\n");
  fread(&p, sizeof(Produto), 1, f);
  mostraProduto(p);
  puts("Digite o novo nome para o produto.");
  printf("> ");
  fgets(p.nome, 50, stdin);
  puts("Digite o novo preco do produto.");
  printf("> ");
  scanf("%f", &p.preco);
  getchar();
  f = freopen(arqNome, "w+", f);
  erroNoArquivo(f);
  fwrite(&p, sizeof(Produto), 1, f);
  puts("\nProduto atualizado com sucesso.");
  puts("Novas informacoes do produto\n");
  mostraProduto(p);
  fclose(f);
}
