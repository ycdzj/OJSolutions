#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
struct Node {
	int nxt[2], val;
	bool end;
} t[500 * 20];
int cnt_node;
int new_node() {
	t[cnt_node] = { {0, 0}, 0, false };
	return cnt_node++;
}
struct Trie {
	int root;
	void init() {
		root = new_node();
	}
	void insert(int *str, int len, int val) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].nxt[str[i]] == 0) t[cur].nxt[str[i]] = new_node();
			cur = t[cur].nxt[str[i]];
		}
		if(t[cur].end) {
			t[cur].val = std::min(t[cur].val, val);
		}
		else {
			t[cur].end = true;
			t[cur].val = val;
		}
	}
	int find(int *str, int len) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].nxt[str[i]] == 0) break;
			cur = t[cur].nxt[str[i]];
		}
		return cur;
	}
} suff, pre;
const int INF = 1e9 + 5;
struct Graph {
	static const int MAXN = 505 * 20;
	static const int MAXM = 505 * 60;
	struct { int v, cap, next; } e[MAXM];
	int head[MAXN], cnt_edge;
	void add_edge_(int u, int v, int cap) {
		e[cnt_edge] = { v, cap, head[u] };
		head[u] = cnt_edge++;
	}
	void add_edge(int u, int v, int cap) {
		add_edge_(u, v, cap);
		add_edge_(v, u, 0);
	}
	void init() {
		memset(head, 0xff, sizeof(head));
		cnt_edge = 0;
	}
	
	int level[MAXN], cur[MAXN];
	bool dinic_bfs(int s, int t) {
		memset(level, 0xff, sizeof(level));
		std::queue<int> q;

		level[s] = 0;
		cur[s] = head[s];
		q.push(s);
		while(!q.empty()) {
			int u = q.front(); q.pop();
			if(u == t) return true;
			for(int i = head[u]; i != -1; i = e[i].next) if(e[i].cap) {
				if(level[e[i].v] == -1) {
					level[e[i].v] = level[u] + 1;
					cur[e[i].v] = head[e[i].v];
					q.push(e[i].v);
				}
			}
		}
		return false;
	}

	int dinic_dfs(int u, int cur_min, int t) {
		if(u == t) return cur_min;
		if(level[u] >= level[t]) return 0;

		int res = 0;
		for(int& i = cur[u]; cur_min && i != -1; i = e[i].next) if(e[i].cap) {
			if(level[e[i].v] == level[u] + 1) {
				int nxt_min = std::min(cur_min, e[i].cap);
				int x = dinic_dfs(e[i].v, nxt_min, t);
				cur_min -= x;
				e[i].cap -= x;
				e[i ^ 1].cap += x;
				res += x;
			}
		}
		return res;
	}

	int dinic(int s, int t) {
		int res = 0;
		while(dinic_bfs(s, t)) {
			res += dinic_dfs(s, INF, t);
			if(res >= INF) break;
		}
		return res;
	}
} G;
void pdfs(int u) {
	for(int i = 0; i < 2; i++) if(t[u].nxt[i] != 0) {
		int v = t[u].nxt[i];
		if(!t[v].end) t[v].val = INF;
		G.add_edge(u, v, t[v].val);
		pdfs(v);
	}
}
void sdfs(int u) {
	for(int i = 0; i < 2; i++) if(t[u].nxt[i] != 0) {
		int v = t[u].nxt[i];
		if(!t[v].end) t[v].val = INF;
		G.add_edge(v, u, t[v].val);
		sdfs(v);
	}
}
int n, m, a[505];
int main() {
	int T; scanf("%d", &T);
	for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		G.init();
		cnt_node = 1;
		pre.init();
		suff.init();
		for(int i = 0; i < m; i++) {
			char str[10], num[10]; int val;
			scanf("%s%s%d", str, num, &val);
			int len = strlen(num);
			int d[10];
			for(int j = 0; j < len; j++) d[j] = num[j] - '0';
			if(str[0] == 'P') {
				pre.insert(d, len, val);
			}
			else {
				std::reverse(d, d + len);
				suff.insert(d, len, val);
			}
		}
		pdfs(pre.root);
		sdfs(suff.root);
		for(int i = 0; i < n; i++) {
			int d[10];
			for(int j = 0; j < 8; j++) d[7 - j] = (a[i] >> j & 1);
			int p_idx = pre.find(d, 8);
			std::reverse(d, d + 8);
			int s_idx = suff.find(d, 8);
			G.add_edge(p_idx, s_idx, INF);
		}
		int ans = G.dinic(pre.root, suff.root);
		if(ans >= INF) ans = -1;
		printf("Case #%d: %d\n", cnt_case, ans);
	}
	return 0;
}
