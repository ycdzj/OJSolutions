#include <cstdio>
#include <cmath>
#include <bitset>
#include <algorithm>

using namespace std;
const int MAXN = 100000 + 5;
struct Query {
	int op, l, r, x, idx;
} q[MAXN];
int sq;
bool cmp(const Query &x, const Query &y) {
	int tx = x.l / sq, ty = y.l / sq;
	if(tx != ty) return tx < ty;
	return x.r < y.r;
}
bitset<MAXN + 5> vis, rev_vis;
int cnt[MAXN];
void ins(int val) {
	if(cnt[val]++ == 0) vis.set(val), rev_vis.set(MAXN - val);
}
void del(int val) {
	if(--cnt[val] == 0) vis.reset(val), rev_vis.reset(MAXN - val);
}
int n, m, a[MAXN];
int cur_l, cur_r;
void sync(int l, int r) {
	while(cur_r < r) ins(a[++cur_r]);
	while(l < cur_l) ins(a[--cur_l]);
	while(r < cur_r) del(a[cur_r--]);
	while(cur_l < l) del(a[cur_l++]);
}
int ans[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) {
		scanf("%d%d%d%d", &q[i].op, &q[i].l, &q[i].r, &q[i].x);
		q[i].idx = i;
	}
	sq = sqrt(n);
	std::sort(q, q + m, cmp);
	cur_l = 1; cur_r = 0;
	for(int i = 0; i < m; i++) {
		sync(q[i].l, q[i].r);
		if(q[i].op == 1) ans[q[i].idx] = (vis & (vis << q[i].x)).any();
		else if(q[i].op == 2) ans[q[i].idx] = (rev_vis & (vis << (MAXN - q[i].x))).any();
		else if(q[i].op == 3) {
			for(int j = 1; (long long)j * j <= q[i].x; j++) if(q[i].x % j == 0) {
				if(vis.test(j) && vis.test(q[i].x / j)) {
					ans[q[i].idx] = true;
					break;
				}
			}
		}
	}
	for(int i = 0; i < m; i++) printf("%s\n", ans[i] ? "hana" : "bi");
	return 0;
}