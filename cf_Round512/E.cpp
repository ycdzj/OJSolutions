#include <cstdio>
typedef long long ll;
const int MAXN = 3e5 + 5;
ll a[MAXN];
int n, f[MAXN], cnt[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
		while(a[i]) {
			if(a[i] & 1) cnt[i]++;
			a[i] >>= 1;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		f[i] = f[i + 1] + 1;
		if(cnt[i] & 1) f[i] = (n - i) - f[i];
	}
	ll ans = 0;
	for(int i = 0; i < n; i++) {
		ll l = 0, r = 0;
		for(int j = i; j < n; j++) {
			if(cnt[j] >= r) {
				l = cnt[j] - r;
				r += cnt[j];
			}
			else if(cnt[j] <= l) {
				l = l - cnt[j];
				r += cnt[j];
			}
			else {
				r += cnt[j];
				l = (r & 1);
			}
			if(l == 0) ans++;
			if(l == 0 || l == 1) {
				if(r >= 70) {
					ll dd = f[j + 1];
					ll cc = n - j - 1;
					if(l == 0) ans += dd;
					else ans += cc - dd;
					break;
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}