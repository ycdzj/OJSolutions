#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
char s[155][75];
struct ACA {
	static const int MAXN = 1e5 + 5;
	struct Node {
		int next[26], fail;
		int cnt;
		std::vector<int> idx, adj;
		void init() {
			memset(next, 0, sizeof(next));
			fail = cnt = 0;
			idx.clear();
			adj.clear();
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
	void insert(char *str, int len, int id) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].next[str[i] - 'a'] == 0) {
				t[cur].next[str[i] - 'a'] = new_node();
				t[cur].adj.push_back(t[cur].next[str[i] - 'a']);
			}
			cur = t[cur].next[str[i] - 'a'];
		}
		t[cur].idx.push_back(id);
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
	void dfs(int u) {
		for(int i = 0; i < t[u].adj.size(); i++) {
			dfs(t[u].adj[i]);
		}
		t[t[u].fail].cnt += t[u].cnt;
	}
	void query(char *str, int len) {
		int cur = root;
		for(int i = 0; i < len; i++) {
			cur = t[cur].next[str[i] - 'a'];
			t[cur].cnt++;
		}
		dfs(root);
		int max_ = 0;
		for(int i = 1; i < cnt_node; i++) if(!t[i].idx.empty()) max_ = std::max(max_, t[i].cnt);
		std::vector<int> ans;
		for(int i = 1; i < cnt_node; i++) if(t[i].cnt == max_) {
				for(auto v : t[i].idx) ans.push_back(v);
			}
		std::sort(ans.begin(), ans.end());
		printf("%d\n", max_);
		for(int i = 0; i < ans.size(); i++) printf("%s\n", s[ans[i]]);
	}
} ac;
const int MAXN = 1e6 + 5;
int n;
char str[MAXN];
int main() {
	while(scanf("%d", &n) != EOF) {
		if(n == 0) break;
		ac.init();
		for(int i = 0; i < n; i++) {
			scanf("%s", s[i]);
			ac.insert(s[i], strlen(s[i]), i);
		}
		ac.build();
		scanf("%s", str);
		ac.query(str, strlen(str));
	}
	return 0;
}
