#include <cstdio>
const int MAXN = 1e5 + 5;
int n, l, a;
int t[MAXN], ll[MAXN];
int main() {
	scanf("%d%d%d", &n, &l, &a);
	for(int i = 1; i <= n; i++) scanf("%d%d", &t[i], &ll[i]);
	t[n + 1] = l;
	int ans = 0;
	for(int i = 0; i <= n; i++) {
		ans += (t[i + 1] - t[i] - ll[i]) / a;
	}
	printf("%d\n", ans);
	return 0;
}