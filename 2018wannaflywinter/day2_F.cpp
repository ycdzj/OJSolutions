#include <cstdio>

const int MAXN = 6005;
const int MOD = 998244353;

int powmod(int a, int x) {
    long long cur = a, res = 1;
    while(x) {
        if(x & 1) res = (res * cur) % MOD;
        cur = (cur * cur) % MOD;
        x >>= 1;
    }
    return res;
}
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }

int f[MAXN][MAXN];
int fac[MAXN], inv_fac[MAXN];

int main() {
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) fac[i] = mulmod(fac[i - 1], i);
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for(int i = MAXN - 2; i >= 0; i--) inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);

    int inv_4 = powmod(4, MOD - 2);
    for(int i = 1; i < MAXN; i++) {
        f[i][0] = mulmod(i, mulmod(i - 1, mulmod(fac[i], inv_4)));
    }
    for(int j = 1; j < MAXN; j++) {
        for(int i = 1, sum = 0; i < MAXN; i++) {
            f[i][j] = mulmod(fac[i - 1], mulmod(sum, 2));
            sum = addmod(sum, mulmod(f[i][j - 1], inv_fac[i]));
        }
    }
    
    int t; scanf("%d", &t);
    for(int cnt_case = 1; cnt_case <= t; cnt_case++) {
        int n, k;
        scanf("%d%d", &n, &k);
        printf("Case #%d: %d\n", cnt_case, f[n][k - 1]);
    }
    return 0;
}