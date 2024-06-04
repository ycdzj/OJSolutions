#include <cstdio>
#include <algorithm>
const int MAXN = 1e5 + 5;
const int INF = 2e9 + 5;
int n;
struct Item {
	int val, idx;
	int nxt, pre;
} a[MAXN];
int mapper[MAXN];
bool cmp(const Item &x, const Item &y) {
	return x.val < y.val;
}
int ans[MAXN];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i].val);
		a[i].idx = i;
	}
	std::sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; i++) {
		mapper[a[i].idx] = i;
		a[i].pre = i - 1;
		a[i].nxt = i + 1;
	}
	a[1].pre = a[n].nxt = -1;
	for(int i = n; i >= 2; i--) {
		int cur = INF;
		int x = a[mapper[i]].pre, y = mapper[i], z = a[mapper[i]].nxt;

		if(x != -1) {
			int v = abs(a[x].val - a[y].val);
			if(v < cur) {
				cur = v;
				ans[i] = x;
			}
			a[x].nxt = z;
		}
		if(z != -1) {
			int v = abs(a[z].val - a[y].val);
			if(v < cur || (v == cur && a[z].val < a[x].val)) ans[i] = z;
			a[z].pre = x;
		}
	}
	for(int i = 2; i <= n; i++) printf("%d %d\n", abs(a[mapper[i]].val - a[ans[i]].val), a[ans[i]].idx);
	return 0;
}