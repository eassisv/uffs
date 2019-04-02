#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 1123
#define MAXM 4123
#define f first
#define s second
#define mp make_pair

typedef pair<int, int> ii;

ii ns[MAXN];
int n, memo[MAXN][MAXM];

int solve(int i, int j) {
    if (i >= n) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (j > ns[i].f) return memo[i][j] = solve(i + 1, j);
    return memo[i][j] =
        max(solve(i + 1, j), 
            solve(i + 1, ns[i].s) + ns[i].s - ns[i].f);
}

int main(void) {
    int x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        ns[i] = mp(min(x, y), max(x, y));
    }
    sort(ns, ns + n);
    memset(memo, -1, sizeof(memo));
    printf("%d\n", solve(0, 0));
    return 0;
}
