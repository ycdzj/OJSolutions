#include <cstdio>
const int MAXN = 1005;
int n, a[MAXN], cnt[MAXN];
bool ans[MAXN], vis[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		cnt[a[i]]++;
	}
	int tot1 = 0, tot3 = 0;
	for(int i = 0; i < MAXN; i++) {
		if(cnt[i] == 1) tot1++;
		else if(cnt[i] >= 3) tot3++;
	}
	if(tot1 % 2 == 1 && tot3 == 0) printf("NO\n");
	else {
		int amount = tot1 / 2, cur = 0;
		for(int i = 0; i < n; i++) if(cnt[a[i]] == 1) {
			if(cur < amount) {
				ans[i] = true;
				cur++;
			}
		}
		if(tot1 & 1) {
			for(int i = 0; i < n; i++) if(cnt[a[i]] >= 3) {
				ans[i] = true;
				break;
			}
		}
		printf("YES\n");
		for(int i = 0; i < n; i++) putchar(ans[i] ? 'A' : 'B');
		putchar('\n');
	}
	return 0;
}