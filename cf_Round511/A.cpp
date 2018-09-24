#include <cstdio>

int main() {
	int n; scanf("%d", &n);
	if(n % 3 == 0 || n % 3 == 1) printf("%d %d %d\n", n - 2, 1, 1);
	else printf("%d %d %d\n", n - 3, 1, 2);
	return 0;
}