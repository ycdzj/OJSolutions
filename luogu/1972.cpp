#include <cstdio>
#include <algorithm>
const int MAXN = 500000 + 5;
const int MAXL = 1000000 + 5;
struct Query {
	int l, r, idx;
} q[MAXN];
bool cmp(const Query &x, const Query &y) {
	if(x.l != y.l) return x.l < y.l;
	return x.r < y.r;
}
int pre[MAXL], a[MAXN], n, m;
int tree[MAXN];
inline int lowbit(int x) { return x & (-x); }
void modify(int p, int val) {
	while(p <= n) {
		tree[p] += val;
		p += lowbit(p);
	}
}
int query(int p) {
	int res = 0;
	while(p >= 1) {
		res += tree[p];
		p -= lowbit(p);
	}
	return res;
}
int ans[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].idx = i;
	}
	std::sort(q, q + m, cmp);
	int l = n + 1;
	for(int i = m - 1; i >= 0; i--) {
		while(l > q[i].l) {
			l--;
			if(pre[a[l]] != 0) modify(pre[a[l]], -1);
			pre[a[l]] = l;
			modify(l, 1);
		}
		ans[q[i].idx] = query(q[i].r);
	}
	for(int i = 0; i < m; i++) printf("%d\n", ans[i]);
	return 0;
}