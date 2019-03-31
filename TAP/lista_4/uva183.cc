#include <cstdio>
#include <cmath>
#include <cstring>

#define MAX 212

char bitmap[MAX][MAX]; 

void solve_b(int l, int r, int t, int b) {
    int sum = 0;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < r; j++) {
            sum += (int)(bitmap[i][j] - '0');
        }
    }
    printf("%d %d %d %d %d\n", l, r, t, b, sum);
    if (!sum) { printf("0"); return; }
    if (sum == ((r - l) * (b - t))) { printf("1"); return; }
    printf("D");
    int h_m = ceil((r + l) / 2.0), v_m = ceil((t + b) / 2.0);
    if (r - l > 1) {
        solve_b(l, h_m, t, v_m);
        solve_b(h_m, r, t, v_m);
    }
    if (b - t > 1) {
        solve_b(l, h_m, v_m, b);
        solve_b(h_m, r, v_m, b);
    }
}

int main(void) {
    int r, c;
    char form;
    while (scanf(" %c %d %d ", &form, &r, &c) && form != '#') {
        printf("%c %d %d\n", form, r, c);
        if (form == 'B') {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    scanf("%c", &bitmap[i][j]);
                    printf("%c", bitmap[i][j]);
                }
            }
            puts("");
            solve_b(0, c, 0, r);
            putchar('\n');
        } else {
            
        }
    }
    return 0;
}
