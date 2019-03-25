#include<cstdio>
#include<cstring>

#define MAX 112

int p[MAX], rank[MAX];

void Make(int n) {
    for (int i = 0; i < n; ++i) { p[i] = i; rank[i] = 0; }
}

int Find(int i) { return p[i] == i ? i : p[i] = Find(p[i]); }

int Union(int i, int j) {
    i = Find(i); j = Find(j);
    if (i == j) return 0;
    if (rank[i] > rank[j]) p[j] = i;
    else {
        p[i] = j;
        if (rank[i] == rank[j]) ++rank[j];
    }
    return 1;
}

int main(void) {
    int t, n, m, x, y;
    scanf("%d", &t);
    for (int c = 0; c < t; ++c) {
        scanf("%d %d", &n, &m);
        Make(n);
        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &x, &y);
            n -= Union(x - 1, y - 1);
        }
        printf("Caso #%d: ", c + 1);
        if (!(n - 1)) printf("a promessa foi cumprida\n");
        else printf("ainda falta(m) %d estrada(s)\n", n - 1);
    }
    return 0;
}
