#include <cstdio>
#include <cmath>

const int MAXN = 1e5 + 5;
const int MOD = 998244353;
const int B = 319;

inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }

int n;
int f[MAXN][2];
int g[MAXN][2];
long long sum[MAXN];

int main() {
    scanf("%d", &n);
    int m = n / B;

    int cur = 0, pre = 1;
    f[0][cur] = 1;
    for(int j = 3; j <= B - 1; j++) {
        cur ^= 1;
        pre ^= 1;
        for(int i = 0; i <= n; i++) {
            f[i][cur] = f[i][pre];
            if(i >= j) f[i][cur] = (f[i][cur] + f[i - j][cur]) % MOD;
        }
    }

    int gcur = 0;
    int gpre = 1;
    g[0][gcur] = 1;
    sum[0] = 1;
    for(int j = 1; j <= m; j++) {
        gcur ^= 1;
        gpre ^= 1;
        for(int i = j * (B - 1); i < j * B; i++) g[i][gcur] = 0;
        for(int i = j * B; i <= n; i++) {
            g[i][gcur] = (g[i - B][gpre] + g[i - j][gcur]) % MOD;
            sum[i] += g[i][gcur];
        }
    }

    long long ans = 0;
    for(int i = 0; i <= n; i++) {
        ans += mulmod(sum[n - i] % MOD, f[i][cur]);
    }
    printf("%lld\n", ans % MOD);
    return 0;
}