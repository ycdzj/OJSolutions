#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int lowbit(int x) { return x & (-x); }
const int MAXN = 1e7 + 5;
int tree[MAXN + 5];
void update(int p, int val) {
	while(p <= MAXN) {
		tree[p] = std::max(tree[p], val);
		p += lowbit(p);
	}
}
int query(int p) {
	int res = 0;
	while(p >= 1) {
		res = std::max(res, tree[p]);
		p -= lowbit(p);
	}
	return res;
}

int n;
int x[50005], y[50005];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
	long long ans = 0;
	for(int i = n - 1; i >= 0; i--) {
		int cur = query(MAXN - y[i] + 1);
		if(x[i] > cur) ans += x[i] - cur;
		update(MAXN - y[i] + 1, x[i]);
	}
	memset(tree, 0, sizeof(tree));
	for(int i = n - 1; i >= 0; i--) {
		int cur = query(MAXN - x[i] + 1);
		if(y[i] > cur) ans += y[i] - cur;
		update(MAXN - x[i] + 1, y[i]);
	}
	printf("%lld\n", ans);
	return 0;
}