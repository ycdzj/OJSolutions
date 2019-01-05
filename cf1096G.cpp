#include <iostream>
using namespace std;

const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
inline int powmod(int a, int x) {
    long long cur = a, res = 1;
    while(x) {
        if(x & 1) res = (res * cur) % MOD;
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return res;
}

const int MAXN = 1e6 + 5;

void ntt(int a[], int n, bool reverse) {
    static int buf[MAXN * 2];
    int lg = 0;
    while((1 << lg) < n) lg++;
    for(int i = 0; i < n; i++) {
        int pos = 0;
        for(int j = 0; j < lg; j++) pos |= ((i >> j & 1) << (lg - 1 - j));
        buf[pos] = a[i];
    }
    for(int i = 0; i < n; i++) a[i] = buf[i];

    for(int l = 1; l < n; l <<= 1) {
        int w = powmod(3, (MOD - 1) / (2 * l));
        if(reverse) w = powmod(w, MOD - 2);
        for(int i = 0; i < n; i += 2 * l) {
            int cur = 1;
            for(int j = 0; j < l; j++) {
                int t = mulmod(cur, a[i + j + l]);
                int u = a[i + j];
                a[i + j] = addmod(u, t);
                a[i + j + l] = addmod(u, MOD - t);
                cur = mulmod(cur, w);
            }
        }
    }
    if(reverse) {
        int inv_n = powmod(n, MOD - 2);
        for(int i = 0; i < n; i++) a[i] = mulmod(a[i], inv_n);
    }
}
void polymul(int res[], int a[], int b[], int n) {
    int m = 1;
    while(m < n) m <<= 1;
    m <<= 1;
    ntt(a, m, false);
    ntt(b, m, false);
    for(int i = 0; i < m; i++) res[i] = mulmod(a[i], b[i]);
    ntt(res, m, true);
}
int a[MAXN * 2];
int n, k;
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; i++) {
        int x; scanf("%d", &x);
        a[x] = 1;
    }
    int m = 1;
    while(m < n * 5) m <<= 1;
    ntt(a, m, false);
    for(int i = 0; i < m; i++) a[i] = powmod(a[i], n / 2);
    ntt(a, m, true);
    int ans = 0;
    for(int i = 0; i < m; i++) ans = addmod(ans, mulmod(a[i], a[i]));
    printf("%d\n", ans);
    return 0;
}