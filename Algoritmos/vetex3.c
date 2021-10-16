#include <stdio.h>
#include <string.h>

int main(){
  int n, i, j;
  scanf("%d", &n);

  int v[n], v2[n], r[n*2];
  memset(r, 0, sizeof(r));

  for (i = 0; i < n; i++)
    scanf("%d", &v[i]);
  for (i = 0; i < n; i++)
    scanf("%d", &v2[i]);
  for (i = n - 1, j = 0; i >= 0; i--)
    if(v[i] + v2[i] + r[j] > 9){
      r[j++] += (v[i]+v2[i]) % 10;
      r[j] += (v[i]+v2[i])/10;
    }else
      r[j++] += v[i]+v2[i];
  for (; j >= 0 ; j--)
    printf("%d", r[j]);
  printf("\n");

  return 0;
}
