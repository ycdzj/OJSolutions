#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 1e6 + 5;
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
char str[MAXN];
int sa[MAXN], rank[MAXN];
int a[MAXN];
int main() {
	scanf("%s", str);
	int len = strlen(str);
	for(int i = 0; i < len; i++) a[i] = str[i];
	da(a, sa, rank, len, 128);
	for(int i = 0; i < len; i++) printf("%d%c", sa[i] + 1, (i + 1 < len) ? ' ' : '\n');
	return 0;
}