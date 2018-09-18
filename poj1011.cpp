#include <cstdio>
#include <algorithm>
#include <cstring>
int a[70], n;
int len, cnt;
bool vis[70];
bool dfs(int i, int cur, int p) {
	if(i == cnt) return true;
	for(int j = p; j < n; j++) if(!vis[j]) {
		vis[j] = true;
		if(cur + a[j] < len) {
			if(dfs(i, cur + a[j], j + 1)) return true;
			else if(cur == 0) {
				vis[j] = false;
				return false;
			}
		}
		else if(cur + a[j] == len) {
			if(dfs(i + 1, 0, 0)) return true;
			else {
				vis[j] = false;
				return false;
			}
		}
		else if(cur == 0) {
			vis[j] = false;
			return false;
		}
		vis[j] = false;
	}
	return false;
}
int main() {
	while(scanf("%d", &n) != EOF) {
		if(n == 0) break;
		int sum = 0;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), sum += a[i];
		std::sort(a, a + n);
		std::reverse(a, a + n);
		int ans = sum;
		for(len = 1; len < sum; len++) if(sum % len == 0) {
			cnt = sum / len;
			memset(vis, 0, sizeof(vis));
			if(dfs(0, 0, 0)) {
				ans = len;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
