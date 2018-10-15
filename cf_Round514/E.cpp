#include <cstdio>
#include <vector>
const int MAXN = 1e5 + 5;
int n, l;
long long s, w[MAXN][20];
int fa[MAXN][20];
int get(int u) {
	long long cur_s = 0;
	int cur_l = 0;
	for(int i = 19; i >= 0; i--) {
		if(cur_l + (1 << i) <= l && cur_s + w[u][i] <= s) {
			cur_l += (1 << i);
			cur_s += w[u][i];
			u = fa[u][i];
		}
	}
	return cur_l;
}
std::vector<int> adj[MAXN];
bool flag;
void dfs(int u, int &res, int &len) {
	res = 0;
	len = 0;
	for(auto v : adj[u]) if(v != fa[u][0]) {
		int cur_res, cur_len;
		dfs(v, cur_res, cur_len);
		res += cur_res;
		len = std::max(len, cur_len);
	}
	if(len == 0) {
		len = get(u);
		if(len == 0) flag = true;
		res++;
	}
	len--;
}
int main() {
	scanf("%d%d%lld", &n, &l, &s);
	for(int i = 1; i <= n; i++) scanf("%lld", &w[i][0]);
	for(int i = 2; i <= n; i++) {
		scanf("%d", &fa[i][0]);
		adj[fa[i][0]].push_back(i);
	}
	fa[1][0] = 1;
	for(int i = 1; i < 20; i++) {
		for(int u = 1; u <= n; u++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
			w[u][i] = w[u][i - 1] + w[fa[u][i - 1]][i - 1];
		}
	}
	int res, len;
	dfs(1, res, len);
	if(flag) printf("-1\n");
	else printf("%d\n", res);
	return 0;
}
