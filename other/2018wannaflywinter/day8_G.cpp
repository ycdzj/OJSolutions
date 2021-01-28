#include <cstdio>

const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }

const int MAXN = 2005;
int n, m, s[MAXN][MAXN];
char a[MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%s", a + 1);
        for(int j = 1; j <= m; j++) {
            s[i][j] = a[j] - '0';
            s[i][j] = addmod(s[i][j], s[i - 1][j]);
            s[i][j] = addmod(s[i][j], s[i][j - 1]);
            s[i][j] = addmod(s[i][j], MOD - s[i - 1][j - 1]);
        }
    }

    int ans = 0;
    for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) {
        ans = addmod(ans, mulmod(s[i][j], s[i][j]));
    }
    ans = mulmod(ans, mulmod(n + 1, m + 1));

    int sum = 0;
    for(int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) {
        sum = addmod(sum, s[i][j]);
    }
    ans = addmod(ans, mulmod(sum, sum));

    for(int j2 = 0; j2 <= m; j2++) {
        int f = 0;
        for(int i1 = 0; i1 <= n; i1++) f = addmod(f, s[i1][j2]);
        ans = addmod(ans, MOD - mulmod(m + 1, mulmod(f, f)));
    }

    for(int i1 = 0; i1 <= n; i1++) {
        int f = 0;
        for(int j1 = 0; j1 <= m; j1++) f = addmod(f, s[i1][j1]);
        ans = addmod(ans, MOD - mulmod(n + 1, mulmod(f, f)));
    }

    printf("%d\n", ans);
    return 0;
}