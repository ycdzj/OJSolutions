#include <cstdio>
#include <vector>
const int MAXN = 1e6 + 5;
const int INF = 1e9 + 5;
using namespace std;
int n, k;
vector<int> adj[MAXN];
int f[MAXN];
int dfs(int u, int dep) {
	int res = INF;
	if(adj[u].empty()) {
		res = dep;
		f[u] = 1;
	}
	else {
		for(auto v : adj[u]) {
			int cur = dfs(v, dep + 1);
			res = std::min(res, cur);
			f[u] += f[v];
		}
		if(res - dep >= k) f[u] = 0;
	}
	return res;
}
int dfs2(int u) {
	if(adj[u].empty()) return 1;
	int sum = 0, res = 0;
	for(auto v : adj[u]) sum += f[v];
	for(auto v : adj[u]) {
		res = std::max(res, dfs2(v) + sum - f[v]);
	}
	return res;
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 2; i <= n; i++) {
		int p; scanf("%d", &p);
		adj[p].push_back(i);
	}
	dfs(1, 0);
	printf("%d\n", dfs2(1));
	return 0;
}