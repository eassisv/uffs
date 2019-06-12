#include <cstdio>
#include <cstring>

#define MAX 112345

typedef long long ll;

ll b, p, l, n;
ll bit[MAX];

int main(void) {
  while (scanf("%d %d %d %d", &b, &p, &l, &n), b) {
    memset(bit, 0, sizeof(bit));
    for (int i = 0; i < l; i++) expb[i] = expbin(b, i, p); 
    for (int i = 0)
  return 0;
}
