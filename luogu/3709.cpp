#include <cstdio>
#include <cmath>
#include <algorithm>
const int MAXN = 200000 + 5;
int a[MAXN], n, m;
int buf[MAXN], cnt[MAXN], dist[MAXN];
int cur_l, cur_r, cur_ans;
void ins(int val) {
	dist[cnt[val]]--;
	cnt[val]++;
	dist[cnt[val]]++;
	if(cur_ans < cnt[val]) cur_ans = cnt[val];
}
void del(int val) {
	dist[cnt[val]]--;
	cnt[val]--;
	dist[cnt[val]]++;
	if(dist[cur_ans] == 0) cur_ans = cnt[val];
}
void sync(int l, int r) {
	while(cur_r < r) ins(a[++cur_r]);
	while(cur_l > l) ins(a[--cur_l]);
	while(cur_r > r) del(a[cur_r--]);
	while(cur_l < l) del(a[cur_l++]);
}
struct Query {
	int l, r, idx;
} q[MAXN];
int sq;
int ans[MAXN];
bool cmp(const Query &x, const Query &y) {
	int tx = x.l / sq, ty = y.l / sq;
	if(tx != ty) return tx < ty;
	return x.r < y.r;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		buf[i] = a[i];
	}
	std::sort(buf, buf + n);
	for(int i = 0; i < n; i++) a[i] = std::lower_bound(buf, buf + n, a[i]) - buf;
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].idx = i;
	}
	sq = sqrt(n);
	std::sort(q, q + m, cmp);
	dist[0] = n;
	cur_r = -1;
	for(int i = 0; i < m; i++) {
		sync(q[i].l - 1, q[i].r - 1);
		ans[q[i].idx] = cur_ans;
	}
	for(int i = 0; i < m; i++) printf("%d\n", -ans[i]);
	return 0;
}