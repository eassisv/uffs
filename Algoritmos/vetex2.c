#include <stdio.h>

int main(){
  int i, j, v[10], aux;

  printf("Digite os valores para serem ordenados:\n");
  for (i = 0; i < 10; i++)
    scanf("%d", &v[i]);
  for (i = 9; i >= 1; i--)
    for (j = 0; j < i; j++)
      if(v[j] > v[j+1]){
        aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
        }
  for (i = 0; i < 10; i++)
    printf("%d ", v[i]);
  printf("\n");
  return 0;
}
