#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const int MAXN = 100000 + 5;
int n, k;
ll a[MAXN];
int pre[MAXN], nxt[MAXN];
struct Item {
	ll val;
	int p;
};
bool operator < (const Item &x, const Item &y) {
	return x.val > y.val;
}
priority_queue<Item> que;
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	for(int i = 0; i < n - 1; i++) {
		a[i] = a[i + 1] - a[i];
		pre[i] = i - 1;
		nxt[i] = i + 1;
		que.push({a[i], i});
	}
	pre[0] = nxt[n - 2] = -1;
	ll ans = 0;
	while(k > 0) {
		Item cur = que.top(); que.pop();
		if(a[cur.p] != cur.val) continue;
		ans += cur.val;
		k--;
		a[cur.p] = -1;
		int x = pre[cur.p], y = nxt[cur.p];
		if(x == -1) {
			a[y] = -1;
			if(nxt[y] != -1) pre[nxt[y]] = -1;
		}
		else if(y == -1) {
			a[x] = -1;
			if(pre[x] != -1) nxt[pre[x]] = -1;
		}
		else {
			a[x] = a[x] + a[y] - cur.val;
			nxt[x] = nxt[y];
			if(nxt[x] != -1) pre[nxt[x]] = x;
			a[y] = -1;
			que.push({a[x], x});
		}
	}
	printf("%lld\n", ans);
	return 0;
}
