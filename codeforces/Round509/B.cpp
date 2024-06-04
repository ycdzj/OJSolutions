#include <cstdio>
#include <algorithm>
long long gcd(long long a, long long b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
int main() {
	long long a, b, x, y;
	scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
	long long g = gcd(x, y);
	x /= g; y /= g;
	printf("%lld\n", std::min(b / y, a / x));
	return 0;
}