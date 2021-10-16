#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo_domino.c"

int main(void){
  TpPeca *J1, *JM, *Mesa, *Pesca;
  int i, prox, op; 
  /*Variavel prox indica quem e o proximo jogador
    prox = 0 indica que e a vez do J1
    prox = 1 indica que e a vez do JM*/
  int esq_mesa, dir_mesa, esq, dir; 
  /*Variavel esq_mesa e dir_mesa, guardam os valores da mesa
    Variaveis esq e dir guardam os valores da peça que o jogador quer colocar na mesa*/
  int fim_de_jogo = 0;
  char matriz[36][171];
  //criar a matriz, limpar todas as posicoes e atualizar com a lista da mesa
  memset(matriz, 0, sizeof(matriz));  
  gera_mesa(matriz);
  insere_matriz(matriz, Mesa);
  //criar as listas que serao usadas durante o jogo
  J1 = gera_lista();//jogador humano
  JM = gera_lista();//jogador maquina
  Mesa = gera_lista();//mesa
  Pesca = gera_lista();//pesca
  Pesca = gera_pecas();
  for(i = 0; i < 6; i++){//distribuicao das pecas aos jogadores
    J1 = pesca_peca(&Pesca, J1);
    JM = pesca_peca(&Pesca, JM);
  }
  //inicio do jogo
  prox = inicio_jogo(&J1, &JM, &Mesa);
	atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
  printf("\n\n\n\n\n\n\n\n\n\n\n\n");//esta parte serve apenas para limpar a tela anterior do terminal
  while(1){
    insere_matriz(matriz, Mesa);
    imprime_mesa(matriz);
    if(fim_de_jogo){//quando a variavel fim de jogo for verdadira 
      libera_lista(J1);//libera as listas
      libera_lista(JM);
      libera_lista(Mesa);
      libera_lista(Pesca);
      printf("Deseja jogar novamente? Digite 1 para \"SIM\" e 0 para \"NAO\"\n");
      if(!scanf("%d", &i))//pergunta se o usuario quer jogar novamente
        return 0;
      if(!i) //reinicia o jogo caso o usuario digitou para jogar novamente
        return 0;
      memset(matriz, 0, sizeof(matriz));  
      gera_mesa(matriz);
      J1 = gera_lista();
      JM = gera_lista();
      Mesa = gera_lista();
      Pesca = gera_lista();
      Pesca = gera_pecas();
      for(i = 0; i < 6; i++){
        J1 = pesca_peca(&Pesca, J1);
        JM = pesca_peca(&Pesca, JM);
      }
      prox = inicio_jogo(&J1, &JM, &Mesa);
      atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
      fim_de_jogo = 0;
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      continue;
		}
    if(!prox){//pesca atomatica para o J1 quando nao tiver peca para jogar
			atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
      while(!tem_peca(J1, esq_mesa, dir_mesa) && conta_pecas(Pesca))
        J1 = pesca_peca(&Pesca, J1);
      if(tem_peca(J1, esq_mesa, dir_mesa)){
        printf("A Maquina possui %d e a Pesca possui %d peças.\n", conta_pecas(JM), conta_pecas(Pesca));
        printf("Sua Vez\n");
        imprime_lista(J1);
        for(i = 1; i <= conta_pecas(J1); i++)	
          printf("  %d%s", i,(i < 10)? "   ": "  ");//imprimir as posicoes das pecas do J1
        printf("Opcoes das peças\n");
        if(!scanf("%d", &i))
          return 0;
        while(i > conta_pecas(J1) || i < 1){
					printf("Peca invalida, digite um numero menor ou igual a %d: ", conta_pecas(J1));
					if(!scanf("%d", &i))
						return 0;
        }	
        busca_peca(J1, i, &esq, &dir);
        while((((esq != esq_mesa) && (esq != dir_mesa)) && ((dir != esq_mesa) && (dir != dir_mesa))) || ((i > conta_pecas(J1) || (i < 1)))){
          printf("Peca invalida, digite um numero menor ou igual a %d: ", conta_pecas(J1));
          if(!scanf("%d", &i))
            return 0;
					if((i >= 1) || (i <= conta_pecas(J1)))	
						busca_peca(J1, i, &esq, &dir);
        }
        op = 1;//caso a peca possa ser colocada em ambos os lados
        if((esq == esq_mesa && dir == dir_mesa) || (esq == dir_mesa && dir == esq_mesa)){
          printf("Digite 1 para colocar a peca na esquerda ou 0 na direita: ");
          if(!scanf("%d", &op))
            return 0;
        }
        if((esq == esq_mesa && esq == dir_mesa) || (dir == dir_mesa && dir == esq_mesa)){
          printf("Digite 1 para colocar a peca na esquerda ou 0 na direita: ");
          if(!scanf("%d", &op))
            return 0;
        }
        //atualiza a mesa apos o jogador escolher a peca
        atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
        remove_peca(&J1, i, &esq, &dir);
        insere_mesa(&Mesa, op, esq, dir);
        atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
      }
      if(!conta_pecas(J1)){//se o J1 nao tiver mais pecas na mao ele venceu
        fim_de_jogo = 1;
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Parabens voce venceu!!!\n");
        continue;
      }
      prox = 1;
    }else{//jogadas da maquina
			atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
      while(!tem_peca(JM, esq_mesa, dir_mesa) && conta_pecas(Pesca))
				JM = pesca_peca(&Pesca, JM);
      if(tem_peca(JM, esq_mesa, dir_mesa)){
        atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
        i = jogada_maquina(JM, esq_mesa, dir_mesa, &esq, &dir);
        remove_peca(&JM, i, &esq, &dir);
        insere_mesa(&Mesa, 1, esq, dir);
        atualiza_mesa(Mesa, &esq_mesa, &dir_mesa);
      }
      if(!conta_pecas(JM)){//caso a maquina nao tiver mais pecas na mao ela vence
        fim_de_jogo = 1;
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Que pena voce perdeu!!!\n");
        continue;
      }
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      prox = 0;
    }
    if(!tem_peca(J1, esq_mesa, dir_mesa) && !tem_peca(JM, esq_mesa, dir_mesa) && !conta_pecas(Pesca)){
      fim_de_jogo = 1;
      /*caso a partida resulte em um empate, sera contado o numero de pontos
        na mao dos jogadores, vence quem tiver a menor soma de pontos na mao
      */
      if(conta_pecas(J1) == conta_pecas(JM))
		printf("%s\n",(conta_pontos(J1) > conta_pontos(JM))? "Que pena voce perdeu!!!": "Parabens voce ganhou!!!");
      else
		printf("%s\n",(conta_pecas(J1) > conta_pecas(JM))? "Que pena voce perdeu!!!": "Parabens voce ganhou!!!");
    }
  }
  return 0;
}
