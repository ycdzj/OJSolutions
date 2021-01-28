#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Interval {
    int l, r;
};

const int MAXN = 1e3 + 5;
const int INF = 1e9;
int n;
Interval interval[MAXN];

int f[MAXN * 4][2];
int pos[MAXN * 4];

bool cmp(Interval a, Interval b) {
    if(a.l != b.l) {
        return a.l < b.l;
    }
    return a.r < b.r;
}

int g(int x) { return (x + 1) / 2; }

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &interval[i].l, &interval[i].r);
            pos[i * 4] = interval[i].l;
            pos[i * 4 + 1] = interval[i].r;
            pos[i * 4 + 2] = interval[i].l + 1;
            pos[i * 4 + 3] = interval[i].r - 1;
        }
        sort(pos, pos + 4 * n);
        int m = unique(pos, pos + 4 * n) - pos;

        int cur = 0, nxt = 1;
        for(int i = 0; i < m; i++) {
            if(pos[i] < interval[n - 1].l) {
                f[i][cur] = (interval[n - 1].l - pos[i] + 1) / 2;
            }
            else if(pos[i] > interval[n - 1].r) {
                f[i][cur] = (pos[i] - interval[n - 1].r + 1) / 2;
            }
            else {
                f[i][cur] = 0;
            }
        }
        for(int j = n - 2; j >= 0; j--) {
            cur ^= 1;
            nxt ^= 1;
            int ll, rr;
            for(int i = 0; i < m; i++) {
                if(interval[j].l <= pos[i] && pos[i] <= interval[j].r) {
                    f[i][cur] = f[i][nxt];
                }
                else {
                    f[i][cur] = INF;
                }
                if(pos[i] == interval[j].l) {
                    ll = i;
                }
                if(pos[i] == interval[j].r) {
                    rr = i;
                }
            }
            for(int i = ll - 1; i >= 0; i--) {
                f[i][cur] = min(g(pos[ll] - pos[i]) + f[ll][cur], g(pos[ll + 1] - pos[i]) + f[ll + 1][cur]);
            }
            for(int i = rr + 1; i < m; i++) {
                f[i][cur] = min(g(pos[i] - pos[rr]) + f[rr][cur], g(pos[i] - pos[rr - 1]) + f[rr - 1][cur]);
            }
        }
        int ans = INF;
        for(int i = 0; i < m; i++) {
            ans = min(ans, f[i][cur]);
        }
        printf("%d\n", ans);
    }

    return 0;
}