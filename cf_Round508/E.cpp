//欧拉路 状压
#include <cstdio>
#include <algorithm>
const int INF = 1e9;
int idx[4][4];
int n;
int cnt[10], min_[10], val[10];
int find(int *f, int x) {
	if(f[x] != x) f[x] = find(f, f[x]);
	return f[x];
}
int main() {
	for(int i = 0, k = 0; i < 4; i++) for(int j = i; j < 4; j++) {
		min_[k] = INF;
		idx[i][j] = idx[j][i] = k++;
	}

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int c1, v, c2; scanf("%d%d%d", &c1, &v, &c2);
		--c1; --c2;
		cnt[idx[c1][c2]]++;
		val[idx[c1][c2]] += v;
		min_[idx[c1][c2]] = std::min(min_[idx[c1][c2]], v);
	}
	int ans = 0;
	for(int mask = 0; mask < (1 << 10); mask++) {
		bool flag = true;
		for(int i = 0; i < 10; i++) if(cnt[i] == 0 && (mask >> i & 1)) {
			flag = false;
			break;
		}
		if(!flag) continue;
		for(int vmask = 0; vmask < (1 << 4); vmask++) {
			int deg[4] = {0, 0, 0, 0};
			int f[4] = {0, 1, 2, 3};
			int cur = 0;
			for(int i = 0; i < 4; i++) for(int j = i; j < 4; j++) if((vmask >> i & 1) && (vmask >> j & 1)) {
				if(cnt[idx[i][j]] == 0) continue;
				if(cnt[idx[i][j]] == 1 && (mask >> idx[i][j] & 1)) continue;
				f[find(f, i)] = find(f, j);
				deg[i] += cnt[idx[i][j]];
				deg[j] += cnt[idx[i][j]];
				cur += val[idx[i][j]];
				if(mask >> idx[i][j] & 1) {
					deg[i]--; deg[j]--;
					cur -= min_[idx[i][j]];
				}
			}
			bool fg = true;
			for(int i = 0; i < 4; i++) for(int j = i; j < 4; j++) if((vmask >> i & 1) && (vmask >> j & 1)) {
				if(find(f, i) != find(f, j)) fg = false;
			}
			if(!fg) continue;
			int odd = 0;
			for(int i = 0; i < 4; i++) if(deg[i] & 1) odd++;
			if(odd == 0 || odd == 2)
				ans = std::max(ans, cur);
		}
	}
	printf("%d\n", ans);
	return 0;
}