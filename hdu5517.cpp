#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
map<int, vector<pair<int, int>>> mp_b;
map<int, pair<int, int>> mp_a;
struct Item {
	int c, d, cnt;
};
bool cmp(const Item &x, const Item &y) {
	if(x.c != y.c) return x.c < y.c;
	return x.d < y.d;
}
map<int, vector<Item>> triple;
int n, m;
struct BIT {
	inline int lowbit(int x) { return x & (-x); }
	int tree[1005][1005];
	void modify(int x, int y) {
		for(int i = x; i > 0; i -= lowbit(i)) {
			for(int j = y; j > 0; j -= lowbit(j)) {
				tree[i][j]++;
			}
		}
	}
	int query(int x, int y) {
		int res = 0;
		for(int i = x; i <= 1000; i += lowbit(i)) {
			for(int j = y; j <= 1000; j += lowbit(j)) {
				res += tree[i][j];
			}
		}
		return res;
	}
} bit;
int main() {
	int T; scanf("%d", &T);
	for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
		memset(bit.tree, 0, sizeof(bit.tree));
		mp_a.clear();
		mp_b.clear();
		triple.clear();

		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) {
			int a, b; scanf("%d%d", &a, &b);
			if(mp_a.count(b) == 0 || mp_a[b].first < a) mp_a[b] = {a, 1};
			else if(mp_a[b].first == a) mp_a[b].second++;
		}
		for(int i = 0; i < m; i++) {
			int c, d, e; scanf("%d%d%d", &c, &d, &e);
			mp_b[e].push_back({c, d});
		}
		for(auto val : mp_a) if(mp_b.count(val.first)){
			auto &v = mp_b[val.first];
			auto &vv = triple[val.second.first];
			for(auto cd : v) vv.push_back({cd.first, cd.second, val.second.second});
		}
		long long ans = 0;
		for(auto itr = triple.rbegin(); itr != triple.rend(); ++itr) {
			auto &v = itr->second;
			sort(v.begin(), v.end(), cmp);
			int top = 0;
			for(int i = 1; i < v.size(); i++) {
				if(v[i].c == v[top].c && v[i].d == v[top].d) v[top].cnt += v[i].cnt;
				else v[++top] = v[i];
			}
			for(int i = top; i >= 0; i--) {
				if(bit.query(v[i].c, v[i].d) == 0) ans += v[i].cnt;
				bit.modify(v[i].c, v[i].d);
			}
		}
		printf("Case #%d: %lld\n", cnt_case, ans);
	}
	return 0;
}
