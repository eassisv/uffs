#include <cstdio>
#include <cstring>

#define MAX 1123456

bool prim[MAX], hprim[MAX];
int lprim[MAX], nhprim[MAX];
int n, nprim;

void sieve() {
  memset(prim, 1, sizeof(prim));
  prim[0] = prim[1] = 0;
  for (int i = 2; i < MAX; i++) {
    if (!prim[i]) continue;
    lprim[nprim++] = i;
    for (int j = i + i; j < MAX; j += i)
      prim[j] = 0;
  }
}

void hiper_primes() {
  int ps = 0, divs, fpidx, fp, tmp;
  memset(hprim, 0, sizeof(hprim));
  hprim[0] = hprim[1] = 0;
  for (int i = 2; i < MAX; i++) {
    divs = fpidx = 0;
    fp = lprim[0]; tmp = i;
    while (fp * fp <= tmp) {
      while (!(tmp % fp)) { divs++; tmp /= fp; }
      fp = lprim[++fpidx];
    }
    if (tmp != 1) divs++;
    
  }
}

int main(void) {
  sieve();
  hiper_primes();
  while (scanf("%d", &n) != EOF) {
    printf("%d\n", nhprim[n]);
  }   
  return 0;
}
