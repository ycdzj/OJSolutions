#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 8e4 + 5;
struct PSGT {
	struct Node {
		int sum;
		int lc, rc;
	} tree[MAXN * 60];
	int cnt_node;
	int copy_of(int u) {
		tree[cnt_node] = tree[u];
		return cnt_node++;
	}
	void init() {
		cnt_node = 1;
	}
	int build(int l, int r) {
		int root = cnt_node++;
		if(l == r) {
			tree[root].lc = tree[root].rc = -1;
			tree[root].sum = 0;
		}
		else {
			int mid = (l + r) / 2;
			int lc = build(l, mid), rc = build(mid + 1, r);
			tree[root].lc = lc;
			tree[root].rc = rc;
			tree[root].sum = tree[lc].sum + tree[rc].sum;
		}
		return root;
	}
	int query(int root, int left, int right, int l, int r) {
		if(l <= left && right <= r) return tree[root].sum;
		if(r < left || right < l) return 0;
		int mid = (left + right) / 2;
		return query(tree[root].lc, left, mid, l, r) + query(tree[root].rc, mid + 1, right, l, r);
	}
	int modify(int root, int left, int right, int p, int val) {
		int res = copy_of(root);
		if(left == p && right == p) tree[res].sum += val;
		else {
			int mid = (left + right) / 2;
			if(p <= mid) tree[res].lc = modify(tree[root].lc, left, mid, p, val);
			else tree[res].rc = modify(tree[root].rc, mid + 1, right, p, val);
			tree[res].sum = tree[tree[res].lc].sum + tree[tree[res].rc].sum;
		}
		return res;
	}
} psgt;
int root[MAXN], fa[MAXN][20], dep[MAXN], sz[MAXN];
int buf[MAXN], val[MAXN], cnt_buf;
vector<int> adj[MAXN];
int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	int d = dep[y] - dep[x];
	for(int i = 0; i < 20; i++) if(d >> i & 1) y = fa[y][i];
	if(x == y) return y;
	for(int i = 19; i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i]; y = fa[y][i];
		}
	}
	return fa[x][0];
}
void dfs(int u, int pre) {
	fa[u][0] = pre;
	dep[u] = dep[pre] + 1;
	for(int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	root[u] = psgt.modify(root[pre], 0, cnt_buf - 1, val[u], 1);
	for(auto v : adj[u]) if(v != pre) dfs(v, u);
}
void link(int x, int y) {
	int rx = fa[fa[x][19]][19];
	int ry = fa[fa[y][19]][19];
	if(sz[rx] > sz[ry]) {
		swap(x, y);
		swap(rx, ry);
	}
	adj[x].push_back(y);
	adj[y].push_back(x);
	sz[ry] += sz[rx];
	dfs(x, y);
}
int query(int x, int y, int k) {
	int lc = lca(x, y);
	int rx = root[x], ry = root[y], rl = root[lc];
	int left = 0, right = cnt_buf - 1;
	while(left < right) {
		int mid = (left + right) / 2;
		int lsum = psgt.tree[psgt.tree[rx].lc].sum + psgt.tree[psgt.tree[ry].lc].sum - 2 * psgt.tree[psgt.tree[rl].lc].sum;
		if(left <= val[lc] && val[lc] <= mid) lsum++;
		if(lsum >= k) {
			rx = psgt.tree[rx].lc;
			ry = psgt.tree[ry].lc;
			rl = psgt.tree[rl].lc;
			right = mid;
		}
		else {
			rx = psgt.tree[rx].rc;
			ry = psgt.tree[ry].rc;
			rl = psgt.tree[rl].rc;
			left = mid + 1;
			k -= lsum;
		}
	}
	return left;
}
int testcase, n, m, t;
char str[20];
int main() {
	scanf("%d", &testcase);
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 0; i < n; i++) scanf("%d", &buf[i]), val[i + 1] = buf[i];

	sort(buf, buf + n);
	cnt_buf = unique(buf, buf + n) - buf;

	psgt.init();
	root[0] = psgt.build(0, cnt_buf - 1);
	for(int i = 1; i <= n; i++) {
		val[i] = lower_bound(buf, buf + cnt_buf, val[i]) - buf;
		root[i] = psgt.modify(root[0], 0, cnt_buf - 1, val[i], 1);
		for(int j = 0; j < 20; j++) fa[i][j] = i;
		dep[i] = 0;
		sz[i] = 1;
	}
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		link(x, y);
	}
	int lastans = 0;
	for(int i = 0; i < t; i++) {
		scanf("%s", str);
		if(str[0] == 'Q') {
			int x, y, k; scanf("%d%d%d", &x, &y, &k);
			x ^= lastans; y ^= lastans; k ^= lastans;
			lastans = buf[query(x, y, k)];
			printf("%d\n", lastans);
		}
		else if(str[0] == 'L') {
			int x, y; scanf("%d%d", &x, &y);
			x ^= lastans; y ^= lastans;
			link(x, y);
		}
	}
	return 0;
}