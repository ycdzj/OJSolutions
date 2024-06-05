#include <cstdio>
#include <algorithm>
int n, w, a[20], cur[20];
int ans;
void dfs(int i, int cnt) {
	if(cnt >= ans) return;
	if(i == -1) {
		ans = cnt;
	}
	else {
		for(int j = 0; j < cnt; j++) if(cur[j] + a[i] <= w) {
			cur[j] += a[i];
			dfs(i - 1, cnt);
			cur[j] -= a[i];
		}
		cur[cnt] += a[i];
		dfs(i - 1, cnt + 1);
		cur[cnt] -= a[i];
	}
}
int main() {
	scanf("%d%d", &n, &w);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	std::sort(a, a + n);
	ans = n;
	dfs(n - 1, 0);
	printf("%d\n", ans);
	return 0;
}
