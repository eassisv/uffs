#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 112
#define MAXM 11234

int dgs[MAXN], memo[MAXN][MAXM];

int solve(int i, int j) {
    if (i < 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (dgs[i] > j) return memo[i][j] = solve(i - 1, j);
    return memo[i][j] = 
        max(solve(i - 1, j),
            solve(i - 1, j - dgs[i]) + dgs[i]);
}

int main(void) {
    int a, b, r, k;
    while (scanf("%d %d", &r, &k) != EOF) {
        memset(dgs, 0, sizeof(dgs));
        for (int i = 0; i < k; i++) {
            scanf("%d %d", &a, &b);
            dgs[a]++; dgs[b]++;
        }
        memset(memo, -1, sizeof(memo));
        printf("%c\n", solve(r - 1, k) == k ? 'S': 'N');
    }
    return 0;
}
