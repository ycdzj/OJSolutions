#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;
const ll INF = 1e18;

int n, m, k;
ll h[MAXN], w[MAXN];
vector<pair<int, ll>> adj[MAXN];
ll dis[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++) scanf("%lld", &h[i]);
    for(int i = 1; i <= n; i++) {
        if(h[i] > h[1] + k) {
            w[i] = h[i] - (h[1] + k);
            w[i] = w[i] * w[i];
        }
        dis[i] = INF;
    }
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;

    dis[1] = 0;
    que.push({dis[1], 1});

    while(!que.empty()) {
        int u = que.top().second;
        ll dis_u = que.top().first;
        que.pop();
        if(dis[u] != dis_u) continue;
        for(auto pr : adj[u]) {
            int v = pr.first;
            if(dis_u + pr.second + w[v] < dis[v]) {
                dis[v] = dis_u + pr.second + w[v];
                que.push({dis[v], v});
            }
        }
    }

    printf("%lld\n", dis[n]);

    return 0;
}