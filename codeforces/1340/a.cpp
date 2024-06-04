#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

int n, p[MAXN];
int nxt[MAXN], sz[MAXN];
multiset<int> sz_values;

void update_sz(int pos, int val) {
	sz_values.erase(sz_values.find(sz[pos]));
	sz[pos] = val;
	sz_values.insert(sz[pos]);
}

int find(int x) {
	if(nxt[x] != x) {
		nxt[x] = find(nxt[x]);
	}
	return nxt[x];
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x > y) {
		merge(y, x);
		return;
	}
	nxt[x] = y;
	update_sz(y, sz[x] + sz[y]);
	update_sz(x, 0);
	update_sz(n + 1, 0);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t-- > 0) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			p[x] = i;
		}
		sz_values.clear();
		for(int i = 1; i <= n; i++) {
			nxt[i] = i;
			sz[i] = 1;
			sz_values.insert(1);
		}
		nxt[n + 1] = n + 1;
		sz[n + 1] = 0;
		sz_values.insert(0);
		bool ans = true;
		for(int i = 1; i <= n; i++) {
			if(sz[p[i]] != *sz_values.rbegin()) {
				ans = false;
				break;
			}
			merge(p[i], p[i] + 1);
		}
		if(ans) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}
