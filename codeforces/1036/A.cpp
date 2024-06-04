#include <cstdio>

int main() {
	long long n, k; scanf("%lld%lld", &n, &k);
	printf("%lld\n", (k + n - 1) / n);
}