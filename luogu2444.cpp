#include <cstdio>
#include <cstring>
#include <queue>
const int MAXN = 30000 + 5;
struct ACA {
	struct Node {
		int next[2], adj[2], fail;
		int end, clr;
		void init() {
			memset(next, 0, sizeof(next));
			memset(adj, 0, sizeof(adj));
			fail = end = 0;
			clr = 0;
		}
	} t[MAXN];
	int cnt_node;
	int new_node() {
		t[cnt_node].init();
		return cnt_node++;
	}

	int root;
	void init() {
		cnt_node = 1;
		root = new_node();
	}
	void insert(char *str, int len) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].next[str[i] - '0'] == 0) {
				t[cur].adj[str[i] - '0'] = t[cur].next[str[i] - '0'] = new_node();
			}
			cur = t[cur].next[str[i] - '0'];
		}
		t[cur].end++;
	}
	void build() {
		std::queue<int> que;
		t[root].fail = root;
		for(int i = 0; i < 2; i++) {
			if(t[root].next[i] == 0) t[root].next[i] = root;
			else {
				t[t[root].next[i]].fail = root;
				que.push(t[root].next[i]);
			}
		}
		while(!que.empty()) {
			int u = que.front(); que.pop();
			for(int i = 0; i < 2; i++) {
				if(t[u].next[i] == 0) t[u].next[i] = t[t[u].fail].next[i];
				else {
					t[t[u].next[i]].fail = t[t[u].fail].next[i];
					que.push(t[u].next[i]);
				}
			}
		}
	}
	void gao() {
		std::queue<int> que;
		que.push(root);
		while(!que.empty()) {
			int u = que.front(); que.pop();
			if(t[t[u].fail].end) t[u].end = true;
			if(t[u].adj[0]) que.push(t[u].adj[0]);
			if(t[u].adj[1]) que.push(t[u].adj[1]);
		}
	}
	bool dfs(int u) {
		t[u].clr = 1;
		for(int i = 0; i < 2; i++) if(t[t[u].next[i]].end == 0) {
			int v = t[u].next[i];
			if(t[v].clr == 0) {
				if(!dfs(v)) return false;
			}
			else if(t[v].clr == 1) {
				return false;
			}
		}
		t[u].clr = 2;
		return true;
	}
} ac;
char str[MAXN];
int main() {
	int n; scanf("%d", &n);
	ac.init();
	for(int i = 0; i < n; i++) {
		scanf("%s", str);
		ac.insert(str, strlen(str));
	}
	ac.build();
	ac.gao();
	if(!ac.dfs(ac.root)) printf("TAK\n");
	else printf("NIE\n");
	return 0;
}
