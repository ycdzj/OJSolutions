#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
const int MAXN = 1e5 + 5;
struct Query { int x, idx; };
struct ACA {
	struct Node {
		int next[26], fail, par;
	} t[MAXN];
	int cnt_node;
	int new_node() {
		return cnt_node++;
	}

	int root;
	void init() {
		cnt_node = 1;
		root = new_node();
		t[root].par = root;
	}
	int idx[MAXN], cnt;
	void insert(char *str, int len) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(str[i] == 'P') {
				idx[++cnt] = cur;
				continue;
			}
			else if(str[i] == 'B') {
				cur = t[cur].par;
				continue;
			}
			if(t[cur].next[str[i] - 'a'] == 0) {
				t[cur].next[str[i] - 'a'] = new_node();
				t[t[cur].next[str[i] - 'a']].par = cur;
			}
			cur = t[cur].next[str[i] - 'a'];
		}
	}
	void build() {
		std::queue<int> que;
		t[root].fail = root;
		for(int i = 0; i < 26; i++) {
			if(t[root].next[i] == 0) t[root].next[i] = root;
			else {
				t[t[root].next[i]].fail = root;
				que.push(t[root].next[i]);
			}
		}
		while(!que.empty()) {
			int u = que.front(); que.pop();
			for(int i = 0; i < 26; i++) {
				if(t[u].next[i] == 0) t[u].next[i] = t[t[u].fail].next[i];
				else {
					t[t[u].next[i]].fail = t[t[u].fail].next[i];
					que.push(t[u].next[i]);
				}
			}
		}
	}
} ac;
std::vector<int> adj[MAXN], adjj[MAXN];
int l[MAXN], r[MAXN];
int clk;
void dfs(int u) {
	l[u] = ++clk;
	for(auto v : adj[u]) dfs(v);
	r[u] = clk;
}
inline int lowbit(int x) { return x & (-x); }
int tree[MAXN];
void modify(int p, int val) {
	while(p <= clk) {
		tree[p] += val;
		p += lowbit(p);
	}
}
int query_prefix(int p) {
	int res = 0;
	while(p >= 1) {
		res += tree[p];
		p -= lowbit(p);
	}
	return res;
}
char str[MAXN];
int ans[MAXN];
std::vector<Query> query[MAXN];
void gao(int u) {
	modify(l[u], 1);
	for(auto &pr : query[u]) {
		ans[pr.idx] = query_prefix(r[pr.x]) - query_prefix(l[pr.x] - 1);
	}
	for(auto v : adjj[u]) gao(v);
	modify(l[u], -1);
}
int main() {
	scanf("%s", str);
	ac.init();
	ac.insert(str, strlen(str));
	ac.build();
	for(int i = 2; i < ac.cnt_node; i++) {
		adj[ac.t[i].fail].push_back(i);
		adjj[ac.t[i].par].push_back(i);
	}
	dfs(1);
	int m; scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		query[ac.idx[y]].push_back({ac.idx[x], i});
	}
	gao(1);
	for(int i = 0; i < m; i++) printf("%d\n", ans[i]);
	return 0;
}
