#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define MAX 212345
#define cmp compare

int m, t, ms[MAX], ts[MAX], b[MAX];

string notes[] = {
  "A", "A#","B", "C", "C#", "D",
  "D#", "E", "F", "F#", "G", "G#"
};

string notes2[] = {
  "", "Bb", "Cb", "B#", "Db", "",
  "Eb", "Fb", "E#", "Gb", "", "Ab" 
};

int val(string note) {
  for (int i = 0; i < 12; i++)
    if (!notes[i].cmp(note))
      return i;
  for (int i = 0; i < 12; i++)
    if (!notes2[i].cmp(note))
      return i;
  return 0;
}

void kmpre() {
  int i = 0, j = -1; b[0] = -1;
  while (i < t) {
    while (j >= 0 && ts[i] != ts[j]) j = b[j];
    i++; j++;
    b[i] = j;
  }
}

int kmp() {
  int i = 0, j = 0;
  while (i < m) {
    while (j >= 0 && ms[i] != ts[j]) j = b[j];
    i++; j++;
    if (j == t) return 1;
  }
  return 0;
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
        v = val(string{note});
        if (i) w[i - 1] = (v - p + 12) % 12;
        p = v;
      }
    }
    m--; t--; kmpre();
    printf("%c\n", kmp() ? 'S' : 'N');
  } 
  return 0;
}
