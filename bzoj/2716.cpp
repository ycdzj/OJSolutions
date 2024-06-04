#include <cstdio>
#include <algorithm>
const int MAXN = 5e5 + 5;
const int MAXM = 1e6 + 15;
struct BIT {
	int tree[MAXM], time[MAXM], clk;
	int lowbit(int x) { return x & (-x); }
	void update(int p) {
		if(time[p] != clk) {
			tree[p] = -MAXM * 2;
			time[p] = clk;
		}
	}
	void modify(int p, int val) {
		while(p < MAXM) {
			update(p);
			tree[p] = std::max(tree[p], val);
			p += lowbit(p);
		}
	}
	int query(int p) {
		int res = -MAXM * 2;
		while(p >= 1) {
			update(p);
			res = std::max(res, tree[p]);
			p -= lowbit(p);
		}
		return res;
	}
} bit;
struct Query {
	int t, x, y;
	int ans;
} query[MAXN * 2];
int n, m;
int buf[MAXN * 2], buff[MAXN * 2];
bool cmp(int a, int b) {
	if(query[a].x != query[b].x) return query[a].x < query[b].x;
	if(query[a].y != query[b].y) return query[a].y < query[b].y;
	return query[a].t < query[b].t;
}
void solve(int l, int r) {
	if(l < r) {
		int mid = (l + r) / 2;
		solve(l, mid);
		solve(mid + 1, r);

		bit.clk++;
		int cnt_buf = 0;
		for(int i = l, j = mid + 1; i <= mid || j <= r; ) {
			if(i <= mid && (j > r || cmp(buf[i], buf[j]))) {
				buff[cnt_buf++] = buf[i];
				if(query[buf[i]].t == 1) bit.modify(query[buf[i]].y, query[buf[i]].y + query[buf[i]].x);
				i++;
			}
			else {
				buff[cnt_buf++] = buf[j];
				if(query[buf[j]].t == 2) query[buf[j]].ans = std::min(query[buf[j]].ans, query[buf[j]].x + query[buf[j]].y - bit.query(query[buf[j]].y));
				j++;
			}
		}
		for(int i = 0; i < cnt_buf; i++) buf[l + i] = buff[i];
	}
}
int main() {
	//freopen("input", "r", stdin);
	//freopen("outp", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &query[i].x, &query[i].y);
		query[i].t = 1;
	}
	for(int i = n; i < n + m; i++) scanf("%d%d%d", &query[i].t, &query[i].x, &query[i].y);
	for(int i = 0; i < n + m; i++) {
		++query[i].x; ++query[i].y;
		query[i].ans = MAXM * 2;
		buf[i] = i;
	}

	solve(0, n + m - 1);
	for(int i = 0; i < n + m; i++) {
		query[i].x = MAXM - 5 - query[i].x;
		buf[i] = i;
	}
	solve(0, n + m - 1);
	for(int i = 0; i < n + m; i++) {
		query[i].y = MAXM - 5 - query[i].y;
		buf[i] = i;
	}
	solve(0, n + m - 1);
	for(int i = 0; i < n + m; i++) {
		query[i].x = MAXM - 5 - query[i].x;
		buf[i] = i;
	}
	solve(0, n + m - 1);
	for(int i = n; i < n + m; i++) if(query[i].t == 2) printf("%d\n", query[i].ans);
	return 0;
}
