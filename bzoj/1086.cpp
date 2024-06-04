#include <cstdio>
#include <vector>
using namespace std;
const int MAXN = 1e3 + 5;
vector<int> adj[MAXN], stk;
int ans[MAXN];
int cap[MAXN];
int n, b, cnt;
void dfs(int u, int pre) {
	int cur = stk.size();
	for(int i = 0; i < adj[u].size(); i++) if(adj[u][i] != pre) {
		dfs(adj[u][i], u);
		if(stk.size() - cur >= b) {
			while(stk.size() > cur) {
				ans[stk.back()] = cnt;
				stk.pop_back();
			}
			cap[cnt] = u;
			cnt++;
		}
	}
	stk.push_back(u);
}
int main() {
	scanf("%d%d", &n, &b);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1);
	if(stk.size() == b) cap[cnt++] = 1;
	if(cnt == 0) printf("0\n");
	else {
		while(!stk.empty()) {
			ans[stk.back()] = cnt - 1;
			stk.pop_back();
		}
		printf("%d\n", cnt);
		for(int i = 1; i <= n; i++) printf("%d%c", ans[i] + 1, (i + 1 <= n) ? ' ' : '\n');
		for(int i = 0; i < cnt; i++) printf("%d%c", cap[i], (i + 1 < cnt) ? ' ' : '\n');
	}
	return 0;
}