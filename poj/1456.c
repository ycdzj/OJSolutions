#include <cstdio>
#include <algorithm>
const int MAXN = 1e4 + 5;
int f[MAXN];
int find(int x) {
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
int n;
struct Item {
	int p, d;
} item[MAXN];
bool cmp(const Item &x, const Item &y) {
	return x.p > y.p;
}
int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) scanf("%d%d", &item[i].p, &item[i].d);
		for(int i = 0; i < MAXN; i++) f[i] = i;
		std::sort(item, item + n, cmp);
		int ans = 0;
		for(int i = 0; i < n; i++) {
			int cur = find(item[i].d);
			if(cur == 0) continue;
			ans += item[i].p;
			f[cur] = find(cur - 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
