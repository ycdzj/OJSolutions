#include <cstdio>
#include <algorithm>
void prime(int a[], int n) {
	for(int i = 1; i <= n; i++) a[i] = i;
	for(int i = 2; (long long)i * i <= n; i++) if(a[i] == i) {
		for(int j = i * i; j <= n; j += i) a[j] = std::min(a[j], i);
	}
}
int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
const int MAXP = 1.5e7 + 10;
const int MAXN = 3e5 + 5;
int p[MAXP];
int cnt[MAXP];
int n, a[MAXN];
int main() {
	prime(p, MAXP - 1);
	scanf("%d", &n);
	int g = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		g = gcd(g, a[i]);
	}
	for(int i = 0; i < n; i++) a[i] /= g;
	for(int i = 0; i < n; i++) {
		int pre = -1;
		for(int x = a[i]; x > 1; ) {
			int cur = p[x];
			x /= cur;
			if(cur == pre) continue;
			cnt[cur]++;
			pre = cur;
		}
	}
	int ans = 0;
	for(int i = 2; i < MAXP; i++) ans = std::max(ans, cnt[i]);
	if(ans == 0) printf("-1\n");
	else printf("%d\n", n - ans);
	return 0;
}