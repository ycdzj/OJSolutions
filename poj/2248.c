#include <cstdio>
int n, d, ans[105];
bool dfs(int k) {
	if(ans[k - 1] == n) return true;
	if(k == d) return false;
	for(int i = k - 1; i >= 0; i--) for(int j = i; j <= k - 1; j++) {
		ans[k] = ans[i] + ans[j];
		if(ans[k - 1] < ans[k] && ans[k] <= n) {
			if(dfs(k + 1)) return true;
		}
	}
	return false;
}
int main() {
	while(scanf("%d", &n) != EOF) {
		if(n == 0) break;
		for(d = 1; true; d++) {
			ans[0] = 1;
			if(dfs(1)) break;
		}
		printf("%d", ans[0]);
		for(int i = 1; i < d; i++) {
			printf(" %d", ans[i]);
			if(ans[i] == n) break;
		}
		printf("\n");
	}
	return 0;
}
