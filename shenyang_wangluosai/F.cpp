#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 4015;
const int MAXM = 1e5 + 5;
const int INF = 1e9 + 5;
struct Graph {
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
	int n;
	void init(int n_) {
		n = n_;
		for(int i = 0; i < n; i++) head[i] = -1;
		cnt_edge = 0;
	}

	int level[MAXN], cur[MAXN];
	bool dinic_bfs(int s, int t) {
		for(int i = 0; i < n; i++) level[i] = -1;
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
		}
		return res;
	}
} G;
int n, m, k;
int l, r;
int main() {
	int cnt_case = 0;
	while(scanf("%d%d%d", &n, &m, &k) != EOF) {
		scanf("%d%d", &l, &r);
		G.init(n + m + 2);
		int s = n + m;
		int t = n + m + 1;
		for(int i = 0; i < n; i++) G.add_edge(s, i, l);
		for(int i = 0; i < m; i++) G.add_edge(n + i, t, l);
		for(int i = 0; i < k; i++) {
			int u, v; scanf("%d%d", &u, &v);
			--u; --v;
			G.add_edge(u, n + v, 1);
		}
		G.dinic(s, t);
		for(int i = G.head[s]; i != -1; i = G.e[i].next) {
			if(G.e[i].cap == 0) G.e[i].cap += r - l;
		}
		for(int i = G.head[t]; i != -1; i = G.e[i].next) {
			if(G.e[i ^ 1].cap == 0) G.e[i ^ 1].cap += r - l;
		}
		G.dinic(s, t);
		bool flag = true;
		for(int i = G.head[s]; i != -1; i = G.e[i].next) {
			if(G.e[i].cap + G.e[i ^ 1].cap == l && G.e[i].cap != 0) {
				flag = false;
				break;
			}
		}
		for(int i = G.head[t]; i != -1; i = G.e[i].next) {
			if(G.e[i ^ 1].cap + G.e[i].cap == l && G.e[i ^ 1].cap != 0) {
				flag = false;
				break;
			}
		}
		if(flag) printf("Case %d: Yes\n", ++cnt_case);
		else printf("Case %d: No\n", ++cnt_case);
	}
	return 0;
}