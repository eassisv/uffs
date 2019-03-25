#include<cstdio>
#include<iomanip>
#include<vector>
using namespace std;

int main(void) {
    int x, count, ans;
    vector<int> cycles;
    while (scanf("%d", &x)) {
        if (!x) {
            if (cycles.empty()) break;
            
            for (int i = 20; i <= 5 * 60 * 60; ++i) {
                ans = 1;
                for (auto j: cycles) {
                    if ((i / j) % 2 == 0 && j * (i / j + 1) - i > 5)
                        continue;
                    else {
                        ans = 0;
                        break;
                    }
                }
                if (ans) {
                    printf("%02d:%02d:%02d\n", i / 3600, (i / 60) % 60, i % 60); 
                    break;
                }
                if (!ans && i == 5 * 60 * 60) printf("Signals fail to synchronise in 5 hours\n"); 
            }
        }            
        else {
            cycles.push_back(x);
            continue;
        }
        cycles.clear();
    }

    return 0;
}
