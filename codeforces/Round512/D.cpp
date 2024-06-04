#include <cstdio>
typedef long long ll;
ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
ll n, m, k;
int main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	if((2 * n * m) % k != 0) printf("NO\n");
	else {
		printf("YES\n");
		ll cur = k;
		ll a = 2, b = n, c = m;

		ll g = gcd(cur, a);
		cur /= g; a /= g;

		g = gcd(cur, b);
		cur /= g; b /= g;

		g = gcd(cur, c);
		cur /= g; c /= g;

		if(a * b <= n) b *= a;
		else c *= a;

		printf("0 0\n");
		printf("%lld %lld\n", b, (ll)0);
		printf("%lld %lld\n", (ll)0, c);
	}
	return 0;
}