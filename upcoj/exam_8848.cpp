// 虚树 + 暴搜
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN], tree[MAXN], buf;
int clr[MAXN], fa[20][MAXN], dep[MAXN];
bool vis[MAXN];
void dfs(int u, int par, int d) {
	fa[0][u] = par;
	dep[u] = d;
	clr[u] = 1;
	for(int i = 0; i < adj[u].size(); i++) if(adj[u][i] != par) {
		if(clr[adj[u][i]] == 1) {
			vis[adj[u][i]] = vis[u] = true;
			buf.push_back(adj[u][i]);
			buf.push_back(u);
			tree[adj[u][i]].push_back(u);
			tree[u].push_back(adj[u][i]);
		}
		else if(clr[adj[u][i]] == 0) {
			dfs(adj[u][i], u, d + 1);
		}
	}
	clr[u] = 2;
}
int lca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	int delta = dep[v] - dep[u];
	for(int i = 19; i >= 0; i--) if(delta >> i & 1) {
		v = fa[i][v];
	}
	if(u == v) return u;
	for(int i = 19; i >= 0; i--) {
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u]; v = fa[i][v];
		}
	}
	return fa[0][u];
}
int root;
void build(int u, int pre) {
	clr[u] = 3;
	if(vis[u]) {
		if(pre == -1) root = u;
		else {
			tree[pre].push_back(u);
			tree[u].push_back(pre);
		}
		pre = u;
	}
	for(int i = 0; i < adj[u].size(); i++) if(clr[adj[u][i]] == 2) {
		build(adj[u][i], pre);
	}
}
int n, m, ans;
void count(int u, int s, int par) {
	clr[u] = 1;
	bool flag = false;
	for(int i = 0; i < tree[u].size(); i++) if(tree[u][i] <= s) {
		if(tree[u][i] != par) {
			if(tree[u][i] == s) ans++;
			else if(clr[tree[u][i]] == 0) count(tree[u][i], s, u);
		}
		else {
			if(flag)
				if(tree[u][i] == s) ans++;
			flag = true;
		}
	}
	clr[u] = 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1, 0);
	for(int i = 1; i < 20; i++) {
		for(int j = 1; j <= n; j++) fa[i][j] = fa[i - 1][fa[i - 1][j]];
	}
	for(int i = 0; i < buf.size(); i++) for(int j = i + 1; j < buf.size(); j++) {
		vis[lca(buf[i], buf[j])] = true;
	}
	build(1, -1);
	memset(clr, 0, sizeof(clr));
	for(int i = 1; i <= n; i++) if(vis[i]) count(i, i, i);
	printf("%d\n", ans / 2);
	return 0;
}
 
/**************************************************************
	Problem: 8848
	User: St087
	Language: C++
	Result: 正确
	Time:128 ms
	Memory:23756 kb
****************************************************************/