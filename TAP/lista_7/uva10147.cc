#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX 751
#define pow2(x) ((x) * (x))
#define dist(x, y) (sqrt(pow2((double)x.first - (double)y.first) +\
            pow2((double)x.second - (double)y.second)))

typedef pair<int, int> ii;
typedef pair<double, ii> dii;

int p[MAX], r[MAX];

void make(int n) {
    for (int i = 0; i <= n; i++) {
        p[i] = i; r[i] = 0;
    }
}

int find(int i) {
    return p[i] == i ? i : p[i] = find(p[i]);
}

int _union(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return 0;
    if (r[u] > r[v]) p[v] = u;
    else {
        p[u] = v;
        if (r[u] == r[v]) r[v]++;
    }
    return 1;
}

void kruskal(vector<ii> towns) {
    vector<dii> roads;
    int u, v, have_roads = 0;
    for (int i = 0; i < (int)towns.size(); i++)
        for (int j = i + 1; j < (int)towns.size(); j++)
            roads.push_back(make_pair(dist(towns[i], towns[j]),
                            ii(i + 1, j + 1)));
    sort(roads.begin(), roads.end());
    for (auto i: roads) {
        u = i.second.first;
        v = i.second.second;
        if (_union(u, v)) {
            printf("%d %d\n", u, v);
            have_roads = 1;
        }
    }
    if (!have_roads) printf("No new highways need\n");
}

int main(void) {
    int t, n, m, x, y;
    scanf("%d", &t);
    while (t--) {
        vector<ii> towns;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            towns.push_back(ii(x, y));
        }
        make(n);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            _union(x, y);
        }
        kruskal(towns);
        if (t) putchar('\n');
    }
    return 0;
}
