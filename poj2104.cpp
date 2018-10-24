#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 2e5 + 5;
const int INF = 1e9 + 5;
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
struct Query { int idx, op, l, r, k; } q[MAXN];
int n, m, ans[MAXN];
Query bufl[MAXN], bufr[MAXN];
void solve(int lval, int rval, int s, int t) {
	if(s > t) return;
	if(lval == rval) {
		for(int i = s; i <= t; i++) if(q[i].op == 2) ans[q[i].idx] = lval;
		return;
	}
	int mid = lval + (rval - lval) / 2;
	int nl = 0, nr = 0;
	bit.clk++;
	for(int i = s; i <= t; i++) {
		if(q[i].op == 1) {
			if(q[i].k <= mid) {
				bit.modify(q[i].l, 1);
				bufl[nl++] = q[i];
			}
			else {
				bufr[nr++] = q[i];
			}
		}
		else {
			int cnt = bit.query(q[i].r) - bit.query(q[i].l - 1);
			if(cnt >= q[i].k) {
				bufl[nl++] = q[i];
			}
			else {
				q[i].k -= cnt;
				bufr[nr++] = q[i];
			}
		}
	}
	for(int i = 0; i < nl; i++) q[s + i] = bufl[i];
	for(int i = 0; i < nr; i++) q[s + nl + i] = bufr[i];
	solve(lval, mid, s, s + nl - 1);
	solve(mid + 1, rval, s + nl, s + nl + nr - 1);
}
int main() {
	scanf("%d%d", &n, &m);
	bit.n = n;
	for(int i = 0; i < n; i++) {
		int a; scanf("%d", &a);
		q[i].op = 1;
		q[i].l = i + 1;
		q[i].k = a;
	}
	for(int i = n; i < n + m; i++) {
		int l, r, k; scanf("%d%d%d", &l, &r, &k);
		q[i].idx = i - n;
		q[i].op = 2;
		q[i].l = l;
		q[i].r = r;
		q[i].k = k;
	}
	solve(-INF, INF, 0, n + m - 1);
	for(int i = 0; i < m; i++) printf("%d\n", ans[i]);
	return 0;
}