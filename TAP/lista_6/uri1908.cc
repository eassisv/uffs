#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 11234
#define MAXK 1123

vector< vector<int> > ls(MAXN);
vector< vector<int> > cs(MAXK);
int dist[MAXN];

int bfs(int s, int d) {
    int u, v;
    memset(dist, -1, sizeof(dist));
    queue<int> Q;    
    dist[s] = 0;
    Q.push(s);
    while (!Q.empty()) {
        u = Q.front(); Q.pop();
        if (u == d) break;
        for (int i = 0; i < (int)ls[u].size(); i++)
            for (int j = 0; j < (int)cs[ls[u][i]].size(); j++) {
                v = cs[ls[u][i]][j];
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    Q.push(v);
                }
            }
    }
    return dist[d];
}

int main(void) {
    int n, k, l, c;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &l);
        for (int j = 0; j < l; j++) {
            scanf("%d", &c);
            ls[c].push_back(i);
            cs[i].push_back(c);
        }
    }
    printf("%d\n", bfs(1, n));
    return 0;
}
