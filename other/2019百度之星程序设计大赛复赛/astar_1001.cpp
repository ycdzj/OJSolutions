#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int n;
int a[MAXN][2];
long long f[MAXN][2];
bool vis[MAXN][2];

long long dis(long long x, long long y) {
    x -= y;
    if(x < 0) {
        x = -x;
    }
    return x;
}

long long get_f(int u, int par, int idx) {
    if(vis[u][idx]) {
        return f[u][idx];
    }
    vis[u][idx] = true;
    long long res = 0;
    for(int v : adj[u]) {
        if(v == par) {
            continue;
        }
        long long cur = 0;
        for(int i = 0; i < 2; i++) {
            long long val = get_f(v, u, i) + dis(a[v][i], a[u][idx]);
            cur = max(cur, val);
        }
        res += cur;
    }
    return f[u][idx] = res;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            adj[i].clear();
            vis[i][0] = false;
            vis[i][1] = false;
        }
        for(int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 2; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        printf("%lld\n", max(get_f(1, 1, 0), get_f(1, 1, 1)));
    }
    return 0;
}
