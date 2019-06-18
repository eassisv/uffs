#include <cstdio>
#include <cstring>

#define MAX 112345

typedef long long unsigned llu;

llu b, p, l, n;
llu bit[MAX], exps[MAX], hs[MAX];

llu expbin(llu a,llu e) {
  if (!e) return 1L;
  if (e & 1L) return a * expbin(a, e - 1L) % p;
  llu tmp = expbin(a, e >> 1L);
  return tmp * tmp % p;
}

void setbit(llu i, llu v) {
  for (; i < MAX; i += (i & -i))
    bit[i] = (bit[i] + v + p) % p;
}

llu getbit(llu i) {
  llu t = 0;
  if (!i) return 0;
  for (; i; i -= (i & -i))
    t = (bit[i] + t + p) % p;
  return t;
}

int main(void) {
  llu i, j, ans = 0;
  char op;
  while (scanf("%llu %llu %llu %llu", &b, &p, &l, &n), b) {
    memset(bit, 0, sizeof(bit));
    memset(hs, 0, sizeof(hs));
    for (i = 1; i <= l; i++)
      exps[i] = expbin(b, l - i); 
    while (n--) {
      scanf(" %c %llu %llu", &op, &i, &j);  
      if (op == 'E') {
        setbit(i, (p - hs[i]) % p); 
        setbit(i, (hs[i] = j * exps[i] % p));
      } else {
        ans = (getbit(j) - getbit(i - 1) + p) % p; 
        printf("%llu\n", ans * expbin(exps[j], p - 2) % p);
      }
    }
    puts("-");
  }
  return 0;
}
