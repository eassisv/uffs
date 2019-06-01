#include <cstdio>
#include <cstring>

#define MAX 112
typedef long long ll;

ll M = 1e9 + 7;
ll memo[MAX * MAX];
int grid[MAX][MAX];

ll fact(ll n) {
  if (n < 2) return 1;
  if (memo[n] != -1) return memo[n];
  return memo[n] = fact(n - 1) * n % M;
}

ll expbin(ll a, ll x) {
  ll t;
  if (!x) return 1L;
  if (x & 1L) return a * expbin(a, x - 1) % M;
  t = expbin(a, x >> 1);
  return t * t % M;
}

int main(void) {
  int n, m, xa, xb, ya, yb;
  ll p, q, tt, bb;
  char c;
  scanf("%d %d", &n, &m);
  memset(grid, 0, sizeof(grid));
  memset(memo, -1, sizeof(memo));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      scanf(" %c", &c);
      grid[i][j] = (c == '#');
      if (j) grid[i][j] += grid[i][j - 1];
    }
  while (scanf("%d %d %d %d", &xa, &ya, &xb, &yb) != EOF) {
    bb = 0; tt = (xb - xa + 1) * (yb - ya + 1);
    for (int i = xa; i <= xb; i++) bb += (grid[i][yb] - grid[i][ya - 1]);
    p = fact(tt);
    q = fact(tt - bb) * fact(bb) % M;
    printf("%lld\n", (p * expbin(q, M - 2) + M - 1) % M);
  }
  return 0;
}
