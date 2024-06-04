#include <cstdio>

const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }

const int MAXN = 1e6 + 5;
int n;
int fac[MAXN];
int main() {
    scanf("%d", &n);

    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = mulmod(fac[i - 1], i);

    int ans = 0;
    for(int x = 0, cur = 1; x <= n; x++) {
        ans = addmod(ans, mulmod(cur, addmod(fac[n - x], MOD - 1)));
        cur = mulmod(cur, n - x);
    }

    printf("%d\n", addmod(ans, 1));
    return 0;
}