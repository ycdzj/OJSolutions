#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 1e5 + 5;
typedef long long ll;
const ll INF = 1e18;
struct Edge {
	int v, w;
};
vector<Edge> adj[MAXN];
int fa[MAXN][20], dep[MAXN];
int n, m;
ll dis[MAXN][50], sum[MAXN];
vector<int> buf;
bool vis[MAXN], lol[MAXN];
void dfs(int u, int pre) {
	vis[u] = true;
	for(int i = 0; i < adj[u].size(); i++) if(adj[u][i].v != pre) {
		if(!vis[adj[u][i].v]) {
			fa[adj[u][i].v][0] = u;
			dep[adj[u][i].v] = dep[u] + 1;
			sum[adj[u][i].v] = sum[u] + adj[u][i].w;
			dfs(adj[u][i].v, u);
		}
		else {
			lol[u] = lol[adj[u][i].v] = true;
		}
	}
}
int lca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	int d = dep[v] - dep[u];
	for(int i = 0; i < 20; i++) if(d >> i & 1) {
		v = fa[v][i];
	}
	if(u == v) return v;
	for(int i = 19; i >= 0; i--) {
		if(fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> que;
void dij(int id) {
	for(int i = 1; i <= n; i++) dis[i][id] = INF;
	while(!que.empty()) que.pop();
	dis[buf[id]][id] = 0;
	que.emplace(0, buf[id]);
	while(!que.empty()) {
		auto cur = que.top(); que.pop();
		if(dis[cur.second][id] != cur.first) continue;
		int u = cur.second;
		for(int i = 0; i < adj[u].size(); i++) {
			if(dis[adj[u][i].v][id] > dis[u][id] + adj[u][i].w) {
				dis[adj[u][i].v][id] = dis[u][id] + adj[u][i].w;
				que.emplace(dis[adj[u][i].v][id], adj[u][i].v);
			}
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int u, v, d; scanf("%d%d%d", &u, &v, &d);
		adj[u].push_back({v, d});
		adj[v].push_back({u, d});
	}
	fa[1][0] = 1;
	sum[1] = 0;
	dep[1] = 0;
	dfs(1, 1);
	for(int i = 1; i < 20; i++) {
		for(int u = 1; u <= n; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = 1; i <= n; i++) if(lol[i]) buf.push_back(i);
	for(int i = 0; i < buf.size(); i++) dij(i);
	int q; scanf("%d", &q);
	while(q--) {
		int u, v; scanf("%d%d", &u, &v);
		int lc = lca(u, v);
		ll ans = sum[u] + sum[v] - 2 * sum[lc];
		for(int i = 0; i < buf.size(); i++)
			ans = std::min(ans, dis[u][i] + dis[v][i]);
		printf("%lld\n", ans);
	}
	return 0;
}