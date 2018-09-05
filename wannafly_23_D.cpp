#include <cstdio>
#include <vector>
#include <map>
using namespace std;
const int MAXN = 1e5 + 5;
int n, q, c[MAXN];
vector<int> adj[MAXN];
int fa[MAXN][20];
int dep[MAXN];
map<int, pair<int, int>> dia;
void dfs(int u, int pre, int d) {
	fa[u][0] = pre;
	dep[u] = d;
	for(int i = 0; i < adj[u].size(); i++) if(adj[u][i] != pre) {
		dfs(adj[u][i], u, d + 1);
	}
}
int lca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	int d = dep[v] - dep[u];
	for(int i = 19; i >= 0; i--) if(d >> i & 1) {
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
int dis(int u, int v) {
	int p = lca(u, v);
	return dep[v] + dep[u] - 2 * dep[p];
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		if(dia[c[i]].first == 0) dia[c[i]] = {i, i};
		else dia[c[i]].second = i;
	}
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1, 0);
	for(int i = 1; i < 20; i++) {
		for(int u = 1; u <= n; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for(int i = 1; i <= n; i++) {
		int d1 = dis(dia[c[i]].first, dia[c[i]].second);
		int d2 = dis(dia[c[i]].first, i);
		int d3 = dis(dia[c[i]].second, i);
		if(d2 >= d1 && d2 >= d3) dia[c[i]] = {dia[c[i]].first, i};
		else if(d3 >= d1 && d3 >= d2) dia[c[i]] = {dia[c[i]].second, i};
	}
	while(q--) {
		int x, y; scanf("%d%d", &x, &y);
		if(dia.find(x) == dia.end() || dia.find(y) == dia.end()) printf("%d\n", 0);
		else {
			int d = dis(dia[x].first, dia[y].first);
			d = std::max(d, dis(dia[x].first, dia[y].second));
			d = std::max(d, dis(dia[x].second, dia[y].first));
			d = std::max(d, dis(dia[x].second, dia[y].second));
			printf("%d\n", d);
		}
	}
	return 0;
}

