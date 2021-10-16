#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo_domino.h"

struct _domino{
  int num_dir;
  int num_esq;
  struct _domino *dir;
  struct _domino *esq;
};

//funcao para inicializar as listas
TpPeca* gera_lista(){
  return NULL;
}

//funcao para apagar todos os elementos das listas
void libera_lista(TpPeca *lista){
  TpPeca *p = lista, *aux;
  if(p){
	while(p->esq) p = p->esq;
	while(p){
	  aux = p;
	  p = p->dir;
	  free(aux);
	}
  }
}

//funcao para inserir elementos nas listas
TpPeca* insere_elemento(TpPeca *peca, int e, int d){
  TpPeca *p = peca, *novo = (TpPeca *) malloc(sizeof(TpPeca));
  novo->num_esq = e;
  novo->num_dir = d;
  novo->dir = NULL;
  if(!peca){//veriica se a lista esta vazia
    novo->esq = NULL;
    return novo;
  }
  while(p->dir)//para os demais casos
    p = p->dir;
  p->dir = novo;
  novo->esq = p;
  return peca;
}

//funcao para inserir uma peca na mesa
void insere_mesa(TpPeca **Mesa, int i, int esq, int dir){
  /*A variavel i que a funcao recebe, e utilizada para caso o usuario tenha a
    opcao de colocar a peca na direita ou na esquerda sendo que se i = 0
    ele ira colocar na direita, quando i = 1, ele vai colocar na esquerda
    sempre que possivel ou na direita quando nao e possivel colocar a peca na 
    esquerda*/
  TpPeca *p = *Mesa, *novo = (TpPeca *) malloc(sizeof(TpPeca));
  
  /* o ponteiro da mesa sempre vai apontar para o elemento do meio, que no caso
     eh o primeiro elemento a ser inserido na mesa, entao nesse primeiro for
     percorre toda a lista do lado esquerdo para achar o elemento mais distante
     do meio, que esta apotando para NULL
  */
  for(p = *Mesa; p->esq; p = p->esq);
  novo->esq = NULL;
  novo->dir = p;
  if(i && (dir == p->num_esq)){//inserir a peca no lado esquerdo da mesa
    novo->num_dir = dir;
    novo->num_esq = esq;
    p->esq = novo;
  }else
    if(i && (esq == p->num_esq)){
      novo->num_dir = esq;
      novo->num_esq = dir;
      p->esq = novo;
    }else{
      //agora o p vai andar pelo lado direito da mesa
      for(p = *Mesa; p->dir; p = p->dir);
      novo->dir = NULL;
      novo->esq = p;
      p->dir = novo;
      if(dir == p->num_dir){//insere no lado direito da mesa
	novo->num_dir = esq;
	novo->num_esq = dir;
      }
      else
	if(esq == p->num_dir){
          novo->num_dir = dir;
          novo->num_esq = esq;
	}
    }
}

//funcao para remover uma peca da lista dos jogadores e inserir na mesa atraves
//das variaveis passadas por parametro na propria funcao
void remove_peca(TpPeca **lista, int x, int *esq, int *dir){
  TpPeca *p = *lista, *aux;
  int i;
  for(i = 1; i < x; i++, p = p->dir); //Atualize o valor de p
  aux = (p->dir)? p->dir: p; //Caso p seja o ultimo elemento
  aux->esq = p->esq;
  aux = (p->esq)? p->esq: p; //Caso p seja o primeiro elemento
  aux->dir = p->dir;
  *esq = p->num_esq;
  *dir = p->num_dir;
  if(!p->esq)
    *lista = p->dir;
  free(p);
}

//funcao para imprimir uma lista
void imprime_lista(TpPeca *peca){
  TpPeca *p = peca;
  while(p->esq) p = p->esq;
  while(p){
    printf("|%d-%d| ", p->num_esq, p->num_dir);
    p = p->dir;
  }
  printf("\n");
}

//funcao para gerar as pecas do jogo
TpPeca* gera_pecas(){
  TpPeca *p = gera_lista();
  int i, j;
  for(i = 0; i <= 6; i++)
    for(j = i; j <= 6; j++)
      p = insere_elemento(p, i, j);
  return p;
}

//funcao para contar a quantidade pecas em uma lista
int conta_pecas(TpPeca *lista){
  TpPeca *p;
  int num;
  for(num = 0, p = lista; p; p = p->dir, num++);
  return num;
}

//funcao para pescar, ela é realizada atomaticamente na main
//o jogador vai pescar ate que tenha uma peca que possa ser jogada na mesa
TpPeca* pesca_peca(TpPeca **pesca, TpPeca *Jog){
  int esq, dir, num;
  srand((long long int)clock());
  num = conta_pecas(*pesca);
  remove_peca(pesca, rand()% num + 1, &esq, &dir);
  Jog = insere_elemento(Jog, esq, dir);
  return Jog;
}

//funcao para percorrer uma lista e retorna um inteiro com a posicao da peca
int percorre_lista(TpPeca *lista, int esq, int dir){
  TpPeca *p;
  int i;
  for(i = 1, p = lista; p; p = p->dir, i++)
    if((p->num_esq == esq) && (p->num_dir == dir))
      return i;
  return 0;
}

//funcao para buscar uma peca
void busca_peca(TpPeca *lista, int i, int *esq, int *dir){
  TpPeca *p;
  for(p = lista; i > 1; i--, p = p->dir);
  *esq = p->num_esq;
  *dir = p->num_dir;
}

/*funcao para inicializar o jogo, coloca automaticamente a peca da mao de um
  dos jogadores na mesa e passa a vez para o outro jogador*/
int inicio_jogo(TpPeca **J1, TpPeca **JM, TpPeca **Mesa){
  TpPeca *pj1 = *J1, *pjm = *JM;
  int bucha = -1, soma_di = 0, di_esq = -1, resp;
  int jog = 0; /* jog = 0 indica que o J1 esta com a peça de inicio e
                  jog = 1 indica que o JM esta com a peça de inicio */
  int esq, dir; //Recebe os valores da peca que vai para mesa
  
  /*primeiro verifica a maior peca de numeros iguais na maos dos jogadores
    para colocar na mesa, caso nao encontrar coloca a peca com os valores mais
    altos*/
  while(pj1){
    if(pj1->num_esq == pj1->num_dir){
      if(pj1->num_esq > bucha){
        bucha = pj1->num_esq;
      }
    }
    else
      if((pj1->num_esq + pj1->num_dir) > soma_di){
        soma_di = pj1->num_esq + pj1->num_dir;
        di_esq = pj1->num_esq;
      }
    pj1 = pj1->dir;
  }
  while(pjm){
    if(pjm->num_esq == pjm->num_dir){
      if(pjm->num_esq > bucha){
        bucha = pjm->num_esq;
        jog = 1;
      }
    }
    else
      if((pjm->num_esq + pjm->num_dir) > soma_di){
        soma_di = pjm->num_esq + pjm->num_dir;
        di_esq = pjm->num_esq;
        if(bucha == -1)
          jog = 1;
      }
    pjm = pjm->dir;
  }
  if(jog){
    resp = (bucha != -1) ? percorre_lista(*JM, bucha, bucha): percorre_lista(*JM, di_esq, soma_di - di_esq);
    remove_peca(JM, resp, &esq, &dir);
  }
  else{
    resp = (bucha != -1) ? percorre_lista(*J1, bucha, bucha): percorre_lista(*J1, di_esq, soma_di - di_esq);
    remove_peca(J1, resp, &esq, &dir);
  }
  *Mesa = insere_elemento(*Mesa, esq, dir);
  return (!jog);//retorna a vez do proximo jogador
}

//funcao para verificar se o jogador tem uma peca 'x'
int tem_peca(TpPeca *lista, int esq, int dir){
  TpPeca *p;
  for(p = lista; p; p = p->dir)
    if((esq == p->num_esq || esq == p->num_dir) || (dir == p->num_esq || dir == p->num_dir))
      return 1;
  return 0;
}

//funcao que faz as jogadas da maquina
int jogada_maquina(TpPeca *JM, int esq_mesa, int dir_mesa, int *esq, int *dir){
  TpPeca *p;
  int i = 1;
  for(p = JM; p; p = p->dir, i++)
    if((esq_mesa == p->num_esq || esq_mesa == p->num_dir) || (dir_mesa == p->num_esq || dir_mesa == p->num_dir)){
      *esq = p->num_esq;
      *dir = p->num_dir;
      break;
    }
  return i;
}

//funcao para contar os pontos na mao dos jogadores
int conta_pontos(TpPeca *lista){
  TpPeca *p;
  int num;
  for(num = 0, p = lista; p; p = p->dir){
    num += p->num_esq;
    num += p->num_dir;
  }
  return num;
}

//funcao para atualizar os valores das pecas que estao nas pontas
void atualiza_mesa(TpPeca *Mesa, int *esq_mesa, int *dir_mesa){
  TpPeca *p = Mesa;
  for(; p->dir; p = p->dir);
  *dir_mesa = p->num_dir;
  for(p = Mesa; p->esq; p = p->esq);
  *esq_mesa = p->num_esq; 
}

//funcao para imprimir a matriz que representa a mesa
void imprime_mesa(char m[][171]){
  int i, j;
  for(i = 0; i <= MAX_INF; i++){
    for(j = 0; j <= MAX_DIR; j++)
      printf("%c", m[i][j]);
    printf("\n");
  }
}

//funcao para padronizar cada tipo de peca no jogo em ascii art
void desenha_peca(char m[][171], int l, int c, int tipo, int num){
  //tipo = 1, parte de cima da bucha
  //tipo = 2, parte de baixo da bucha
  //tipo = 3, peca deitada da esquerda
  //tipo = 4, peca deitada da direita
  int i = l, j = c;
  if(tipo == 1 || tipo == 2){
    
    for(i = l-1; i <= l+1; i++){
      m[i][j+3] = '|';
      m[i][j-3] = '|';
    }
    if(tipo == 1){
      m[l-2][c-3] = ' ';
      m[l-2][c-3] = ' ';
      for(j = c-2, i = l-2; j <= c+2; j++)
	m[i][j] = '_';
    }
    else{
      m[l-2][c-3] = '|';
      m[l-2][c+3] = '|';
      for(i = l-2, j = c-2; j <= c+2; j++)
	m[i][j] = '-';
      for(i = l+1, j = c-1; j <= c+1; j++)
	m[i][j] = '_';
    }
    switch(num){
    case 1:
      m[l][c] = 'o';
      if(tipo == 2){
	m[l+1][c-2] = '_';
	m[l+1][c+2] = '_';
      }
      break;
    case 2:
      if(tipo == 2)
	m[l+1][c-2] = '_';
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      break;
    case 3:
      if(tipo == 2)
	m[l+1][c-2] = '_';
      m[l][c] = 'o';
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      break;
    case 4:
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      break;
    case 5:
      m[l][c] = 'o';
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      break;
    case 6:
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      m[l][c+2] = 'o';
      m[l][c-2] = 'o';
      break;
    default:
      if(tipo == 2){
	m[l+1][c-2] = '_';
	m[l+1][c+2] = '_';
      }
      break;
    }
    
  }
  if(tipo == 3 || tipo == 4){
    for(i = l-2, j = c-2; j <= c+2; j++)
      m[i][j] = '_';
    for(i = l-1, j = c-3; i <= l+1; i++)
      m[i][j] = '|';
    m[l-2][c-3] = ' ';
    m[l+2][c-3] = ' ';
    if(tipo == 4){
      for(i = l-1, j = c+3; i <= l+1; i++)
	m[i][j] = '|';
      m[l-2][c+3] = ' ';
      m[l+2][c+3] = ' ';
    }
    switch(num){
    case 1:
      m[l][c] = 'o';
      for(i = l+1, j = c-2; j <= c+2; j++)
	m[i][j] = '_';
      break;
    case 2:
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      for(i = l+1, j = c-2; j <= c+1	; j++)
	m[i][j] = '_';		
      break;
    case 3: 
      m[l][c] = 'o';
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      for(i = l+1, j = c-2; j <= c+1; j++)
	m[i][j] = '_';	
      break;
    case 4:
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      for(i = l+1, j = c-1; j <= c+1; j++)
	m[i][j] = '_';
      break;
    case 5:
      m[l][c] = 'o';
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      for(i = l+1, j = c-1; j <= c+1; j++)
	m[i][j] = '_';
      break;
    case 6:
      m[l-1][c-2] = 'o';
      m[l+1][c+2] = 'o';
      m[l-1][c+2] = 'o';
      m[l+1][c-2] = 'o';
      m[l+1][c] = 'o';
      m[l-1][c] = 'o';
      m[l+1][c+1] = '_';
      m[l+1][c-1] = '_';
      break;
    default:
      for(i = l+1, j = c-2; j <= c+2; j++)
	m[i][j] = '_';
      break;
    }
  }
}

//funcao para inserir o desenho de uma peca na matriz da mesa
void insere_matriz(char m[][171], TpPeca *Mesa){
  TpPeca *p = Mesa;
  int cdir = 85, cesq = 85, ldir = 17, lesq = ldir, primdir = 0, primesq = 0;;
  //a variavel primdir e primesq verifica se a peca e a primeira peca depois que a mesa quedra de linha
  //assim como o ponteiro da mesa, para imprimir tbm começa do meio para os lados
if(p)
	if(p->num_dir != p->num_esq){
		cdir -= 3;
		cesq += 3;
	}  
  while(p){
    if((p->num_dir == p->num_esq) && ldir == 17){
      if(cdir + 25 < MAX_DIR){
				desenha_peca(m, ldir-2, cdir, 1, p->num_esq);
				desenha_peca(m, ldir+2, cdir, 2, p->num_dir);
				cdir += 7;
			}else{
				desenha_peca(m, ldir, cdir, 1, p->num_esq);
				desenha_peca(m, ldir+4, cdir, 2, p->num_dir);
				ldir += 8;
			}
			p = p->dir;
			continue;
    }
    if((p->num_dir != p->num_esq) && ldir == 17){
			if(cdir + 14 < MAX_DIR){
				desenha_peca(m, ldir, cdir, 3, p->num_esq);
				cdir += 6;
				desenha_peca(m, ldir, cdir, 4, p->num_dir);
				cdir += 7;
			}else{
				desenha_peca(m, ldir, cdir, 1, p->num_esq);
				desenha_peca(m, ldir+4, cdir, 2, p->num_dir);
				ldir += 8;
			}
      p = p->dir;
      continue;
    }
    if((p->num_dir == p->num_esq) && ldir == 25){
			desenha_peca(m, ldir, cdir, 1, p->num_esq);
			desenha_peca(m, ldir+4, cdir, 2, p->num_dir);
			cdir -= 7;
			ldir += 2;
			p = p->dir;
			continue;
		}
		if((p->num_dir != p->num_esq) && ldir == 25){
			desenha_peca(m, ldir, cdir, 1, p->num_esq);
			desenha_peca(m, ldir+4, cdir, 2, p->num_dir);
			cdir -= 7;
			ldir += 4;
			p = p->dir;
			primdir = 1;
			continue;
		}
		if((p->num_dir == p->num_esq) && primdir){
			desenha_peca(m, ldir, cdir, 4, p->num_esq);
			cdir -= 6;
			desenha_peca(m, ldir, cdir, 3, p->num_dir);
			cdir -= 7;
			p = p->dir;
			primdir = 0;
			continue;
		}
		if((p->num_dir == p->num_esq)){
			desenha_peca(m, ldir-2, cdir, 1, p->num_esq);
			desenha_peca(m, ldir+2, cdir, 2, p->num_dir);
			cdir -= 7;
			p = p->dir;
			continue;
		}
		if((p->num_dir != p->num_esq)){
			desenha_peca(m, ldir, cdir, 4, p->num_esq);
			cdir -= 6;
			desenha_peca(m, ldir, cdir, 3, p->num_dir);
			cdir -= 7;
			p = p->dir;
			primdir = 0;
			continue;
		}
  }
  p = Mesa;
  while(p){
    if((p->num_dir == p->num_esq) && (lesq == 17)){
      if(cesq - 24 > 0){
				desenha_peca(m, lesq-2, cesq, 1, p->num_dir);
				desenha_peca(m, lesq+2, cesq, 2, p->num_esq);
				cesq -= 7;
			}else{
				desenha_peca(m, lesq, cesq, 2, p->num_dir);
				desenha_peca(m, lesq-4, cesq, 1, p->num_esq);
				lesq -= 8;
			}
      p = p->esq;
      continue;
    }
    if((p->num_dir != p->num_esq) && (lesq == 17)){
	    if(cesq - 14 > 0){
	      desenha_peca(m, lesq, cesq, 4, p->num_dir);
	      cesq -= 6;
	      desenha_peca(m, lesq, cesq, 3, p->num_esq);
	      cesq -= 7;
	    }else{
			desenha_peca(m, lesq, cesq, 2, p->num_dir);
			desenha_peca(m, lesq-4, cesq, 1, p->num_esq);
			lesq -= 8;
		}  
	    p = p->esq;
      continue;
    }
    if((p->num_dir == p->num_esq) && lesq == 9){
		desenha_peca(m, lesq, cesq, 2, p->num_dir);
		desenha_peca(m, lesq-4, cesq, 1, p->num_esq);
		cesq += 7;
		lesq -= 2;
		p = p->esq;
		continue;
	}
	if((p->num_dir != p->num_esq) && lesq == 9){
		desenha_peca(m, lesq, cesq, 2, p->num_dir);
		desenha_peca(m, lesq-4, cesq, 1, p->num_esq);
		cesq += 7;
		lesq -= 4;
		p = p->esq;
		primesq = 1;
		continue;
	}
	if((p->num_dir == p->num_esq) && primesq){
		desenha_peca(m, lesq, cesq, 3, p->num_esq);
		cesq += 6;
		desenha_peca(m, lesq, cesq, 4, p->num_dir);
		cesq += 7;
		p = p->esq;
		primesq = 0;
		continue;
	}
	if((p->num_dir == p->num_esq)){
		desenha_peca(m, lesq-2, cesq, 1, p->num_esq);
		desenha_peca(m, lesq+2, cesq, 2, p->num_dir);
		cesq += 7;
		p = p->esq;
		continue;
	}
	if((p->num_dir != p->num_esq)){
		desenha_peca(m, lesq, cesq, 3, p->num_dir);
		cesq += 6;
		desenha_peca(m, lesq, cesq, 4, p->num_esq);
		cesq += 7;
		p = p->esq;
		primesq = 0;
		continue;
	}
  }
}

//funcao para imprimir os caracters ao redor da mesa
void gera_mesa(char m[][171]){
  int i, j;
  for(i = 0; i <= MAX_DIR; i++){
    m[0][i] = '-';
    m[MAX_INF][i] = '-';
  }
  for(i = 1; i < MAX_INF; i++){
    m[i][0] = '|';
    m[i][MAX_DIR] = '|';
  }
  for(i = 1; i < MAX_INF; i++)
    for(j = 1; j < MAX_DIR; j++)
      m[i][j] = ' ';
}
