#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 5e3 + 7;

int main(void) {
  int n;
  vector<int> xs(MAX, 0);

  while (cin >> n && n != 0) {
    int first = -1;
    for (int i = 0, x; i < n; i++) {
      scanf("%d", &x);
      xs[i] = x;
      if (first == -1 && x == 1) {
        first = i;
      }
    }
    int ans = 0, last, i;
    last = i = first == -1 ? 0 : first;
    do {
      if (!xs[(i + n - 1) % n] && !xs[i]) {
        ++ans;
        xs[i] = 1;
      }
      i = (i + 1) % n;
    } while (i != last);
    cout << ans << "\n";
  }

  return 0;
}
