#include <stdio.h>

int main(){
  int n;

  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);
  int v[n], i;
  printf("\nDigite o valor de cada posicao do vetor:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &v[i]);
  printf("Os valores digitados em ordem inversa são:\n");
  for (i = n - 1; i >= 0; i--)
    printf("V[%d] = %d\n", i, v[i]);

  return 0;
}
