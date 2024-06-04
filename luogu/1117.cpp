#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 3e4 + 5;
const int INF = 1e9 + 5;
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
int lg[MAXN];
struct Worker {
    int sa[MAXN], rank[MAXN], len;
    int st[20][MAXN];
    void build(char *str, int len_) {
    	len = len_;
    	da(str,sa, rank, len, 128);
    	calc_height(str, sa, rank, st[0], len);
    	for(int i = 1; i < 20; i++) {
    		int l = (1 << i), l2 = (1 << (i - 1));
    		for(int j = 0; j + l <= len; j++) {
    			st[i][j] = std::min(st[i - 1][j], st[i - 1][j + l2]);
    		}
    	}
    }
    int lcp(int i, int j) {
    	if(i < 0 || j < 0 || i >= len || j >= len) return 0;
		if(i == j) return INF;
    	i = rank[i]; j = rank[j];
    	if(i > j) std::swap(i, j);
    	int p = lg[j - i];//[i + 1, j]
    	return std::min(st[p][i + 1], st[p][j - (1 << p) + 1]);
    }
};
struct Util {
	Worker cp, cs;
	int len;
	void build(char *str, int len_) {
		len = len_;
		cp.build(str, len);
		std::reverse(str, str + len);
		cs.build(str, len);
	}
	int lcp(int i, int j) { return cp.lcp(i, j); }
	int lcs(int i, int j) { return cs.lcp(len - 1 - j, len - 1 - i); }
} util;
char str[MAXN];
int st[MAXN], ed[MAXN];
int main() {
	for(int i = 0; i < 20 && (1 << i) < MAXN; i++) lg[1 << i] = i;
	for(int i = 1; i < MAXN; i++) {
		int j = (i & (-i));
		if(j != i) lg[i] = lg[i ^ j];
	}
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%s", str);
		int len = strlen(str);
		for(int i = 0; i < len; i++) st[i] = ed[i] = 0;
		util.build(str, len);
		for(int l = 1; l <= len; l++) {
			for(int i = 0, j = l; j < len; i += l, j += l) {
				int x = std::min(util.lcp(i, j), l);
				int y = std::min(util.lcs(i - 1, j - 1), l - 1);
				if(x + y >= l) {
					st[i - y]++;
					st[i + x - l + 1]--;
					ed[j - y + l - 1]++;
					ed[j + x]--;
				}
			}
		}
		for(int i = 1; i < len; i++) st[i] += st[i - 1], ed[i] += ed[i - 1];
		long long ans = 0;
		for(int i = 0; i + 1 < len; i++) ans += (long long)ed[i] * st[i + 1];
		printf("%lld\n", ans);
	}
	return 0;
}