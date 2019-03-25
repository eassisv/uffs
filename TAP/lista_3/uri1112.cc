#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;

#define MAX 1123

int bit[MAX][MAX];
int x, y, q;
int p;

void setbit(int i, int j, int v) {
    for (++i, ++j; i <= x + 1; i += (i & -i)) {
        int _j = j;
        for (; _j <= y + 1; _j += (_j & -_j))
            bit[i][_j] += v;
    }
}

int getbit(int i, int j) {
    int ans = 0;
    for (++i, ++j; i > 0; i -= (i & -i)) {
        int _j = j;
        for (; _j > 0; _j -= (_j & -_j))
            ans += bit[i][_j];
    }
    return ans;
}

int getbit(int i, int j, int w, int z) {
    return getbit(max(i, w), max(j, z)) - getbit(max(i, w), min(j, z) - 1)
        - getbit(min(i, w) - 1, max(j, z)) + getbit(min(i, w) - 1, min(j, z) - 1);
}

int main(void) {
    char c;
    int _x, _y, w, z;
    while (scanf("%d %d %d", &x, &y, &p) && (x || y || p)) {
        memset(bit, 0, sizeof(bit));
        scanf("%d", &q);
        while (q--) {
            scanf(" %c", &c);
            if (c == 'A') {
                scanf("%d %d %d", &z, &_x, &_y);
                setbit(_x, _y, z);
            } else {
                scanf("%d %d %d %d", &_x, &_y, &w, &z);
                printf("%d\n", p * getbit(_x, _y, w, z));
            }
        }
        puts("");
    }
    return 0;
}
