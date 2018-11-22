#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 3e5 + 5;
typedef long long ll;
struct Edge {
    int v, w, idx;
};
vector<Edge> adj[MAXN];
int n, m, k;
ll dis[MAXN];
int pre[MAXN];
vector<int> ans;
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w, i});
        adj[v].push_back({u, w, i});
    }
    for(int i = 1; i <= n; i++) dis[i] = 1e18;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
    pre[1] = -1;
    dis[1] = 0;
    que.emplace(dis[1], 1);
    while(!que.empty()) {
        int u = que.top().second;
        ll dis_u = que.top().first;
        que.pop();
        if(dis[u] != dis_u) continue;
        if(pre[u] != -1) ans.push_back(pre[u]);
        for(auto edg : adj[u]) if(dis[edg.v] > dis_u + edg.w) {
            dis[edg.v] = dis_u + edg.w;
            pre[edg.v] = edg.idx;
            que.emplace(dis[edg.v], edg.v);
        }
    }
    k = std::min(k, (int)ans.size());
    printf("%d\n", k);
    for(int i = 0; i < k; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}