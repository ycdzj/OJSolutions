#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 2e5 + 5;
typedef long long ll;
int n, h;
ll l[MAXN], r[MAXN];
ll sum[MAXN];
bool check(int i, ll d) {
	ll t = l[i] + d;
	int p = lower_bound(l, l + n, t) - l - 1;
	ll cur = sum[p] - sum[i];
	if(r[p] < t) return cur + t - r[p] <= h;
	return cur < h;
}
int main() {
	scanf("%d%d", &n, &h);
	for(int i = 0; i < n; i++) scanf("%lld%lld", &l[i], &r[i]);
	for(int i = 1; i < n; i++) {
		sum[i] = sum[i - 1] + l[i] - r[i - 1];
	}
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ll l = 0, r = 4e9;
		while(l < r) {
			ll mid = l + (r - l) / 2 + 1;
			if(check(i, mid)) l = mid;
			else r = mid - 1;
		}
		ans = max(ans, l);
	}
	printf("%lld\n", ans);
	return 0;
}