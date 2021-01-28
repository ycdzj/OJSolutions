#include <cstdio>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 3e3 + 5;
const int INF = 1e9;

inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}

int n;
int c[MAXN], d[MAXN];
int f[MAXN], g[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n - 1; i++) {
            scanf("%d", &c[i]);
        }
        c[0] = INF;
        c[n] = INF;
        for(int i = 1; i <= n; i++) {
            d[i] = min(c[i], c[i - 1]);
        }
        f[n] = 1;
        g[n] = d[n] - 1;
        for(int i = n - 1; i >= 1; i--) {
            f[i] = 0;
            int l = d[i], r = d[i];
            for(int j = i; l <= r && j <= n; j++) {
                if(j == n) {
                    f[i] = addmod(f[i], r - l + 1);
                }
                else {
                    if(r == c[j]) {
                        f[i] = addmod(f[i], f[j + 1]);
                        f[i] = addmod(f[i], g[j + 1]);
                        j--;
                        r--;
                    }
                    else {
                        if(c[j] == d[j + 1]) {
                            f[i] = addmod(f[i], mulmod(r - l + 1, f[j + 1]));
                        }
                        int nxt_l = max(c[j] - r, 1);
                        int nxt_r = min(c[j] - l, d[j + 1]);
                        l = nxt_l;
                        r = nxt_r;
                    }
                }
            }

            g[i] = 0;
            l = 1;
            r = d[i] - 1;
            for(int j = i; l <= r && j <= n; j++) {
                if(j == n) {
                    g[i] = addmod(g[i], r - l + 1);
                }
                else {
                    if(r == c[j]) {
                        g[i] = addmod(g[i], f[j + 1]);
                        g[i] = addmod(g[i], g[j + 1]);
                        j--;
                        r--;
                    }
                    else {
                        if(c[j] == d[j + 1]) {
                            g[i] = addmod(g[i], mulmod(r - l + 1, f[j + 1]));
                        }
                        int nxt_l = max(c[j] - r, 1);
                        int nxt_r = min(c[j] - l, d[j + 1]);
                        l = nxt_l;
                        r = nxt_r;
                    }
                }
            }
        }
        printf("%d\n", addmod(f[1], g[1]));
    }
    return 0;
}
