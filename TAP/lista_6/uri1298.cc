#include <utility>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 3123
typedef pair<int, int> ii;

char maze[MAX][MAX];
bool seen[2 * MAX][2 * MAX];

int dfs(int i, int j) {

}

int main(void) {
    int n, ans;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < 2 * n; i++)
            scanf(" %s", (char *)(maze + i));
        ans = 0;
        for (int i = 0; i < 2 * n; i++)
            for (int j = 0; j <= 2 * n; j++)
                ans += dfs(i, j);
        printf("%d\n", ans);
    }
    return 0;
}
