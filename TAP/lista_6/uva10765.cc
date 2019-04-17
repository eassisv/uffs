#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

#define MAX 11234
#define pb push_back

struct pg_val {
    int i, v;
    pg_val() {}
    pg_val(int _i, int _v) : i(_i), v(_v) {}
    bool operator < (const pg_val other) const {
        if (other.v != v) return v > other.v;
        return i < other.i;
    }
};

int seen[MAX], low[MAX], childs[MAX], ap[MAX];

void dfs(int u, int t, vector< vector<int> > &adj, vector<pg_val> &ans) {
    seen[u] = low[u] = t;
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        if (!seen[v]) {
            childs[u]++;
            dfs(v, t + 1, adj, ans);
            low[u] = min(low[u], low[v]);
            if (low[v] >= seen[u]) ap[u]++;
        } else if (seen[v] != seen[u] - 1){
            low[u] = min(low[u], seen[v]);
        }
    }
    if (seen[u] == 1) ap[u] = childs[u];
    else ap[u]++;
    ans.pb(pg_val(u, ap[u]));
}

int main(void) {
    int n, m, x, y;
    while (scanf("%d %d", &n, &m), n || m) {
        vector< vector<int> > adj(MAX);
        while (scanf("%d %d", &x, &y), x != -1 && y != -1) {
            adj[x].pb(y); adj[y].pb(x);
        }
        vector<pg_val> ans;
        memset(seen, 0, sizeof(seen));
        memset(ap, 0, sizeof(ap));
        memset(childs, 0, sizeof(childs));
        for (int i = 0; i < n; i++)
            if (!seen[i]) dfs(0, 1, adj, ans);
        sort(ans.begin(), ans.end());
        for (int i = 0; i < m; i++) printf("%d %d\n", ans[i].i, ans[i].v);
        printf("\n");
    }
}
