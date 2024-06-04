#include <cstdio>
const int MAXN = 3e5 + 5;
int n, m;
long long a[MAXN], b[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	scanf("%d", &m);
	for(int i = 0; i < m; i++) scanf("%lld", &b[i]);
	int ans = 0;
	int p = 0, q = 0;
	while(p < n && q < m) {
		if(a[p] == b[q]) p++, q++, ans++;
		else if(a[p] < b[q]) {
			a[p + 1] += a[p];
			p++;

		}
		else {
			b[q + 1] += b[q];
			q++;
		}
	}
	if(p < n || q < m) ans = -1;
	printf("%d\n", ans);
	return 0;
}