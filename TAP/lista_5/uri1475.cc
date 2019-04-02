#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 1123

int n, c, t1, t2;
int ns[MAX], memo[MAX];

int solve(int i) {
    if (i == n) return 0;
    if (memo[i] != -1) return memo[i];
    int a = t1, b = t2, j;
    if (ns[n - 1] - ns[i] > t1) {
        for (j = i + 1; ns[j] - ns[i] <= t1; j++);
        a = t1 + solve(j);
    }
    if (ns[n - 1] - ns[i] > t2) {
        for (j = i + 1; ns[j] - ns[i] <= t2; j++);
        b = t2 + solve(j);
    }
    return memo[i] = min(a, b);
}

int main(void) {
    while (scanf("%d %d %d %d", &n, &c, &t1, &t2) != EOF) {
        for (int i = 0; i < n; i++) scanf("%d", ns + i);
        memset(memo, - 1, sizeof(memo));
        printf("%d\n", solve(0));
    }
    return 0;
}
