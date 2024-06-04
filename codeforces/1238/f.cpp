#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 3e5 + 5;

int n;
vector<int> adj[MAXN];
int val[MAXN];

int ans;
int dfs(int u, int par) {
    vector<int> res;
    for(int v : adj[u]) {
        if(v != par) {
            res.push_back(dfs(v, u));
        }
    }
    if(res.empty()) {
        return val[u];
    }
    sort(res.begin(), res.end());
    int sz = res.size();
    int res_val = val[u] + res[sz - 1];
    if(sz >= 2) {
        ans = max(ans, res_val + res[sz - 2]);
    }
    ans = max(ans, res_val);
    return res_val;
}

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            adj[i].clear();
            val[i] = -1;
        }
        for(int i = 1; i < n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            adj[x].push_back(y);
            adj[y].push_back(x);
            val[x]++;
            val[y]++;
        }
        ans = 0;
        dfs(1, 1);
        printf("%d\n", ans + 2);
    }
    return 0;
}
