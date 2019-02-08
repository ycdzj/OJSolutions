#include <cstdio>
#include <cstring>
const int MOD = 1e9 + 7;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
const int MAXN = 100000 + 5;
int n, s;
int f[MAXN][4][2];
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &s);
        f[1][1][0] = s;
        for(int i = 2; i <= n; i++) for(int k = 0; k <= 1; k++) {
            int sum = addmod(f[i - 1][1][k], addmod(f[i - 1][2][k], f[i - 1][3][k]));
            f[i][1][k] = mulmod(sum, s - 1);
            f[i][2][k] = f[i - 1][1][k];
            if(k > 0) f[i][3][k] = f[i - 1][2][k - 1];
        }
        printf("%d\n", addmod(f[n][1][1], addmod(f[n][2][1], f[n][3][1])));
    }
    return 0;
}