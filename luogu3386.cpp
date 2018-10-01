#include <cstdio>
#include <cstring>

const int MAXN = 2005;
struct Graph {
	int n;
	struct { int v, next; } e[MAXN * MAXN];
	int head[MAXN], cnt_edge;
	void init(int n_) {
		n = n_;
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
	}
	void add_edge(int u, int v) {
		e[cnt_edge] = { v, head[u] };
		head[u] = cnt_edge++;
	}
	bool vis[MAXN];
	int link[MAXN];
	bool hungarian_dfs(int u) {
		for(int i = head[u]; i != -1; i = e[i].next) if(!vis[e[i].v]) {
				vis[e[i].v] = true;
				if(link[e[i].v] == -1 || hungarian_dfs(link[e[i].v])) {
					link[e[i].v] = u, link[u] = e[i].v;
					return true;
				}
			}
		return false;
	}
	int hungarian() {
		memset(link, 0xff, sizeof(link));
		int res = 0;
		for(int i = 0; i < n; i++) if(link[i] == -1) {
				memset(vis, 0, sizeof(vis));
				if(hungarian_dfs(i)) res++;
			}
		return res;
	}
} G;
int n, m, e;
int main() {
	scanf("%d%d%d", &n, &m, &e);
	G.init(n + m);
	for(int i = 0; i < e; i++) {
		int u, v; scanf("%d%d", &u, &v);
		if(u > n) continue;
		if(v > m) continue;
		--u; --v;
		G.add_edge(u, n + v);
	}
	printf("%d\n", G.hungarian());
	return 0;
}
