#include <cstdio>
#include <algorithm>
const int MAXN = 1005;
int n, cnt[MAXN];
int main() {
	scanf("%d", &n);
	bool ans = true;
	for(int i = 0; i < n - 1; i++) {
		int a, b; scanf("%d%d", &a, &b);
		if(b < n) ans = false;
		cnt[a]++;
	}
	if(ans) {
		int p = 1;
		for(int i = 1; i <= n - 1; i++) if(cnt[i] > 1) {
			for(int j = 0; j < cnt[i] - 1; j++) {
				while(p < i && cnt[p] > 0) p++;
				if(p >= i) ans = false;
				p++;
			}
		}
	}
	if(!ans) printf("NO\n");
	else {
		printf("YES\n");
		int p = 1;
		for(int i = 1; i <= n - 1; i++) if(cnt[i] > 0) {
			int pre = n;
			for(int j = 0; j < cnt[i] - 1; j++) {
				while(p < i && cnt[p] > 0) p++;
				printf("%d %d\n", pre, p);
				pre = p++;
			}
			printf("%d %d\n", pre, i);
		}
	}
	return 0;
}
