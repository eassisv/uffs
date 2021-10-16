#include <stdio.h>

int main(){
  int v1[10], v2[10], i, ans;
  char op[10];

  printf("**Digite dois numeros inteiros e em seguida a operacao**\n");
  for (i = 0; i < 10; i++){
    scanf("%d %d %c ", &v1[i], &v2[i], &op[i]);
  }
  for (i = 0; i < 10; i++){
    switch(op[i]){
    case '+': ans = v1[i] + v2[i]; break;
    case '-': ans = v1[i] - v2[i]; break;
    case '*': ans = v1[i] * v2[i]; break;
    case '/': ans = v1[i] / v2[i]; break;
    }
    printf("%d %c %d = %d\n",v1[i], op[i], v2[i], ans);
  }

  return 0;
}
