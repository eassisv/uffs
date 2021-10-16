#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct pilha{
	int top;
	char letra[MAX];
}Pilha;

Pilha* criaPilha(){
	Pilha *p;
	p = (Pilha*) malloc(sizeof(Pilha));
	p->top = 0;
	return p;
}

void pPush(Pilha *p, char c){
	p->letra[p->top] = c;
	p->top++;
}

char pPop(Pilha *p){
	char c;
	p->top--;
	c = p->letra[p->top];
	p->letra[p->top] = 0;
	return c;
}

int pEmpty(Pilha *p){
	return (p->top == 0);
}

int pFull(Pilha *p){
	return (p->top == MAX);
}

int main(void){
	char c;
	Pilha *p;
	
	p = criaPilha();
	while(1){
		scanf("%c", &c);
		if(c == ' ' || c == '\n'){
			if(c == '\n'){
				while(!pEmpty(p)){
				c = pPop(p);
				printf("%c", c);
				}
				printf("\n");
				free(p);
				return 0;
			}
			while(!pEmpty(p)){
				c = pPop(p);
				printf("%c", c);
			}
			printf(" ");
		}
		else{
			if(!pFull(p))	pPush(p, c);
		}
	}	
	return 0;
}
