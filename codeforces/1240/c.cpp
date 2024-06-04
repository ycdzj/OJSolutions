#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 5e5 + 5;

struct Edge {
    int v, w;
};

struct Result {
    long long val[2];
};

int n, k;
vector<Edge> adj[MAXN];

Result dfs(int u, int par) {
    priority_queue<long long> que;
    long long s = 0;
    for(Edge e : adj[u]) {
        if(e.v != par) {
            Result cur = dfs(e.v, u);
            s += cur.val[0];
            long long d = cur.val[1] + e.w - cur.val[0];
            if(d > 0) {
                que.push(d);
            }
        }
    }
    for(int i = 0; i < k - 1; i++) {
        if(!que.empty()) {
            s += que.top();
            que.pop();
        }
        else {
            break;
        }
    }
    Result res{s, s};
    if(!que.empty()) {
        res.val[0] += que.top();
    }
    return res;
}

int main() {
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        scanf("%d", &k);
        for(int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for(int i = 0; i < n - 1; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        Result res = dfs(1, 1);
        printf("%lld\n", max(res.val[0], res.val[1]));
    }
    return 0;
}
