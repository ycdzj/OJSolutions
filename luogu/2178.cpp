#include <cstdio>
#include <algorithm>
const int MAXN = 3e5 + 5;
typedef long long ll;
void count(int *a, int *b, int *val, int n, int m) {//[0, n) [0, m]
	static int cnt[MAXN];
	for(int i = 0; i <= m; i++) cnt[i] = 0;
	for(int i = 0; i < n; i++) cnt[val[a[i]]]++;
	for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for(int i = n - 1; i >= 0; i--) b[--cnt[val[a[i]]]] = a[i];
}
void da(char *str, int *sa, int *rank, int n, int m) {
	static int sa_[MAXN];
	for(int i = 0; i < n; i++) sa_[i] = i;
	for(int i = 0; i < n; i++) rank[i] = str[i];
	count(sa_, sa, rank, n, m);
	for(int k = 0; (1 << k) < n; k++) {
		int l = (1 << k), p = 0;
		for(int i = n - l; i < n; i++) sa_[p++] = i;
		for(int i = 0; i < n; i++) if(sa[i] >= l) sa_[p++] = sa[i] - l;
		count(sa_, sa, rank, n, m);
		int *rank_ = sa_;
		m = 0;
		for(int i = 0; i < n; i++) {
			if(i > 0) {
				if(rank[sa[i]] != rank[sa[i - 1]]) m++;
				else if(sa[i - 1] + l >= n) m++;
				else if(rank[sa[i] + l] != rank[sa[i - 1] + l]) m++;
			}
			rank_[sa[i]] = m;
		}
		for(int i = 0; i < n; i++) rank[i] = rank_[i];
		if(m >= n - 1) break;
	}
}
void calc_height(char *str, int *sa, int *rank, int *height, int n) {
	for(int i = 0; i < n; i++) rank[sa[i]] = i;
	height[0] = 0;
	for(int i = 0, k = 0; i < n; i++) {
		if(k > 0) k--;
		if(rank[i] != 0) {
			while(str[i + k] == str[sa[rank[i] - 1] + k]) k++;
			height[rank[i]] = k;
		}
	}
}
ll a[MAXN];
int n, sa[MAXN], rank[MAXN], height[MAXN];
char s[MAXN];

int f[MAXN];
ll min_[MAXN], max_[MAXN], cnt[MAXN];
int find(int x) {
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
long long cur_cnt, cur_val;
void merge(int x, int y) {
	x = find(x); y = find(y);
	if(x != y) {
		if(x < y) std::swap(x, y);
		f[x] = y;

		cur_val = std::max(cur_val, max_[x] * max_[y]);
		cur_val = std::max(cur_val, min_[x] * min_[y]);
		max_[y] = std::max(max_[y], max_[x]);
		min_[y] = std::min(min_[y], min_[x]);

		cur_val = std::max(cur_val, a[sa[y - 1]] * min_[y]);
		cur_val = std::max(cur_val, a[sa[y - 1]] * max_[y]);

		cur_cnt += cnt[x] * cnt[y];
		cnt[y] += cnt[x];
	}
}
struct Item {
	int val, idx;
} que1[MAXN], que2[MAXN];
bool operator < (const Item &x, const Item &y) {
	return x.val < y.val;
}
long long ans_cnt[MAXN], ans_val[MAXN];
int main() {
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	da(s, sa, rank, n, 128);
	calc_height(s, sa, rank, height, n);
	int cnt1 = 0, cnt2 = 0;
	for(int i = 1; i < n - 1; i++) que1[cnt1++] = (Item){std::min(height[i], height[i + 1]), i};
	for(int i = 1; i < n; i++) que2[cnt2++] = (Item){height[i], i};
	std::sort(que1, que1 + cnt1);
	std::sort(que2, que2 + cnt2);
	for(int i = 0; i < n; i++) {
		f[i] = i;
		cnt[i] = 1;
		min_[i] = max_[i] = a[sa[i]];
	}
	cur_cnt = 0; cur_val = -1e18;
	for(int x = n - 1; x >= 0; x--) {
		while(cnt2 > 0 && que2[cnt2 - 1].val >= x) {
			int id = que2[--cnt2].idx;
			cur_cnt++;
			cur_val = std::max(cur_val, a[sa[id]] * a[sa[id - 1]]);
		}
		while(cnt1 > 0 && que1[cnt1 - 1].val >= x) {
			--cnt1;
			merge(que1[cnt1].idx, que1[cnt1].idx + 1);
		}
		ans_cnt[x] = cur_cnt;
		ans_val[x] = cur_cnt > 0 ? cur_val : 0;
	}
	for(int i = 0; i < n; i++) printf("%lld %lld\n", ans_cnt[i], ans_val[i]);
	return 0;
}