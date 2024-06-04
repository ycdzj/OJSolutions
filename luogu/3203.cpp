#include <cstdio>
#include <cmath>

const int MAXN = 200000 + 5;
int k[MAXN], n, sq;
int cnt[MAXN], to[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &k[i]);
	sq = sqrt(n);
	for(int i = n - 1; i >= 0; i--) {
		if(i + k[i] >= n || i / sq != (i + k[i]) / sq) {
			cnt[i] = 1;
			to[i] = i + k[i];
		}
		else {
			cnt[i] = 1 + cnt[i + k[i]];
			to[i] = to[i + k[i]];
		}
	}
	int q; scanf("%d", &q);
	while(q--) {
		int op; scanf("%d", &op);
		if(op == 1) {
			int s; scanf("%d", &s);
			int ans = 0;
			while(s < n) {
				ans += cnt[s];
				s = to[s];
			}
			printf("%d\n", ans);
		}
		else {
			int p, j; scanf("%d%d", &p, &j);
			k[p] = j;
			int l = p - p % sq;
			for(int i = p; i >= l; i--) {
				if(i + k[i] >= n || i / sq != (i + k[i]) / sq) {
					cnt[i] = 1;
					to[i] = i + k[i];
				}
				else {
					cnt[i] = 1 + cnt[i + k[i]];
					to[i] = to[i + k[i]];
				}
			}
		}
	}
	return 0;
}
