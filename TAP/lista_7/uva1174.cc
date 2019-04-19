#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <utility>
#include <string>
#include <vector>
using namespace std;

#define MAX 2123
#define f first
#define s second
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

int p[MAX], rk[MAX];

void make(int i) { p[i] = i; }

int find(int i) {
    return p[i] == i ? i : p[i] = find(p[i]);
}

int Union(int i, int j) {
    i = find(i), j = find(j);
    if (i == j) return 0;
    if (rk[i] > rk[j]) p[j] = i;
    else {
        p[i] = j;
        rk[j] += (rk[i] == rk[j]);
    }
    return 1;
}

int kruskal(vector<iii> &ms) {
    int ans = 0;
    sort(ms.begin(), ms.end());
    for (int i = 0; i < (int)ms.size(); i++) {
        if (Union(ms[i].s.f, ms[i].s.s))
            ans += ms[i].f;
    }
    return ans;
}

int main(void) {
    int t, m, n, c;
    char b[11], e[11];
    scanf("%d", &t);
    while (t--) {
        map<string, int> idx;
        vector<iii> ms;
        memset(rk, 0, sizeof(rk));
        scanf("%d %d", &m, &n);
        for (int i = 0, j = 0; i < n; i++) {
            scanf(" %s %s %d", b, e, &c);
            string sb(b), se(e);
            if (idx.find(sb) == idx.end()) { 
                idx[sb] = j; make(j++);
            }
            if (idx.find(se) == idx.end()) {
                idx[se] = j; make(j++);
            }
            ms.push_back(iii(c, ii(idx[sb], idx[se]))); 
        }
        printf("%d\n%s", kruskal(ms), t ? "\n" : "");
    }
    return 0;
}
