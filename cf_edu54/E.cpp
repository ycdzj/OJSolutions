#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 3e5 + 5;
vector<int> adj[MAXN];
vector<pair<int, int>> q[MAXN];
int n, m;
long long ans[MAXN], depval[MAXN];
void dfs(int u, int dep, int pre, long long cur) {
    for(auto pr : q[u]) {
        depval[dep] += pr.second;
        if(dep + pr.first + 1 < MAXN) depval[dep + pr.first + 1] -= pr.second;
    }
    long long curr = cur + depval[dep];
    ans[u] = curr;
    for(auto v : adj[u]) if(v != pre) dfs(v, dep + 1, u, curr);
    for(auto pr : q[u]) {
        depval[dep] -= pr.second;
        if(dep + pr.first + 1 < MAXN) depval[dep + pr.first + 1] += pr.second;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int v, d, x; scanf("%d%d%d", &v, &d, &x);
        q[v].emplace_back(d, x);
    }
    dfs(1, 0, 1, 0);
    for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    printf("\n");
    return 0;
}