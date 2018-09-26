#include <cstdio>
#include <algorithm>
#include <cmath>

const int MAXN = 50000 + 5;
struct Modi {
	int time, p, val, pre;
} modi[MAXN];
int cnt_m;
struct Query {
	int time, l, r;
} query[MAXN];
int cnt_q;
int n, m;
int a[MAXN], cnt[1000006];
int cur_l, cur_r, cur_t, ans;
void sync(int l, int r, int t) {
	while(modi[cur_t].time < t) {
		modi[cur_t].pre = a[modi[cur_t].p];
		a[modi[cur_t].p] = modi[cur_t].val;
		if(cur_l <= modi[cur_t].p && modi[cur_t].p <= cur_r) {
			if(--cnt[modi[cur_t].pre] == 0) ans--;
			if(++cnt[modi[cur_t].val] == 1) ans++;
		}
		cur_t++;
	}
	while(cur_t > 0 && modi[cur_t - 1].time >= t) {
		--cur_t;
		a[modi[cur_t].p] = modi[cur_t].pre;
		if(cur_l <= modi[cur_t].p && modi[cur_t].p <= cur_r) {
			if(--cnt[modi[cur_t].val] == 0) ans--;
			if(++cnt[modi[cur_t].pre] == 1) ans++;
		}
	}
	while(cur_r < r) {
		++cur_r;
		if(++cnt[a[cur_r]] == 1) ans++;
	}
	while(cur_l > l) {
		--cur_l;
		if(++cnt[a[cur_l]] == 1) ans++;
	}
	while(cur_r > r) {
		if(--cnt[a[cur_r]] == 0) ans--;
		--cur_r;
	}
	while(cur_l < l) {
		if(--cnt[a[cur_l]] == 0) ans--;
		++cur_l;
	}
}
int sq;
bool cmp(const Query &x, const Query &y) {
	int tx = x.l / sq, ty = y.l / sq;
	if(tx != ty) return tx < ty;
	tx = x.r / sq; ty = y.r / sq;
	if(tx != ty) return tx < ty;
	return x.time < y.time;
}
int ans_[MAXN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) {
		char buf[15]; int a, b;
		scanf("%s%d%d", buf, &a, &b);
		if(buf[0] == 'R') modi[cnt_m++] = {i, a, b, 0}, ans_[i] = -1;
		else query[cnt_q++] = {i, a, b};
	}
	modi[cnt_m++].time = m;
	cur_r = -1;
	sq = pow(n, 2.0 / 3);
	std::sort(query, query + cnt_q, cmp);
	for(int i = 0; i < cnt_q; i++) {
		sync(query[i].l, query[i].r, query[i].time);
		ans_[query[i].time] = ans;
	}
	for(int i = 0; i < m; i++) if(ans_[i] != -1) printf("%d\n", ans_[i]);
	return 0;
}