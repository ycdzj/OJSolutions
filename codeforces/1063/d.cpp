#include <cstdio>
#include <algorithm>

typedef long long ll;
ll n, k, l, r;

int main() {
	scanf("%lld%lld%lld%lld", &n, &l, &r, &k);
	ll m = r - l + 1;
	if(m <= 0) m += n;
	ll ans = -1;
	if((double)n * n <= 1e7) {
		for(ll a = 0; a <= m; a++) for(ll b = 0; b <= n - m; b++) {
			ll kk = k - m - a;
			ll nn = n + a + b;
			if(kk >= 0 && kk % nn == 0) ans = std::max(ans, a + b);
			if(a >= 1) {
				kk++;
				if(kk >= 0 && kk % nn == 0) ans = std::max(ans, a + b);
			}
		}
	}
	else {
		if(0 <= k - m && k - m <= m) ans = std::max(ans, k - m + n - m);
		for(ll t = 1; t * n <= k - m; t++) {
			ll cur = k - m - n * t;
			ll y = std::min(cur / t, n);
			y = std::min(y, (n - m + cur) / (t + 1));
			ll x = cur - t * y;
			if(x <= y && x <= m && y - x <= n - m) ans = std::max(ans, y);
		}
		k++;
		if(1 <= k - m && k - m <= m) ans = std::max(ans, k - m + n - m);
		for(ll t = 1; t * n <= k - m; t++) {
			ll cur = k - m - n * t;
			ll y = std::min(cur / t, n);
			y = std::min(y, (n - m + cur) / (t + 1));
			ll x = cur - t * y;
			if(x == 0) {
				y--;
				x += t;
			}
			if(x <= y && x <= m && y - x <= n - m) ans = std::max(ans, y);
		}
	}
	printf("%lld\n", ans);
	return 0;
}