#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX 1123456
#define MAXN 1123

int ns[MAX], memo[MAXN];
int n, c, t1, t2;

int solve(int i, int d) {
    if (i == n) return 0;
    if (memo[i] != -1) return memo[i];
    
}

int main(void) {
    while (scanf("%d %d %d %d", &n, &c, &t1, &t2) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &ns[i]);
        }
        sort(ns, ns + n);
        memset(memo, -1, sizeof(memo));
        printf("%d\n", solve(0, ns[0]));
    }
    return 0;
}
