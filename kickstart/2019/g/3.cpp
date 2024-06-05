#include <cstdio>

const int MAXN = 20;

inline int lowbit(int x) {
    return x & (-x);
}

int n, h;
int a[MAXN], b[MAXN];
int f_a[1 << MAXN][MAXN + 1], f_b[1 << MAXN][MAXN + 1];
int mask;

long long sum[1 << MAXN];
void solve(int *val, int f[][MAXN + 1]) {
    for(int i = 0; i < n; i++) {
        sum[1 << i] = val[i];
    }
    for(int i = 1; i < mask; i++) {
        int lo = lowbit(i);
        if(i == lo) {
            continue;
        }
        sum[i] = sum[i ^ lo] + sum[lo];
    }
    long long tot = sum[mask - 1];
    for(int i = 0; i < mask; i++) {
        if(sum[i] <= tot - h) {
            f[i][n] = 1;
        }
        else {
            f[i][n] = 0;
        }
    }
    for(int j = n - 1; j >= 0; j--) {
        for(int i = 0; i < mask; i++) {
            if(i >> j & 1) {
                f[i][j] = f[i][j + 1];
            }
            else {
                f[i][j] = f[i][j + 1] + f[i ^ (1 << j)][j + 1];
            }
        }
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        scanf("%d%d", &n, &h);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }
        mask = (1 << n);
        solve(a, f_a);
        solve(b, f_b);

        long long ans = 0;
        for(int i = 0; i < mask; i++) {
            int sign = 0;
            for(int j = 0; j < n; j++) {
                if(i >> j & 1) {
                    sign ^= 1;
                }
            }
            if(sign == 0) {
                ans += (long long)f_a[i][0] * f_b[i][0];
            }
            else {
                ans -= (long long)f_a[i][0] * f_b[i][0];
            }
        }
        printf("Case #%d: %lld\n", cnt_case, ans);
    }
    return 0;
}
