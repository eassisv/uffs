#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

#define mt make_tuple
#define pb push_back

typedef long long ll;
typedef tuple<double, ll, ll, ll> dt;
vector<dt> ds;

int main(void) {
  ll i, j, day = 1, ans = 0;
  while (scanf("%lld %lld", &i, &j) != EOF)
    ds.pb(mt((double)i / (double)j, j, day++, i));
  priority_queue<dt, vector<dt>, greater<dt>> Q;
  //    for (i = 0; i < (int)ds.size(); i++) {
  //        printf("%lf\n", get<0>(ds[i]));
  //    }
  Q.push(ds[0]);
  day = i = 1;
  while (!Q.empty()) {
    dt tp = Q.top();
    Q.pop();
    ans += (day - get<2>(tp)) * get<1>(tp);
    day += get<3>(tp);
    while (i < (int)ds.size()) {
      if (get<2>(ds[i]) > day)
        break;
      Q.push(ds[i++]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
