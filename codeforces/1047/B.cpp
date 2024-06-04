#include <cstdio>
#include <algorithm>

int main() {
	int ans = 0;
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		ans = std::max(ans, x + y);
	}
	printf("%d\n", ans);
	return 0;
}