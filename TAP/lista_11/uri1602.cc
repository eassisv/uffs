#include <cstdio>
#include <cstring>

#define MAX 2123456

bool prim[MAX];
int divs[MAX], prims[MAX];
int n;

void sieve() {
  for (int i = 0; i < MAX; i++) {
    prim[i] = true;
    divs[i] = 1;
  }
  prim[0] = prim[1] = 0;
  for (int i = 2; i < MAX; i++) {
    divs[i]++;
    for (int j = i + i; j < MAX; j += i) {
      prim[j] = false;
      divs[j]++;
    }
  }
}

int main(void) {
  sieve();
  prims[2] = 1;
  for (int i = 3; i < MAX; i++) {
    prims[i] = prims[i - 1];
    if (prim[divs[i]]) prims[i]++;
  }
  while (scanf("%d", &n) != EOF) {
    printf("%d\n", prims[n]);
  }   
  return 0;
}
