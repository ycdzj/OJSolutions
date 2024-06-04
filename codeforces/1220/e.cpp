#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 5;

int n, m;
vector<int> adj[MAXN];
int w[MAXN];

bool vis[MAXN];
long long ans;
long long val[MAXN];
bool dfs(int u, int par) {
    vis[u] = true;
    bool flag = false;
    for(auto v : adj[u]) {
        if(v == par) {
            continue;
        }
        if(vis[v]) {
            flag = true;
        }
        else {
            if(dfs(v, u)) {
                flag = true;
            }
            val[u] = max(val[u], val[v]);
        }
    }
    if(flag) {
        ans += w[u];
        val[u] = 0;
    }
    else {
        val[u] += w[u];
    }
    return flag;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int s;
    scanf("%d", &s);
    dfs(s, s);
    long long max_val = 0;
    for(int i = 1; i <= n; i++) {
        max_val = max(max_val, val[i]);
    }
    printf("%lld\n", ans + max_val);
    return 0;
}
