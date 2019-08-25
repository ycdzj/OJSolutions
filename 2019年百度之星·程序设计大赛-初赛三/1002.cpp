#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
const int MAXN = 1005;

struct Edge {
    int v, w;
};

struct QueNode {
    int v;
    long long dis;
    bool operator < (const QueNode &node) const {
        return dis > node.dis;
    }
};

vector<Edge> adj[MAXN];
long long dis[MAXN];
int ans[MAXN];
bool vis[MAXN];
int n, m;

const long long INF = 1e18;
void dijkstra(int s) {
    for(int i = 0; i < n; i++) {
        dis[i] = INF;
        vis[i] = false;
        ans[i] = -1;
    }

    priority_queue<QueNode> que;
    dis[s] = 0;
    que.push({s, dis[s]});
    while(!que.empty()) {
        QueNode node = que.top();
        que.pop();
        if(dis[node.v] != node.dis) {
            continue;
        }
        int u = node.v;
        long long dis_u = node.dis;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].v;
            if(dis[v] > dis_u + adj[u][i].w) {
                dis[v] = dis_u + adj[u][i].w;
                que.push({v, dis[v]});
            }
        }
    }
}
int s;
int get_ans(int u) {
    if(vis[u]) {
        return ans[u];
    }
    vis[u] = true;
    ans[u] = n;
    for(int i = 0; i < adj[u].size(); i++) {
        if(dis[adj[u][i].v] + adj[u][i].w == dis[u]) {
            if(adj[u][i].v == s) {
                ans[u] = -1;
            }
            else {
                ans[u] = min(ans[u], max(adj[u][i].v, get_ans(adj[u][i].v)));
            }
        }
    }
    return ans[u];
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for(int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u;
            --v;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        long long sum = 0;
        for(int u = 0; u < n; u++) {
            dijkstra(u);
            vis[u] = true;
            ans[u] = -1;
            s = u;
            for(int i = 0; i < n; i++) {
                sum += get_ans(i) + 1;
            }
        }
        printf("%d\n", (int)(sum % MOD));
    }
    return 0;
}
