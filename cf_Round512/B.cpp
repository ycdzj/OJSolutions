#include <cstdio>

int main() {
	int n, d; scanf("%d%d", &n, &d);
	int m; scanf("%d", &m);
	while(m--) {
		int x, y; scanf("%d%d", &x, &y);
		if(d <= x + y && x + y <= 2 * n - d && -d <= x - y && x - y <= d) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
	return 0;
}