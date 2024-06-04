#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 1e5 + 5;
struct BIT {
	int tree[MAXN], time[MAXN], n, clk;
	void update(int p) {
		if(time[p] != clk) {
			tree[p] = 0;
			time[p] = clk;
		}
	}
	int lowbit(int x) { return x & (-x); }
	void modify(int p, int val) {
		while(p <= n) {
			update(p);
			tree[p] += val;
			p += lowbit(p);
		}
	}
	int query(int p) {
		int res = 0;
		while(p >= 1) {
			update(p);
			res += tree[p];
			p -= lowbit(p);
		}
		return res;
	}
} bit;
struct Query { int idx, op, p, val; } query[MAXN * 3], buf[MAXN * 3];
bool cmp(const Query &x, const Query &y) {
	if(x.p != y.p) return x.p > y.p;
	return x.op < y.op;
}
bool cmp2(const Query &x, const Query &y) {
	if(x.p != y.p) return x.p < y.p;
	return x.op < y.op;
}
int n, m;
long long ans[MAXN];
void solve(int l, int r) {
	if(l == r) return;
	int mid = (l + r) / 2;
	solve(l, mid); solve(mid + 1, r);
	int i = l, j = mid + 1;
	bit.clk++;
	int cnt = 0;
	while(i <= mid || j <= r) {
		if(i <= mid && (j > r || cmp(query[i], query[j]))) {
			if(query[i].op == 1) bit.modify(query[i].val, 1);
			buf[cnt++] = query[i];
			i++;
		}
		else {
			if(query[j].op == 2) ans[query[j].idx] += bit.query(query[j].val - 1);
			buf[cnt++] = query[j];
			j++;
		}
	}
	for(int i = 0; i < cnt; i++) query[l + i] = buf[i];
}
void solve2(int l, int r) {
	if(l == r) return;
	int mid = (l + r) / 2;
	solve2(l, mid); solve2(mid + 1, r);
	int i = l, j = mid + 1;
	bit.clk++;
	int cnt = 0;
	while(i <= mid || j <= r) {
		if(i <= mid && (j > r || cmp2(query[i], query[j]))) {
			if(query[i].op == 1) bit.modify(query[i].val, 1);
			buf[cnt++] = query[i];
			i++;
		}
		else {
			if(query[j].op == 2) ans[query[j].idx] += bit.query(n) - bit.query(query[j].val);
			buf[cnt++] = query[j];
			j++;
		}
	}
	for(int i = 0; i < cnt; i++) query[l + i] = buf[i];
}
int pos[MAXN], a[MAXN], b[MAXN];
bool vis[MAXN];
int build_query() {
	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < n; i++) pos[a[i]] = i;
	for(int i = 0; i < m; i++) vis[pos[b[i]]] = true;
	int cnt = 0;
	for(int i = 0; i < n; i++) if(!vis[i]) {
		query[cnt++] = { -1, 1, i, a[i] };
	}
	for(int i = m - 1; i >= 0; i--) {
		query[cnt++] = { i, 2, pos[b[i]], b[i] };
		query[cnt++] = { -1, 1, pos[b[i]], b[i] };
	}
	bit.n = n;
	return cnt;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) scanf("%d", &b[i]);
	int cnt = build_query();
	solve(0, cnt - 1);
	cnt = build_query();
	solve2(0, cnt - 1);
	bit.clk++;
	long long cur = 0;
	for(int i = n - 1; i >= 0; i--) {
		cur += bit.query(a[i] - 1);
		bit.modify(a[i], 1);
	}
	for(int i = 0; i < m; i++) {
		printf("%lld\n", cur);
		cur -= ans[i];
	}
	return 0;
}
