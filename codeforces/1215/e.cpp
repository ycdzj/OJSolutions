#include <cstdio>
#include <vector>
#include <climits>
using namespace std;

vector<int> pos[20];
int cnt[20];
int n;
long long g[20][1 << 20];
long long f[1 << 20];

inline int lowbit(int x) {
    return x & (-x);
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        --a;
        cnt[a]++;
        pos[a].push_back(i);
    }
    for(int c = 0; c < 20; c++) {
        for(int c2 = 0; c2 < 20; c2++) {
            int k = pos[c2].size();
            for(int i = (int)pos[c].size() - 1; i >= 0; i--) {
                while(k > 0 && pos[c2][k - 1] >= pos[c][i]) {
                    k--;
                }
                g[c][1 << c2] += pos[c2].size() - k;
            }
        }
    }
    for(int i = 1; i < (1 << 20); i++) {
        for(int c = 0; c < 20; c++) {
            int lo = lowbit(i);
            g[c][i] = g[c][i ^ lo] + g[c][lo];
        }
    }
    for(int i = 1; i < (1 << 20); i++) {
        f[i] = LONG_LONG_MAX;
        for(int c = 0; c < 20; c++) {
            if(i >> c & 1) {
                f[i] = min(f[i], f[i ^ (1 << c)] + g[c][i ^ (1 << c)]);
            }
        }
    }
    printf("%lld\n", f[(1 << 20) - 1]);
    return 0;
}
