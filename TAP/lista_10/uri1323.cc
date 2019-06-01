#include <cstdio>
#include <cstring>

#define MAX 112
int memo[MAX];

int f(int n) {
  if (n == 1) return 1;
  if (memo[n] != -1) return memo[n];
  return n * n + f(n - 1);
}

int main(void) {
  int n;
  memset(memo, -1, sizeof(memo));
  while (scanf("%d", &n), n)
    printf("%d\n", f(n));
  return 0;
}
