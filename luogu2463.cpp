#include <cstdio>
#include <algorithm>

const int MAXN = 1005;
const int INF = 1e9 + 5;
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
	str[n] = -1; //字符串尾需有结束符
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
int n, len[MAXN];
int str[MAXN][MAXN], buf[MAXN * 2];
int sa[MAXN], rank[MAXN], height[MAXN];
int ans[MAXN], cur[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &len[i]);
		for(int j = 0; j < len[i]; j++) scanf("%d", &str[i][j]);
	}
	for(int i = 0; i < len[0] - 1; i++) ans[i] = len[0] - 1;
	for(int i = 1; i < n; i++) {
		int p = 0;
		for(int j = 0; j + 1 < len[0]; j++) buf[p++] = str[0][j + 1] - str[0][j] + 105;
		int x = p++;
		buf[x] = 0;
		for(int j = 0; j + 1 < len[i]; j++) buf[p++] = str[i][j + 1] - str[i][j] + 105;
		da(buf, sa, rank, p, 210);
		calc_height(buf, sa, rank, height, p);
		for(int j = 0; j < x; j++) cur[j] = 0;
		for(int j = 0, min_ = INF; j < p; j++) {
			if(sa[j] > x) min_ = INF;
			else min_ = std::min(min_, height[j]);
			if(sa[j] < x) cur[sa[j]] = std::max(cur[sa[j]], min_);
		}
		for(int j = p - 1, min_ = 0; j >= 0; j--) {
			if(sa[j] < x) cur[sa[j]] = std::max(cur[sa[j]], min_);
			if(sa[j] > x) min_= height[j];
			else min_ = std::min(min_, height[j]);
		}
		for(int j = 0; j < x; j++) ans[j] = std::min(ans[j], cur[j]);
	}
	int max_ = 0;
	for(int i = 0; i < len[0] - 1; i++) max_ = std::max(max_, ans[i]);
	printf("%d\n", max_ + 1);
	return 0;
}