#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

#define MAX 512
#define INF 112345678
#define INT(x) (x == '#' ? INF : x == '.' || x == 'E' ? 0 : x - '0')
#define f first
#define s second
#define valid(x) (x.f >= 0 && x.s >= 0 && x.f < n && x.s < m)
#define dist(x) dist[x.f][x.s]
#define seen(x) seen[x.f][x.s]
#define maze(x) maze[x.f][x.s]

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
  
int n, m;
ii s, t;
char maze[MAX][MAX];
int dist[MAX][MAX], seen[MAX][MAX];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int dijkstra() {
  ii u, v;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      dist[i][j] = INF;
  memset(seen, 0, sizeof(seen));
  priority_queue< iii, vector<iii>, greater<iii> > pq;
  pq.push(iii(dist(s) = 0, s));
  while (!pq.empty()) {
    u = pq.top().second; pq.pop();
    if (u == t) return dist(u);
    if (seen(u)) continue;
    seen(u) = 1;
    for (int i = 0; i < 4; i++) {
      v = ii(u.f + dx[i], u.s + dy[i]);
      if (!valid(v)) continue;
      if (dist(v) > dist(u) + INT(maze(v))) {
        dist(v) = dist(u) + INT(maze(v));
        pq.push(iii(dist(v), v));
      }
    }
  }
  return INF;
}

int main(void) {
  scanf("%d %d", &n, &m);
  for (int u = 0; u < n; u++)
    for (int v = 0; v < m; v++) {
      char c;
      scanf(" %c", &c);
      if (c == 'H') s = ii(u, v);
      if (c == 'E') t = ii(u, v);
      maze[u][v] = c;
    }
  int ans = dijkstra();
  if (ans != INF) printf("%d\n", ans);
  else printf("ARTSKJID\n");
  return 0;
}
