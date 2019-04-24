#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 112
#define INF 112345678
#define f first
#define s second

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

int edges[MAX][MAX], p[MAX], r[MAX];

void make(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i; r[i] = 0;
    }
}

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

int _union(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return 0;
    if (r[u] > r[v]) p[v] = u;
    else {
        p[u] = v;
        r[u] += r[v] == r[u];
    }
    return 1;
}

int kruskal(vector<iii> &schools, vector<int> &tree,
             int n, int ignore) {
    int u, v, ans = 0, count = 0;
    make(n);
    for (int i = 0; i < (int)schools.size(); i++) {
        if (i == ignore) continue;
        u = schools[i].s.f; v = schools[i].s.s;
        if (_union(u, v)) {
            ans += schools[i].f;
            count++;
            if (ignore == -1) tree.push_back(i);
        }
    }
    return count == (n - 1) ? ans: INF; 
}

int main(void) {
    int t, n, m, a, b, c, ans;
    scanf("%d", &t);
    while (t--) {
        vector<iii> schools;
        memset(edges, 0, sizeof(edges));
        scanf("%d %d", &n, &m);
        make(n);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &c);
            schools.push_back(iii(c, ii(a, b)));
        }
        vector<int> min_tree;
        sort(schools.begin(), schools.end());
        ans = kruskal(schools, min_tree, n, -1);
        printf("%d ", ans);
        ans = INF;
        for (int i = 0; i < n - 1; i++) {
            ans = min(ans,
                    kruskal(schools, min_tree, n, min_tree[i]));
            
        }
        printf("%d\n", ans);
    }
    return 0;
}
