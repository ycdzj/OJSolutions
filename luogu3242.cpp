#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 4e4 + 5;
struct Bit {
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
struct Query {
	int idx, op;
	int x, y1, y2, k;
} query[MAXN * 5], bufl[MAXN * 5], bufr[MAXN * 5];
int ans[MAXN];
void solve(int lval, int rval, int s, int t) {
	if(lval == rval) {
		for(int i = s; i <= t; i++)
			if(query[i].op == 2)
				ans[query[i].idx] = lval;
	}
	else if(s <= t) {
		int mid = lval + (rval - lval) / 2;
		int nl = 0, nr = 0;
		bit.clk++;
		for(int i = s; i <= t; i++) {
			if(query[i].op == 2) {
				int cnt = bit.query(query[i].y1);
				if(cnt>= query[i].k) bufl[nl++] = query[i];
				else {
					query[i].k -= cnt;
					bufr[nr++] = query[i];
				}
			}
			else if(query[i].k <= mid) {
				if(query[i].op == 1) {
					bit.modify(query[i].y1, 1);
					bit.modify(query[i].y2 + 1, -1);
				}
				else {
					bit.modify(query[i].y1, -1);
					bit.modify(query[i].y2 + 1, 1);
				}
				bufl[nl++] = query[i];
			}
			else {
				bufr[nr++] = query[i];
			}
		}
		for(int i = 0; i < nl; i++) query[s + i] = bufl[i];
		for(int i = 0; i < nr; i++) query[s + nl + i] = bufr[i];
		solve(lval, mid, s, s + nl - 1);
		solve(mid + 1, rval, s + nl, s + nl + nr - 1);
	}
}
int l[MAXN], r[MAXN], clk;
int n, p, q;
vector<int> adj[MAXN];
int fa[MAXN][20], dep[MAXN];
void dfs(int u, int pre) {
	l[u] = ++clk;
	fa[u][0] = pre;
	dep[u] = dep[pre] + 1;
	for(auto v : adj[u]) if(v != pre) dfs(v, u);
	r[u] = clk;
}
bool check(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	int d = dep[y] - dep[x];
	for(int i = 0; i < 20; i++) if(d >> i & 1) y = fa[y][i];
	return x == y;
}
int get(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	int d = dep[y] - dep[x] - 1;
	for(int i = 0; i < 20; i++) if(d >> i & 1) y = fa[y][i];
	return y;
}
bool cmp(const Query &x, const Query &y) {
	if(x.x != y.x) return x.x < y.x;
	return x.op < y.op;
}
int main() {
	scanf("%d%d%d", &n, &p, &q);
	for(int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 1);
	bit.n = clk;
	for(int i = 1; i < 20; i++) {
		for(int u = 1; u <= n; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	int cnt_q = 0;
	for(int i = 0; i < p; i++) {
		int u, v, k; scanf("%d%d%d", &u, &v, &k);
		if(check(u, v)) {
			if(dep[u] > dep[v]) swap(u, v);
			u = get(u, v);
			if(1 <= l[u] - 1) {
				query[cnt_q++] = { -1, 1, 1, l[v], r[v], k};
				query[cnt_q++] = { -1, -1, l[u], l[v], r[v], k};
			}
			if(r[u] + 1 <= clk) {
				query[cnt_q++] = { -1, 1, l[v], r[u] + 1, clk, k };
				query[cnt_q++] = { -1, -1, r[v] + 1, r[u] + 1, clk, k };
			}
		}
		else {
			if(l[u] > l[v]) swap(u, v);
			query[cnt_q++] = { -1, 1, l[u], l[v], r[v], k };
			query[cnt_q++] = { -1, -1, r[u] + 1, l[v], r[v], k };
		}
	}
	for(int i = 0; i < q; i++) {
		int u, v, k; scanf("%d%d%d", &u, &v, &k);
		if(l[u] > l[v]) swap(u, v);
		query[cnt_q++] = { i, 2, l[u], l[v], -1, k };
	}
	sort(query, query + cnt_q, cmp);
	solve(0, 1e9, 0, cnt_q - 1);
	for(int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}