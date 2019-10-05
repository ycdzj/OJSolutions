#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = 20;
constexpr int MOD = 1e9 + 7;

inline int addmod(long long a, long long b) {
    return static_cast<int>((a + b) % MOD);
}
inline int mulmod(long long a, long long b) {
    return static_cast<int>((a * b) % MOD);
}
long long gcd(long long a, long long b) {
    if(a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

vector<int> adj[MAXN];
int par[MAXN][MAXM];
long long g[MAXN][MAXM];
int dep[MAXN], ans[MAXN];
bool vis[MAXN];
int n;

void dfs_par(int u, int p) {
    par[u][0] = p;
    for(int i = 1; i < MAXM; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
        g[u][i] = gcd(g[u][i - 1], g[par[u][i - 1]][i - 1]);
    }
    for(int v : adj[u]) {
        if(v != p) {
            dep[v] = dep[u] + 1;
            dfs_par(v, u);
        }
    }
}
int get_next(int u, long long cur) {
    for(int i = MAXM - 1; i >= 0; i--) {
        if(g[u][i] % cur == 0) {
            u = par[u][i];
        }
    }
    return u;
}
void get_ans(int i) {
    if(vis[i]) {
        return;
    }
    vis[i] = true;
    if(g[i][0] == 0) {
        if(i != 1) {
            get_ans(par[i][0]);
            ans[i] = ans[par[i][0]];
        }
    }
    else {
        int u = i;
        long long cur = g[i][0];
        do {
            int nxt_u = get_next(u, cur);
            ans[i] = addmod(ans[i], mulmod(dep[u] - dep[nxt_u], cur));
            cur = gcd(cur, g[nxt_u][0]);
            u = nxt_u;
        } while(u != 1);
        ans[i] = addmod(ans[i], gcd(cur, g[1][0]));
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &g[i][0]);
    }
    for(int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs_par(1, 1);
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        get_ans(i);
        tot = addmod(tot, ans[i]);
    }
    printf("%d\n", tot);
    return 0;
}
