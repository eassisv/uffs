#include <cstdio>
#include <cstring>

#define MAX 1123
#define MAXC 112

typedef long long ll;

const ll M = (ll)(1e9 + 7);
ll memo[MAX], count[MAXC];

ll fib(ll n) {
  if (n < 2)
    return 1L;
  if (memo[n] != -1)
    return memo[n];
  return memo[n] = (n * fib(n - 1)) % M;
}

ll bbin(ll a, ll n) {
  if (!n)
    return 1L;
  if (n & 1L)
    return a * bbin(a, n - 1) % M;
  ll tmp = bbin(a, n >> 1);
  return tmp * tmp % M;
}

int main(void) {
  char c;
  ll n, b;
  int len = 0;
  memset(count, 0, sizeof(count));
  memset(memo, -1, sizeof(memo));
  while (scanf("%c", &c) != EOF && (c != '\n' || len)) {
    if (c == '\n' && len) {
      n = fib(len); b = 1; len = 0;
      for (int i = 0; i < MAXC; i++)
        b = fib(count[i]) * b % M;
      printf("%lld\n", n * bbin(b, M - 2) % M);
      memset(count, 0, sizeof(count));
      continue;
    }
    count[c - 'A']++; len++;
  }
  return 0;
}
