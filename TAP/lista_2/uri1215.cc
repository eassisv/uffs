#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main(void) {
  char c;
  string w;
  set<string> dc;
  while (scanf("%c", &c) != EOF) {
    c = tolower(c);
    if (isalpha(c))
      w.push_back(c);
    else if (w.size()) {
      dc.insert(w);
      w.clear();
    }
  }
  for (auto i : dc) {
    cout << i << '\n';
  }
  return 0;
}
