#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 505;
struct Item {
	int u, v, w;
} e[MAXN * MAXN * 4];
bool cmp(const Item &x, const Item &y) {
	return x.w > y.w;
}
int n, m;
inline int get(int i, int j) { return (i - 1) * m + j - 1; }
int f[MAXN * MAXN];
int find(int x) {
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
vector<int> adj[MAXN * MAXN];
int dep[MAXN * MAXN], fa[MAXN * MAXN][20];
void dfs(int u, int pre) {
	for(int i = 0; i < adj[u].size(); i++) if(adj[u][i]!= pre) {
		int v = adj[u][i];
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		dfs(v, u);
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
			u = fa[u][i]; v = fa[v][i];
		}
	}
	return fa[u][0];
}
long long dis(int u, int v) {
	int p = lca(u, v);
	return dep[u] + dep[v] - 2 * dep[p];
}
int main() {
	scanf("%d%d", &n, &m);
	int cnt = 0;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
		f[get(i, j)] = get(i, j);
		char str[15];
		int w;
		scanf("%s%d", str, &w);
		if(str[0] == 'D') e[cnt++] = {get(i, j), get(i + 1, j), w};
		else if(str[0] == 'R') e[cnt++] = {get(i, j), get(i, j + 1), w};
		scanf("%s%d", str, &w);
		if(str[0] == 'D') e[cnt++] = {get(i, j), get(i + 1, j), w};
		else if(str[0] == 'R') e[cnt++] = {get(i, j), get(i, j + 1), w};
	}
	sort(e, e + cnt, cmp);
	for(int i = 0; i < cnt; i++) {
		int u = find(e[i].u), v = find(e[i].v);
		if(u != v) {
			f[u] = v;
			adj[e[i].u].push_back(e[i].v);
			adj[e[i].v].push_back(e[i].u);
		}
	}
	dfs(0, 0);
	int k = get(n, m);
	for(int i = 1; i < 20; i++) {
		for(int u = 0; u <= k; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	int q; scanf("%d", &q);
	while(q--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%lld\n", dis(get(x1, y1), get(x2, y2)));
	}
	return 0;
}