#include <cstdio>

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}

int f[MAXN][4];
int get(int n) {
    if(n == 0) {
        return 0;
    }
    if(n == 1) {
        return 0;
    }
    int res = 0;
    for(int j = 0; j < 4; j++) {
        res = addmod(res, f[n - 2][j]);
    }
    return addmod(res, MOD - 2);
}
int main() {
    f[0][0] = 1;
    f[0][1] = 1;
    f[0][2] = 1;
    f[0][3] = 1;
    for(int i = 1; i < MAXN; i++) {
        f[i][0] = f[i - 1][2];
        f[i][3] = f[i - 1][1];
        f[i][1] = addmod(f[i - 1][2], f[i - 1][0]);
        f[i][2] = addmod(f[i - 1][3], f[i - 1][1]);
    }
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d\n", addmod(2, addmod(get(n), get(m))));
    return 0;
}
