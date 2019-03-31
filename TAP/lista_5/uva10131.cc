#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX 1123

struct Elep{
    int w, s, i;
    Elep() {}
    Elep(int _w, int _s, int _i): w(_w), s(_s), i(_i) {}
};

Elep Ws[MAX];
int memo[MAX], path[MAX], ans[MAX];

void solve(int n) {
    int i, j, g = 0;
    memset(path, -1, sizeof(path));
    for (i = 0; i < n; i++) {
        memo[i] = 1;
        for (j = 0; j < i; j++) {
            if (Ws[j].s > Ws[i].s && Ws[j].w < Ws[i].w && memo[j] >= memo[i]) {
                memo[i] = memo[j] + 1;
                path[i] = j;
                if (memo[i] > memo[g]) g = i;
            }
        }
    }
    printf("%d\n", memo[g]);
    ans[0] = Ws[g].i;
    for (i = 1, g = path[g]; g != -1;
         i++, g = path[g]) ans[i] = Ws[g].i;
    while (i) printf("%d\n", ans[--i] + 1);
}

int cmp(const void *a, const void *b) {
    Elep e1 = *(Elep *)a, e2 = *(Elep *)b;
    if (e1.w != e2.w) return e1.w - e2.w;
    return e2.s - e1.s;
}


int main(void) {
    int w, s, n = 0;
    while (scanf("%d %d", &w, &s) != EOF) {
        Ws[n] = Elep(w, s, n);
        n++;
    }
    if (!n) { printf("0\n"); return 0; }
    qsort(Ws, n, sizeof(Elep), cmp);
    //for (int i = 0; i < n; i++) printf("%d %d %d\n", Ws[i].w, Ws[i].s, Ws[i].i);
    solve(n);
    return 0;
}
