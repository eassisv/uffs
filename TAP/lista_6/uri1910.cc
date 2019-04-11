#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAX 100001
#define INF 112345678

int Ks[MAX], dist[MAX];

int valid(int v) { return v >= 1 && v < MAX; }

int op(int u, int i) {
    if (!i) return u / 2;
    if (i == 1) return u + 1;
    if (i == 2) return u - 1;
    if (i == 3) return u * 2;
    return u * 3;
}

int bfs(int o, int d) {
    int u, v;
    for (int i = 0; i < MAX; i++) dist[i] = INF;
    queue<int> Q; dist[o] = 0; Q.push(o);
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        if (u == d) return dist[d];
        for (int i = 0; i < 5; i++) {
            if ((u & 1) && !i) continue;
            v = op(u, i);
            if (valid(v) && dist[v] == INF && !Ks[v]) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }
    return -1;
}

int main(void) {
    int o, d, k, u;
    while (scanf("%d %d %d", &o, &d, &k) != EOF &&  (o || d || k)) {
        memset(Ks, 0, sizeof(Ks));
        for (int i = 0; i < k; i++) {
            scanf("%d", &u);
            Ks[u] = 1;
        }
        printf("%d\n", o == d ? 0 : bfs(o, d));
    }
    return 0;
}
