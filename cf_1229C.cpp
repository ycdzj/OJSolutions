#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> in_adj[MAXN];
int deg[MAXN];
int n, m;

long long f(int i) {
    long long in_size = in_adj[i].size();
    return in_size * (deg[i] - in_size);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++deg[u];
        ++deg[v];
        if(u > v) {
            in_adj[v].push_back(u);
        }
        else {
            in_adj[u].push_back(v);
        }
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += f(i);
    }
    printf("%lld\n", ans);
    int q;
    scanf("%d", &q);
    while(q--) {
        int u;
        scanf("%d", &u);
        for(int v : in_adj[u]) {
            ans -= f(v);
            in_adj[v].push_back(u);
            ans += f(v);
        }
        ans -= f(u);
        in_adj[u].clear();
        ans += f(u);
        printf("%lld\n", ans);
    }
    return 0;
}
