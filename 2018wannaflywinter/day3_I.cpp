#include <cstdio>

const int MAXN = 2e5 + 5;
const int MOD = 998244353;

inline int mulmod(long long a, int b) { return (a * b) % MOD; }

int n, m;
int cnt[MAXN], rank[MAXN], val[MAXN], p[MAXN], edg[MAXN];

int p2[MAXN], p3[MAXN];

void f(int u) {
    if(p[u] == u) return;
    f(p[u]);
    val[u] += val[p[u]];
    edg[u] += edg[p[u]];
    p[u] = p[p[u]];
}

int main() {
    scanf("%d%d", &n, &m);
    p2[0] = 1;
    p3[0] = 1;
    for(int i = 1; i <= n; i++) {
        p2[i] = mulmod(p2[i - 1], 2);
        p3[i] = mulmod(p3[i - 1], 3);
        p[i] = i;
    }
    for(int i = 0; i < m; i++) {
        int op; scanf("%d", &op);
        if(op == 1) {
            int x, y; scanf("%d%d", &x, &y);
            rank[y] = ++cnt[x];
            p[y] = x;
            edg[y] = 1;
            val[y] = cnt[y] - rank[y];
        }
        else if(op == 2) {
            int x; scanf("%d", &x);
            f(x);
            int cnt2 = val[x] + cnt[p[x]];
            int cnt1 = edg[x];
            int ans = mulmod(p2[cnt2], p3[n - cnt1 - cnt2]);
            printf("%d\n", ans);
        }
    }
    return 0;
}