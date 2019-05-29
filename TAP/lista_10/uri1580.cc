#include <cstdio>
#include <cstring>

#define MAX 1123
#define MAXC 112

typedef long long ll;

const ll M = (ll)(10e9 + 7);
ll memo[MAX];
int count[MAXC];

ll fib(int n) {
  if (n < 2) return 1;
  if (memo[n] != -1) return memo[n];
  return memo[n] = n * memo[n - 1];
}

int main(void) {
  char c;
  ll n, b;
  int len = 0;
  memset(memo, -1, sizeof(memo));
  while (scanf("%c", &c) != EOF) {
    if (c != '\n') {
      len++; count[c - 'A']++;
      continue;
    }
    n = fib(len);
    for (int i = 0; i < MAXC; i++) 
      b *= fib(count[i]);
    printf("%lld\n", n / b);
  }
  return 0;
}
