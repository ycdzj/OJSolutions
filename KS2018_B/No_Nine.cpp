#include <cstdio>

const int MAXN = 20;
typedef long long ll;

ll f[MAXN][9];
int p10[MAXN];

ll solve(ll val) {
    int cnt = 0, buf[MAXN];
    while(val) {
        buf[cnt++] = val % 10;
        val /= 10;
    }
    ll ans = 0;
    for(int i = cnt - 1, cur = 0; i >= 0; i--) {
        for(int x = 0; x < buf[i]; x++) {
            ans += f[i][(9 - (p10[i] * x + cur) % 9) % 9];
        }
        cur = (cur + buf[i] * p10[i]) % 9;
    }
    return ans;
}

int main() {
    for(int i = 1; i < 9; i++) f[0][i] = 1;
    for(int i = 1, cur = 1; i < MAXN; i++) {
        for(int j = 0; j < 9; j++) {
            for(int k = 0; k < 9; k++) {
                f[i][j] += f[i - 1][(j - (cur * k) % 9 + 9) % 9];
            }
        }
        cur = (cur * 10) % 9;
    }
    p10[0] = 1;
    for(int i = 1; i < MAXN; i++) p10[i] = (p10[i - 1] * 10) % 9;
    int T;
    scanf("%d", &T);
    for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
        ll f, l; scanf("%lld%lld", &f, &l);
        printf("Case #%d: %lld\n", cnt_case, solve(l + 1) - solve(f));
    }
    return 0;
}