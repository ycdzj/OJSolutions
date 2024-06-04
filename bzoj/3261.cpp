#include <cstdio>
const int MAXN = (int)3e5 + 5;
struct Node {
	int go[2], max_;
	void init() {
		go[0] = go[1] = max_ = 0;
	}
};
struct PTrie {
	Node t[MAXN * 61];
	int cnt_node;
	int new_node() {
		t[cnt_node].init();
		return cnt_node++;
	}
	int copy_of(int p) {
		t[cnt_node] = t[p];
		return cnt_node++;
	}

	int init() {
		cnt_node = 1;
		return new_node();
	}

	int insert(int root, int *str, int len, int idx) {
		int res = copy_of(root);
		int cur = res;
		t[cur].max_ = idx;
		for(int i = 0; i < len; i++) {
			if(t[cur].go[str[i]]) {
				t[cur].go[str[i]] = copy_of(t[cur].go[str[i]]);
			}
			else {
				t[cur].go[str[i]] = new_node();
			}
			cur = t[cur].go[str[i]];
			t[cur].max_ = idx;
		}
		return res;
	}

	int query(int root, int *str, int len, int l) {
		int res = 0, cur = root;
		for(int i = 0; i < len; i++) {
			if(t[cur].go[str[i] ^ 1] && t[t[cur].go[str[i] ^ 1]].max_ >= l) {
				cur = t[cur].go[str[i] ^ 1];
				res = (res << 1 | 1);
			}
			else {
				cur = t[cur].go[str[i]];
				res = (res << 1);
			}
		}
		return res;
	}
} ptrie;
int n, m;
char str[109];
int root[MAXN * 2], s[MAXN * 2], cnt;
void insert(int x) {
	static int buf[30];
	x ^= s[cnt];
	s[cnt + 1] = x;
	for(int j = 29; j >= 0; j--) {
		buf[j] = (x & 1);
		x >>= 1;
	}
	root[cnt + 1] = ptrie.insert(root[cnt], buf, 30, cnt + 1);
	cnt++;
}
int query(int l, int r, int x) {
	static int buf[30];
	x ^= s[cnt];
	for(int j = 29; j >= 0; j--) {
		buf[j] = (x & 1);
		x >>= 1;
	}
	return ptrie.query(root[r - 1], buf, 30, l - 1);
}
int buf[30];
int main() {
	scanf("%d%d", &n, &m);
	root[0] = ptrie.init();
	root[0] = ptrie.insert(root[0], buf, 30, 0);
	s[0] = 0;
	cnt = 0;
	for(int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		insert(x);
	}
	for(int i = 0; i < m; i++) {
		scanf("%s", str);
		if(str[0] == 'A') {
			int x; scanf("%d", &x);
			insert(x);
		}
		else {
			int l, r, x; scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", query(l, r, x));
		}
	}
	return 0;
}