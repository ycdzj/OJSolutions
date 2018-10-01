#include <cstdio>
#include <cstring>
const int MAXN = 405;
struct { int v, next; } e[MAXN * MAXN];
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
int hungarian(int n) {
	memset(link, 0xff, sizeof(link));
	int res = 0;
	for(int i = 0; i < n; i++) if(link[i] == -1) {
		memset(vis, 0, sizeof(vis));
		if(hungarian_dfs(i)) res++;
	}
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
			int a; scanf("%d", &a);
			if(a == 1) add_edge(i, n + j);
		}
		if(hungarian(n) == n) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
