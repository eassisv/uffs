#include <cstdio>
#include <cstring>

#define MAX 11234

int ns[MAX][31];
int sums[31];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main(void) {
  int n, m, d;
  while (scanf("%d %d", &n, &m), n) {
    memset(sums, 0, sizeof(sums));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &ns[i][j]);
        sums[j] += ns[i][j];
      }
    } 
    while (!sums[--m]); 
    for (int i = 0; i < n; i++) {
      d = gcd(ns[i][m], sums[m]);
      printf("%d / %d\n", ns[i][m] / d, sums[m] / d);
    }
  }
  return 0;
}
