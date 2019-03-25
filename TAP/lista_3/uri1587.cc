#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX 2123456
#define Vec(x) ((x) == 'A' ? as: bs)
#define Bit(x) ((x) == 'A' ? bit_a: bit_b)

int as[MAX], bs[MAX];
int bit_a[MAX], bit_b[MAX];

void setbit(int i, int v, int *bit) {
    for (++i; i < MAX; i += (i & -i)) bit[i] += v;
}

int getbit(int i, int *bit) {
    int t = 0;
    for (++i; i > 0; i -= (i & -i)) t += bit[i];
    return t;
}

int main(void) {
    int n, e, i, x, a, b, v;
    char c, xi;
    while (scanf("%d %d", &n, &e) && n) {
        memset(bit_a, 0, sizeof(bit_a));
        memset(bit_b, 0, sizeof(bit_b));
        for (i = 0; i < 2; i++) {
            int *v = !i ? as: bs;
            int *bit = !i ? bit_a: bit_b;
            for (int j = 0; j < n >> 1; j++) {
                scanf("%d", v + j + 1);
                setbit(v[j + 1], 1, bit);
            }
        }
        a = b = 0;
        while (e--) {
            scanf(" %c", &c);
            switch (c) {
                case 'M':
                    scanf(" %c%d %d", &xi, &i, &x);
                    setbit(Vec(xi)[i], -1, Bit(xi));
                    Vec(xi)[i] = x;
                    setbit(Vec(xi)[i], 1, Bit(xi));
                    break;
                case 'I':
                case 'P':
                    scanf(" %c%d", &xi, &i);
                    if (!v) continue;
                    if (xi == 'B') v = getbit(bs[i] - 1, bit_a) < ceil((double)n / (double)11) ? 0: 1;
                    else v = (n >> 1) - getbit(as[i], bit_b) < ceil((double)n / (double)11) ? 0: 1;
                    break;
                case 'G':
                    scanf(" %c", &xi);
                    if (v && xi == 'B') a++;
                    else if (v && xi == 'A') b++;
                case 'S':
                    v = 1;
            }
        }
        printf("%d X %d\n", a, b);
    }

    return 0;
}

