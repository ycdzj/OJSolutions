#include <cstdio>
#include <algorithm>

const int MOD = 1e9 + 7;
const int MAXN = 3e6 + 5;

inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}
inline int powmod(int a, int x) {
    int res = 1;
    int cur = a;
    while(x) {
        if(x & 1) {
            res = mulmod(res, cur);
        }
        cur = mulmod(cur, cur);
        x >>= 1;
    }
    return res;
}

int fac[MAXN], inv_fac[MAXN];
void init_fac() {
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for(int i = MAXN - 2; i >= 0; i--) {
        inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);
    }
}

int combine(int n, int m) {
    return mulmod(fac[n], mulmod(inv_fac[n - m], inv_fac[m]));
}

int n, q;
int p[MAXN], r[MAXN];

int main() {
    init_fac();

    scanf("%d%d", &n, &q);

    for(int i = 0; i <= 3 * n + 3; i++) {
        r[i] = addmod(r[i], combine(3 * n + 3, i));
    }
    for(int i = 0; i <= 3; i++) {
        r[i] = addmod(r[i], MOD - combine(3, i));
    }

    for(int i = 3 * n; i >= 0; i--) {
        p[i] = r[i + 3];
        // r[i + 3] = 0;
        r[i + 2] = addmod(r[i + 2], MOD - mulmod(3, p[i]));
        r[i + 1] = addmod(r[i + 1], MOD - mulmod(3, p[i]));
    }

    while(q--) {
        int x;
        scanf("%d", &x);

        printf("%d\n", p[x]);
    }
    return 0;
}
