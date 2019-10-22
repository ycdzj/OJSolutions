#include <cstdio>

const int MOD = 998244353;
const int MAXN = 3605;

inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}
inline int powmod(long long a, int x) {
    long long res = 1;
    while(x) {
        if(x & 1) {
            res = (res * a) % MOD;
        }
        x >>= 1;
        a = (a * a) % MOD;
    }
    return res;
}

bool vis_row[MAXN], vis_col[MAXN];
int h, w, n;

void read_once() {
    int r, c;
    scanf("%d%d", &r, &c);
    vis_row[r] = true;
    vis_col[c] = true;
}

void solve(bool vis[], int f[][MAXN], int len) {
    f[0][0] = 1;
    for(int i = 1; i <= len; i++) {
        for(int j = 0; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if(i >= 2 && !vis[i] && !vis[i - 1]) {
                f[i][j] = addmod(f[i][j], f[i - 2][j - 1]);
            }
        }
    }
}
int count(bool vis[], int len) {
    int res = 0;
    for(int i = 1; i <= len; i++) {
        if(vis[i]) {
            res++;
        }
    }
    return res;
}
int f_row[MAXN][MAXN], f_col[MAXN][MAXN];
int fac[MAXN], inv_fac[MAXN];
int com(int n, int m) {
    return mulmod(fac[n], mulmod(1, inv_fac[n - m]));
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
    scanf("%d%d%d", &h, &w, &n);
    for(int i = 0; i < n; i++) {
        read_once();
        read_once();
    }
    solve(vis_row, f_row, h);
    solve(vis_col, f_col, w);
    int ans = 0;
    int cnt_row = count(vis_row, h);
    int cnt_col = count(vis_col, w);
    for(int x = 0; x <= h; x++) {
        for(int y = 0; y <= w; y++) {
            if(y + cnt_row + 2 * x <= h && x + cnt_col + 2 * y <= w) {
                ans = addmod(ans, mulmod(f_row[h][x], mulmod(f_col[w][y], mulmod(com(h - cnt_row - 2 * x, y), com(w - cnt_col - 2 * y, x)))));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
