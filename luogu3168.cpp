#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 5;
struct PSGT {
	struct Node {
		long long sum;
		int cnt;
		int lc, rc;
	} tree[MAXN * 100];
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
			tree[root].cnt = 0;
		}
		else {
			int mid = (l + r) / 2;
			int lc = build(l, mid), rc = build(mid + 1, r);
			tree[root].lc = lc;
			tree[root].rc = rc;
			tree[root].sum = tree[lc].sum + tree[rc].sum;
			tree[root].cnt = tree[lc].cnt + tree[rc].cnt;
		}
		return root;
	}
	long long query(int root, int left, int right, int l, int r) {
		if(l <= left && right <= r) return tree[root].sum;
		if(r < left || right < l) return 0;
		int mid = (left + right) / 2;
		return query(tree[root].lc, left, mid, l, r) + query(tree[root].rc, mid + 1, right, l, r);
	}
	int modify(int root, int left, int right, int p, int val) {
		int res = copy_of(root);
		if(left == p && right == p) {
			tree[res].sum += val;
			if(tree[res].sum == 0) tree[res].cnt = 0;
			else tree[res].cnt = 1;
		}
		else {
			int mid = (left + right) / 2;
			if(p <= mid) tree[res].lc = modify(tree[root].lc, left, mid, p, val);
			else tree[res].rc = modify(tree[root].rc, mid + 1, right, p, val);
			tree[res].sum = tree[tree[res].lc].sum + tree[tree[res].rc].sum;
			tree[res].cnt = tree[tree[res].lc].cnt + tree[tree[res].rc].cnt;
		}
		return res;
	}
} psgt;
int n, m;
vector<int> ins[MAXN], rem[MAXN];
int val[MAXN], idx[MAXN];
int buf[MAXN];
int root[MAXN];
bool cmp(int x, int y) { return val[x] < val[y]; }
int main() {
	scanf("%d%d", &m, &n);
	int max_e = 0;
	for(int i = 0; i < m; i++) {
		int s, e, p; scanf("%d%d%d", &s, &e, &p);
		max_e = max(max_e, e + 1);
		ins[s].push_back(i);
		rem[e + 1].push_back(i);
		val[i] = p;
		buf[i] = i;
	}
	sort(buf, buf + m, cmp);
	for(int i = 0; i < m; i++) idx[buf[i]] = i;
	psgt.init();
	root[0] = psgt.build(0, m - 1);
	for(int i = 1; i <= max_e; i++) {
		root[i] = root[i - 1];
		for(auto v : ins[i]) root[i] = psgt.modify(root[i], 0, m - 1, idx[v], val[v]);
		for(auto v : rem[i]) root[i] = psgt.modify(root[i], 0, m - 1, idx[v], -val[v]);
	}
	long long pre = 1;
	while(n--) {
		int x, a, b, c; scanf("%d%d%d%d", &x, &a, &b, &c);
		pre %= c;
		long long k = 1 + (a * pre + b) % c;
		int left = 0, right = m - 1, rt = root[x];
		while(left < right) {
			int mid = left + (right - left) / 2;
			if(psgt.tree[psgt.tree[rt].lc].cnt >= k) {
				right = mid;
				rt = psgt.tree[rt].lc;
			}
			else {
				k -= psgt.tree[psgt.tree[rt].lc].cnt;
				left = mid + 1;
				rt = psgt.tree[rt].rc;
			}
		}
		pre = psgt.query(root[x], 0, m - 1, 0, left);
		printf("%lld\n", pre);
	}
	return 0;
}