#include <cstdio>
#include <algorithm>

int main() {
	int q; scanf("%d", &q);
	while(q--) {
		long long n, m, k; scanf("%lld%lld%lld", &n, &m, &k);
		long long ans = -1;
		for(int i = 0; i < (1 << 4); i++) {
			long long nn = n, mm = m, kk = k;
			if(i & 1) nn--, kk--;
			if(i >> 1 & 1) nn++, kk--;
			if(i >> 2 & 1) mm--, kk--;
			if(i >> 3 & 1) mm++, kk--;
			if(nn < 0) nn = -nn;
			if(mm < 0) mm = -mm;
			if((nn + mm) & 1) continue;
			if(nn > mm) std::swap(nn, mm);
			if(kk < mm) continue;
			if((kk - mm) & 1) {
				if(nn != 0) ans = std::max(ans, kk - 2);
			}
			else {
				ans = std::max(ans, kk);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}