#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define MAX 112345

int m, t, ms[MAX], ts[MAX];

string notes[] = {
  "A", "A#","B", "C", "C#", "D",
  "D#", "E", "F", "F#", "G", "G#"
};

int val(string note) {
  for (int i = 0; i < 12; i++)
    if (!notes[i].compare(note))
      return i;
}

int main(void) {
  int p, v;
  char note[12];
  while (scanf("%d %d", &m , &t), m) {
    for (int j = 0; j < 2; j++) {
      int s = j ? t : m;
      int *w = j ? ts: ms; 
      for (int i = 0; i < s; i++) {
        scanf(" %s", note);
        if (note[1] == 'b') {
          note[1] = '#';
          note[0] = note[0] == 'A' ? 'G' : note[0] - 1;
        }
        v = val(string{note});
        if (i) w[i - 1] = v - p;
        p = v;
      }
    }
    for (int i = 0; i < m - 1; i++) printf("%d ", ms[i]); puts("");
    for (int i = 0; i < t - 1; i++) printf("%d ", ts[i]); puts("");
  } 
  return 0;
}
