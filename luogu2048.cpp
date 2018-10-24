#include <cstdio>
#include <queue>
using namespace std;
const int MAXN = (int)5e5 + 5;
int n, k, l, r;
int s[MAXN][20], idx[MAXN][20], lg[MAXN];
int query(int l, int r) {
	int j = lg[r - l + 1];
	return std::max(s[l][j], s[r - (1 << j) + 1][j]);
}
int query_idx(int l, int r) {
	int j = lg[r - l + 1];
	int val = std::max(s[l][j], s[r - (1 << j) + 1][j]);
	if(val == s[l][j]) return idx[l][j];
	else return idx[r - (1 << j) + 1][j];
}
inline int lowbit(int x) { return x & (-x); }
struct Item { int val, idx, l, r; };
bool operator < (const Item &x, const Item &y) {
	return x.val < y.val;
}
priority_queue<Item> heap[MAXN];
int main() {
	for(int i = 0; (1 << i) < MAXN; i++) lg[1 << i] = i;
	for(int i = 1; i < MAXN; i++) {
		int lo = lowbit(i);
		if(i != lo) lg[i] = lg[i ^ lo];
	}

	scanf("%d%d%d%d", &n, &k, &l, &r);
	for(int i = 1; i <= n; i++) {
		int a; scanf("%d", &a);
		s[i][0] = s[i - 1][0] + a;
		idx[i][0] = i;
	}
	for(int j = 1; j < 20; j++) {
		int l = (1 << j), pl = l >> 1;
		for(int i = 0; i + l - 1 <= n; i++) {
			s[i][j] = std::max(s[i][j - 1], s[i + pl][j - 1]);
			if(s[i][j] == s[i][j - 1]) idx[i][j] = idx[i][j - 1];
			else idx[i][j] = idx[i + pl][j - 1];
		}
	}
	priority_queue<pair<int, int>> que;
	for(int i = 0; i + l <= n; i++) {
		int rr = std::min(i + r, n);
		heap[i].push({query(i + l, rr), query_idx(i + l, rr), i + l, rr});
		que.push({query(i + l, rr) - s[i][0], i});
	}
	long long ans = 0;
	while(k--) {
		auto pr = que.top(); que.pop();
		ans += pr.first;
		auto item = heap[pr.second].top(); heap[pr.second].pop();
		int l = item.l, r = item.idx - 1;
		if(l <= r) heap[pr.second].push({query(l, r), query_idx(l, r), l, r});
		l = item.idx + 1; r = item.r;
		if(l <= r) heap[pr.second].push({query(l, r), query_idx(l, r), l, r});
		if(!heap[pr.second].empty()) que.push({heap[pr.second].top().val - s[pr.second][0], pr.second});
	}
	printf("%lld\n", ans);
	return 0;
}