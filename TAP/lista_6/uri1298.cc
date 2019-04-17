#include <utility>
#include <queue>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 3123
#define valid(x, y) (x > 0 && x < 2 * n -1) \
                    

typedef pair<int, int> ii;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool seen[2 * MAX][2 * MAX];
int n;

int bfs(int i, int j, vector<string> &maze) {
    int x, y, ans = 1;
    queue<ii> Q;
    Q.push(make_pair(i, j));
    while (!Q.empty()) {
        x = Q.front().first; y = Q.front().second;
        Q.pop();
        seen[x][y] = true;
        for (int k = 0; k < 4; k++) {
            i = x + dx[k]; j = y + dy[k];
            if (valid(x, y)) {
               if (x == 2 * n - 1 && !y) ans = 0; 
            }
        }
    }
    return ans;
}

int main(void) {
    int ans;
    char line[2 * MAX];
    while (scanf("%d", &n) != EOF) {
        vector<string> maze;
        memset(seen, 0, sizeof(seen));
        for (int i = 0; i < 2 * n - 1; i++) {
            scanf(" %s", line);
            if (i & 1) maze.push_back(string(" ") + string(line)); 
            else maze.push_back(string(line) + string(" "));
            maze.push_back(maze.back());
        }
        ans = 0;
        for (int i = 0; i < 2 * n; i++)
            for (int j = 0; j <= 2 * n; j++)
                ans += bfs(i, j, maze);
        printf("%d\n", ans);
    }
    return 0;
}
