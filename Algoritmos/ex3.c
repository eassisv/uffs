#include <stdio.h>
#include <string.h>

int main(){
  int max, i, comp;
  scanf("%d ", &max);
  char nome[max][100], tel[max][100], busca[100];

  for (i = 0; i < max; i++){
    scanf("%s", nome[i]);
    scanf("%s", tel[i]);
  }
  scanf(" %[' ' a-z A-Z 0-9]s", busca);
  getchar();
  for (i = 0; i < max; i++){
    comp = strcmp(busca, nome[i]);
    if(!comp)
       printf("%s -- %s\n", nome[i], tel[i]);
  }
  return 0 ;
}
