#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 112
#define INF 112345678
#define f first
#define s second

struct edge {
  int id, from, to, w;
  edge() {}
  edge(int _id, int _from, int _to, int _w) :
    id(_id), from(_from), to(_to), w(_w) {}
};

typedef pair<edge, int> ei;

int n, m, d;
int ws[MAX][MAX], vis[MAX], dist[MAX];
int dg[MAX], gr[2][MAX][MAX];
edge p[MAX];

int bellman_ford(vector<edge> &edges) {
  int id, u, v, w, bneck = INF;
  edge e;
  for (int i = 1; i <= n; i++) {
    dist[i] = INF;
  }
  dist[1] = 0;
  memset(p, 0, sizeof(0));
  for (int i = 1; i < n; i++)
    for (auto e: edges) {
      u = e.from;
      v = e.to;
      w = e.w;
      id = e.id;
      if (dist[u] != INF && dist[u] + w < dist[v] && gr[id][u][v]) {
        dist[v] = dist[u] + w;
        p[v] = e;
      }
    }
  if (dist[n] == INF) return 0;
  for (u = n, e = p[n]; u != 1; u = e.from, e = p[u])
    bneck = min(bneck, gr[e.id][e.from][e.to]);
  return bneck;
}

int ffek(vector<edge> &edges) {
  int u, pu, flow = 0, cost = 0, bneck = INF;
  edge e;
  while ((bneck = bellman_ford(edges))) {
    bneck = min(d - flow, bneck);
    for (u = n, e = p[n]; u != 1; e = p[u]) {
      u = e.to; pu = e.from;
      gr[e.id][pu][u] -= bneck;
      gr[e.id][u][pu] += bneck;
      cost += bneck * (e.w < 0 ? e.w + 1: e.w - 1);
      u = pu;
    }
    flow += bneck;
    if (flow >= d) return cost;
  }
  return INF;
}

int main(void) {
  int u, v, c, k, ans, inst = 1;
  while (scanf("%d %d", &n, &m) != EOF) {
    vector<edge> edges;
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d", &u, &v, &c); c++;
      edges.push_back(edge(0, u, v, c));
      edges.push_back(edge(0, v, u, -c));
      edges.push_back(edge(1, v, u, c));
      edges.push_back(edge(1, u, v, -c));
    }
    scanf("%d %d", &d, &k);
    for (auto i: edges)
      gr[i.id][i.from][i.to] = i.w < 0 ? 0 : k;
    ans = ffek(edges);
    printf("Instancia %d\n", inst); inst++;
    if (ans == INF) printf("impossivel\n\n");
    else printf("%d\n\n", ans);
  }
  return 0;
}
