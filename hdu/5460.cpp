#include <cstdio>
#include <vector>
#include <unordered_map>
using namespace std;
int n, q, a[10], b[1 << 10];
unordered_map<int, long long> v[1 << 10];
inline int lowbit(int x) { return x & (-x); }
int main() {
	for(int i = 0; i < 10; i++) b[1 << i] = i;
	int T; scanf("%d", &T);
	for(int cnt_case = 1; cnt_case <= T; cnt_case++) {
		scanf("%d%d", &n, &q);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		int exp = (1 << n);
		long long ans = 0;
		for(int i = 1; i < exp; i++) {
			v[i].clear();
			if(i == lowbit(i)) v[i][a[b[i]]]++;
			else {
				for(int x = ((i - 1) & i); x; x = ((x - 1) & i)) {
					int y = x ^ i;
					if(x > y) continue;
					for(auto itrx = v[x].begin(); itrx != v[x].end(); ++itrx) for(auto itry = v[y].begin(); itry != v[y].end(); ++itry) {
						long long z = itrx->second * itry->second;
						int fx = itrx->first, fy = itry->first;
						v[i][fx + fy] += z * 2;
						v[i][fx * fy] += z * 2;
						if(fx - fy >= 0) v[i][fx - fy] += z;
						if(fy - fx >= 0) v[i][fy - fx] += z;
						if(fy != 0 && fx % fy == 0) v[i][fx / fy] += z;
						if(fx != 0 && fy % fx == 0) v[i][fy / fx] += z;
					}
				}
			}
			int cnt = 0;
			for(int j = i; j; j ^= lowbit(j)) cnt++;
			if(v[i].count(q)) ans += cnt * cnt * v[i][q];
		}
		printf("Case #%d: %lld\n", cnt_case, ans);
	}
	return 0;
}
