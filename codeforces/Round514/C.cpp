#include <cstdio>

int main() {
	int n; scanf("%d", &n);
	int pre = 1;
	for(int i = 0; i < n; i++) {
		int cur = pre;
		while(n / (cur + pre) >= n - i) cur += pre;
		printf("%d ", cur);
		pre = cur;
	}
	printf("\n");
	return 0;
}