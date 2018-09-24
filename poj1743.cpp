#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 2e4 + 5;
const int INF = 1e9;
void count(int *a, int *b, int *val, int n, int m) {//[0, n) [0, m]
	static int cnt[MAXN];
	for(int i = 0; i <= m; i++) cnt[i] = 0;
	for(int i = 0; i < n; i++) cnt[val[a[i]]]++;
	for(int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for(int i = n - 1; i >= 0; i--) b[--cnt[val[a[i]]]] = a[i];
}
void da(int *str, int *sa, int *rank, int n, int m) {
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
void calc_height(int *str, int *sa, int *rank, int *height, int n) {
	for(int i = 0; i < n; i++) rank[sa[i]] = i;
	str[n] = -1;
	height[0] = 0;
	for(int i = 0, k = 0; i < n; i++) {
		if(k > 0) k--;
		if(rank[i] != 0) {
			while(str[i + k] == str[sa[rank[i] - 1] + k]) k++;//字符串尾需有结束符
			height[rank[i]] = k;
		}
	}
}
int sa[MAXN], rank[MAXN], height[MAXN];
int str[MAXN], a[MAXN], n;
bool check(int x) {
	for(int i = 0, pre = 0; i <= n - 1; i++) {
		if(i == n - 1 || height[i] < x) {
			int max_ = -INF, min_ = INF;
			for(int j = pre; j < i; j++) {
				max_ = std::max(max_, sa[j]);
				min_ = std::min(min_, sa[j]);
			}
			if(max_ - min_ - 1 >= x) return true;
			pre = i;
		}
	}
	return false;
}
int main() {
	while(scanf("%d", &n) != EOF) {
		if(n == 0) break;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		for(int i = 0; i < n - 1; i++) str[i] = a[i + 1] - a[i] + 100;
		da(str, sa, rank, n - 1, 200);
		calc_height(str, sa, rank, height, n - 1);
		int l = 0, r = n;
		while(l < r) {
			int mid = (l + r + 1) / 2;
			if(check(mid)) l = mid;
			else r = mid - 1;
		}
		int ans = l + 1;
		if(ans < 5) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}
