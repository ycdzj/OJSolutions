#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
const int MAXN = 2e5 + 5;
const int INF = 1e9 + 5;
int n, m, d;
struct Item {
	int val, idx;
	bool operator < (const Item &item) {
		return val < item.val;
	}
} a[MAXN];
int ans[MAXN];
int cnt;
int main() {
	scanf("%d%d%d", &n, &m, &d);
	std::set<std::pair<int, int>> s;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i].val);
		a[i].idx = i;
	}
	std::sort(a, a + n);
	for(int i = 0; i < n; i++) {
		if(s.empty()) {
			s.insert({a[i].val, cnt});
			ans[a[i].idx] = cnt;
			cnt++;
		}
		else {
			auto itr = s.lower_bound({a[i].val - d - 1, INF});
			if(itr != s.begin()) {
				--itr;
				ans[a[i].idx] = itr->second;
				s.erase(itr);
				s.insert({a[i].val, ans[a[i].idx]});
			}
			else {
				s.insert({a[i].val, cnt});
				ans[a[i].idx] = cnt;
				cnt++;
			}
		}
	}
	printf("%d\n", cnt);
	for(int i = 0; i < n; i++) printf("%d ", ans[i] + 1);
	printf("\n");
	return 0;
}