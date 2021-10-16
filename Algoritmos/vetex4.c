#include <stdio.h>

int main(){
  int n, i, j, ans, maior, ind;

  scanf("%d", &n);
  int v[n];

  for (i = 0; i < n; i++)
    scanf("%d", &v[i]);
  for (i = 0, ans = 0, ind = 0; i < n; i++){
    for (j = i, maior = 0; j < n; j++)
      maior += v[j];
    if (maior > ans){
      ind = i;
      ans = maior;
    }
  }
  for (i = n - 1; i >= ind; i--){
    for (j = ind, maior = 0; j <= i; j++)
      maior += v[j];
    if (maior > ans)
      ans = maior;
  }

  printf("%d\n", ans);

  return 0;
}
