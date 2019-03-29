#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<double, int> di;
priority_queue <di, vector<di>, greater<di>> pq;

int main(void) {
    int C, n, t, f;
    scanf("%d", &C);
    while (C--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &t, &f);
            pq.push(make_pair((double)t / (double)f, i + 1));
        }
        while ((int)pq.size() > 1) {
            printf("%d ", pq.top().second);
            pq.pop();
        }
        printf("%d\n", pq.top().second);
        pq.pop();
		if (C) putchar('\n');
    }
    return 0;
}
