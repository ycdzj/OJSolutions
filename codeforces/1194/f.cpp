#include <cstdio>

const int MOD = 1e9 + 7;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
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
const int INV_2 = powmod(2, MOD - 2);

const int MAXN = 2e5 + 5;
int t[MAXN];

int fac[MAXN], inv_fac[MAXN];
int com(int n, int m) {
    return mulmod(fac[n], mulmod(inv_fac[m], inv_fac[n - m]));
}
int main() {
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for(int i = MAXN - 2; i >= 0; i--) {
        inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);
    }

    int n;
    long long T;
    scanf("%d%lld", &n, &T);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &t[i]);
    }

    long long rem = T;
    int prefix = 1, pos = 0;
    int ans = 0;
    int p2 = 1;
    for(int i = 1; i <= n; i++) {
        rem -= t[i];
        if(rem < 0) break;
        while(pos < i - 1 && pos < rem - 1) {
            prefix = addmod(prefix, mulmod(p2, com(i - 1, ++pos)));
        }
        while(pos > rem - 1) {
            prefix = addmod(prefix, MOD - mulmod(p2, com(i - 1, pos--)));
        }
        ans = addmod(ans, prefix);
        if(rem <= i - 1) {
            ans = addmod(ans, mulmod(p2, mulmod(INV_2, com(i - 1, rem))));
        }
        prefix = addmod(prefix, MOD - mulmod(mulmod(p2, com(i - 1, pos)), INV_2));
        p2 = mulmod(p2, INV_2);
    }
    printf("%d\n", ans);
    return 0;
}
