#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MOD = 998244353;
inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}
inline int powmod(int a, int x) {
    long long cur = a, res = 1;
    while(x) {
        if(x & 1) {
            res = (res * cur) % MOD;
        }
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return res;
}

int fac[MAXN], inv_fac[MAXN];
inline int com(int n, int m) {
    return mulmod(fac[n], mulmod(inv_fac[m], inv_fac[n - m]));
}

int f[MAXN][MAXN];

int a[MAXN];
int n;

int main() {
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for(int i = MAXN - 2; i >= 0; i--) {
        inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);
    }

    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        for(int j = 0; j <= n + 1; j++) {
            f[n + 1][j] = 1;
        }
        for(int i = n, cnt = 1; i >= 1; i--) {
            if(i > 1 && a[i - 1] == a[i]) {
                cnt++;
                continue;
            }
            else {
                for(int j = 0; j <= i; j++) {
                    f[i][j] = 0;
                    for(int k = 0; k <= j && k <= cnt; k++) {
                        int val = mulmod(inv_fac[k], inv_fac[j- k]);
                        f[i][j] = addmod(f[i][j], mulmod(val, f[i + cnt][j - k + cnt - k]));
                    }
                    f[i][j] = mulmod(f[i][j], mulmod(fac[cnt], fac[j]));
                }
                cnt = 1;
            }
        }
        printf("%d\n", f[1][0]);
    }
    return 0;
}
