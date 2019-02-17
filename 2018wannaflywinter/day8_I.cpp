#include <cstdio>

const int MAXN = 1e5 + 5;
const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
inline int powmod(int a, int x) {
    long long res = 1, cur = a;
    while(x) {
        if(x & 1) res = (res * cur) % MOD;
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return (int)res;
}

void fwht(int a[], int n, bool reverse) {
    for(int l = 1; l < n; l <<= 1) {
        for(int i = 0; i < n; i += 2 * l) {
            for(int j = 0; j < l; j++) {
                int u = a[i + j];
                int t = a[i + j + l];
                a[i + j] = addmod(u, t);
                a[i + j + l] = addmod(u, MOD - t);
            }
        }
    }
    if(reverse) {
        int inv_n = powmod(n, MOD - 2);
        for(int i = 0; i < n; i++) a[i] = mulmod(a[i], inv_n);
    }
}

int n;
int v[MAXN];
int poly[1 << 20];
int cnt[50];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 10; j++) {
            int cur;
            scanf("%d", &cur);
            if(cur == 2) cur = 3;
            v[i] = (v[i] << 2 | cur);
        }
        poly[v[i]]++;
    }

    fwht(poly, 1 << 20, false);
    for(int i = 0; i < (1 << 20); i++) {
        poly[i] = mulmod(poly[i], poly[i]);
    }
    fwht(poly, 1 << 20, true);

    for(int i = 0; i < (1 << 20); i++) {
        int dis = 0;
        for(int j = 0, val = i; j < 10; j++) {
            int cur = (val & 3);
            val >>= 2;
            if(cur == 1 || cur == 2) dis += 1;
            else if(cur == 3) dis += 4;
        }
        cnt[dis] = addmod(cnt[dis], poly[i]);
    }
    int ans = 0;
    for(int i = 0; i <= 40; i++) {
        ans = addmod(ans, mulmod(cnt[i], cnt[i]));
    }
    printf("%d\n", ans);
    return 0;
}