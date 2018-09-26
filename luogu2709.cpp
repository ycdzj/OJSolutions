#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 50000 + 5;
int cnt[MAXN];
long long cur_ans;
void ins(int val) {
	cur_ans -= (long long)cnt[val] * cnt[val];
	cnt[val]++;
	cur_ans += (long long)cnt[val] * cnt[val];
}
void del(int val) {
	cur_ans -= (long long)cnt[val] * cnt[val];
	cnt[val]--;
	cur_ans += (long long)cnt[val] * cnt[val];
}
int a[MAXN], n, m, k;
int cur_l ,cur_r;
void sync(int l, int r) {
	while(cur_r < r) ins(a[++cur_r]);
	while(l < cur_l) ins(a[--cur_l]);
	while(r < cur_r) del(a[cur_r--]);
	while(cur_l < l) del(a[cur_l++]);
}
struct Query {
	int l, r, idx;
} q[MAXN];
int sq;
bool cmp(const Query &x, const Query &y) {
	int tx = x.l / sq, ty = y.l / sq;
	if(tx != ty) return tx < ty;
	return x.r < y.r;
}
long long ans[MAXN];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].idx = i;
	}
	sq = sqrt(n);
	std::sort(q, q + m, cmp);
	cur_r = 0; cur_l = 1;
	for(int i = 0; i < m; i++) {
		sync(q[i].l, q[i].r);
		ans[q[i].idx] = cur_ans;
	}
	for(int i = 0; i < m; i++) printf("%lld\n", ans[i]);
	return 0;
}