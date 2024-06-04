#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int m, n, a[2005], b[2005], c[2005];
struct Item {
	int i, j, val;
};
bool operator < (const Item &x, const Item &y) {
	return x.val > y.val;
}

priority_queue<Item> que;
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a + n);
		for(int i = 1; i < m; i++) {
			for(int j = 0; j < n; j++) scanf("%d", &b[j]);
			sort(b, b + n);
			while(!que.empty()) que.pop();
			que.push({0, 0, a[0] + b[0]});
			for(int j = 0; j < n; j++) {
				Item cur = que.top(); que.pop();
				c[j] = cur.val;
				if(cur.i + 1 < n) que.push({cur.i + 1, cur.j, a[cur.i + 1] + b[cur.j]});
				if(cur.i == 0 && cur.j + 1 < n) que.push({cur.i, cur.j + 1, a[cur.i] + b[cur.j + 1]});
			}
			for(int j = 0; j < n; j++) a[j] = c[j];
		}
		for(int i = 0; i < n; i++) printf("%d%c", a[i], (i + 1 < n) ? ' ' : '\n');
	}
	return 0;
}
