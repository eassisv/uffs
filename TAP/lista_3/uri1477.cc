#include<cstdio>
#include<cstring>

#define MAX 112345
#define left(i) ((i) << 1)
#define right(i) ((left(i)) + 1)

struct Node {
    int x, y, z;
    Node(): x(0), y(0), z(0) {}
    Node(int _x, int _y, int _z): x(_x), y(_y), z(_z) {}
    Node(int i) { 
        x = !i; y = (i == 1); z = (i == 2);
    }
    Node operator >> (const int i) const {
        if (!(i % 3)) return Node(x, y, z);
        if ((i % 3) == 1) return Node(z, x, y);
        return Node(y, z, x);
    }
    Node operator + (const Node &other) const {
        return Node(x + other.x, y + other.y, z + other.z); 
    }
};

Node st[4 * MAX];
int lazy[4 * MAX], ps[MAX];

Node build(int p, int l, int r) {
    if (l == r) return st[p] = Node(ps[l]);
    int m = (l + r) >> 1;
    return st[p] = build(left(p), l, m) + build(right(p), m + 1, r);
}

Node update(int p, int l, int r, int i, int j) {
    if (lazy[p]) {
        if (l != r) {
            lazy[left(p)] += lazy[p];
            lazy[right(p)] += lazy[p];
        } else {
            ps[l] += lazy[p];
        }
        st[p] = st[p] >> lazy[p];
        lazy[p] = 0;
    }
    if (r < i || j < l) return st[p];
    if (l >= i && j >= r) {
        if (l != r) {
            lazy[left(p)]++;
            lazy[right(p)]++;
        } else {
            ps[l] = (ps[l] + lazy[p]) % 3;
        }
        return st[p] = st[p] >> 1;
    }
    int m = (l + r) >> 1;
    return st[p] = update(left(p), l, m, i, j) + update(right(p), m + 1, r, i, j);
}

Node query(int p, int l, int r, int i, int j) {
    if (lazy[p]) {
        if (l != r){ 
            lazy[left(p)] += lazy[p];
            lazy[right(p)] += lazy[p];
        }
        st[p] = st[p] >> lazy[p];
        lazy[p] = 0;
    }
    if (r < i || j < l) return Node();
    if (l >= i && j >= r) return st[p];
    int m = (l + r) >> 1;
    return query(left(p), l, m, i, j) + query(right(p), m + 1, r, i, j);
}

int main(void) {
    int n, m, a, b;
    char op;
    Node ans;
    while (scanf("%d %d", &n, &m) != EOF) {
        memset(lazy, 0, sizeof(lazy));
        memset(st, 0, sizeof(st));
        memset(ps, 0, sizeof(ps));
        build(1, 0, n - 1);
        for (int i = 0; i < m; ++i) {
            scanf(" %c %d %d", &op, &a, &b);
            if (op == 'C') {
                ans = query(1, 0, n - 1, a - 1, b - 1);
                printf("%d %d %d\n", ans.x, ans.y, ans.z);
            } else {
                update(1, 0, n - 1, a - 1, b - 1);
            }
        }
        puts("");
    }
}
