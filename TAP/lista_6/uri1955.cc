#include <cstdio>
#include <cstring>

#define MAX 1123

int n, adj[MAX][MAX], seen[MAX];

int dfs(int u, int f) {
    if (seen[u]) return seen[u] == f;
    seen[u] = f;
    for (int i = 0; i < n; i++) {
        if (adj[u][i]) continue;
        if (!dfs(i, f ^ 1)) return 0;
    }
    return 1;
}

int main(void) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);
    memset(seen, 0, sizeof(seen));
    for (int i = 0; i < n; i++)
        if (!seen[i])
            if (!dfs(i, -1)) {
                printf("Fail!\n");
                return 0;
            }
    printf("Bazinga!\n");
    return 0;
}
