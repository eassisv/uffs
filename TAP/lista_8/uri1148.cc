#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 512
#define INF 112345678

int n, e, k;
int dist[MAX][MAX];

void floyd_warshall() {
  int u, v, w;
  for (w = 1; w <= n; w++)
    for (u = 1; u <= n; u++)
      for (v = 1; v <= n; v++)
        dist[u][v] = min(dist[u][v], dist[u][w] + dist[w][v]);
}

int main(void) {
  int u, v, w;
  while (scanf("%d %d", &n, &e), n || e) {
    for (u = 1; u <= n; u++)
      for (v = 1; v <= n; v++)
        dist[u][v] = INF;
    for (int i = 0; i < e; i++) { 
      scanf("%d %d %d", &u, &v, &w);
      if (dist[v][u] != INF) {
        dist[v][u] = dist[u][v] = 0;
        continue;
      }
      dist[u][v] = w;
    }
    floyd_warshall();
    scanf("%d", &k);
    while (k--) {
      scanf("%d %d", &u, &v);
      if (dist[u][v] != INF) printf("%d\n", dist[u][v]);
      else printf("Nao e possivel entregar a carta\n");
    }
    putchar('\n');
  }
  return 0;
}
