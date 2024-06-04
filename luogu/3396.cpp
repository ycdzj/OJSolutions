#include <cstdio>
#include <cmath>
const int MAXN = 1.5e5 + 5;
int n, m;
int a[MAXN], ans[1000][1000];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int sq = sqrt(n);
	for(int i = 1; i <= sq; i++) {
		for(int j = 1; j <= n; j++) ans[i][j % i] += a[j];
	}
	while(m--) {
		char cmd[5]; int x, y;
		scanf("%s%d%d", cmd, &x, &y);
		if(cmd[0] == 'A') {
			if(x <= sq) printf("%d\n", ans[x][y]);
			else {
				int ans_ = 0;
				for(int i = y; i <= n; i += x) ans_ += a[i];
				printf("%d\n", ans_);
			}
		}
		else if(cmd[0] == 'C') {
			for(int i = 1; i <= sq; i++) ans[i][x % i] -= a[x] - y;
			a[x] = y;
		}
	}
	return 0;
}