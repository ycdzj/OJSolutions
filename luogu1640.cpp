#include <cstdio>
#include <cstring>
const int MAXN = 2e6 + 5;
struct { int v, next; } e[MAXN];
int head[MAXN], cnt_edge;
inline void add_edge(int u, int v) {
	e[cnt_edge] = {v, head[u]};
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
int n;
int hungarian() {
	memset(link, 0xff, sizeof(link));
	int res = 0;
	for(int i = n; i < 2 * n; i++) if(link[i] == -1) {
		memset(vis, 0, sizeof(vis));
		if(hungarian_dfs(i)) res++;
		else return res;
	}
	return res;
}
int main() {
	memset(head, 0xff, sizeof(head));
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		if(a <= n) add_edge(n + a - 1, i);
		if(b <= n) add_edge(n + b - 1, i);
	}
	printf("%d\n", hungarian());
	return 0;
}
