#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 5005;
int mask;
struct Graph {
	int n;
	struct { int v, a, next; } e[MAXN];
	int head[MAXN], cnt_edge;
	void init(int n_) {
		n = n_;
		memset(head, 0xff, n * sizeof(int));
		cnt_edge = 0;
	}
	void add_edge(int u, int v, int a) {
		e[cnt_edge] = { v, a, head[u] };
		head[u] = cnt_edge++;
	}
	bool vis[MAXN];
	int link[MAXN];
	bool hungarian_dfs(int u) {
		for(int i = head[u]; i != -1; i = e[i].next) if(mask >> e[i].a & 1) if(!vis[e[i].v]) {
			vis[e[i].v] = true;
			if(link[e[i].v] == -1 || hungarian_dfs(link[e[i].v])) {
				link[e[i].v] = u, link[u] = e[i].v;
				return true;
			}
		}
		return false;
	}
	int hungarian() {
		memset(link, 0xff, n * sizeof(int));
		int res = 0;
		for(int i = 0; i < n; i++) if(link[i] == -1) {
			memset(vis, 0, n * sizeof(int));
			if(hungarian_dfs(i)) res++;
		}
		return res;
	}
} G;
vector<vector<int>> v[MAXN];
int val[3], idx[3];
bool cmp(int x, int y) { return val[x] < val[y]; }
inline int get(int x, int y, int z) {
	int id[3];
	id[idx[0]] = x;
	id[idx[1]] = y;
	id[idx[2]] = z;
	return v[id[0]][id[1]][id[2]];
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &val[0], &val[1], &val[2]);
		for(int i = 0; i < val[0]; i++) {
			v[i].resize(val[1]);
			for(int j = 0; j < val[1]; j++) {
				v[i][j].resize(val[2]);
				for(int k = 0; k < val[2]; k++) scanf("%d", &v[i][j][k]);
			}
		}
		idx[0] = 0; idx[1] = 1; idx[2] = 2;
		sort(idx, idx + 3, cmp);
		int a = val[idx[0]], b = val[idx[1]], c = val[idx[2]];
		int ans = a * b * c;
		int exp = (1 << a);
		G.init(b + c);
		for(int i = 0; i < a; i++) for(int j = 0; j < b; j++) for(int k = 0; k < c; k++) {
			if(get(i, j, k) == 1) G.add_edge(j, b + k, i);
		}
		for(mask = 0; mask < exp; mask++) {
			int cur = a;
			for(int i = 0; i < a; i++) if(mask >> i & 1) cur--;
			ans = min(ans, cur + G.hungarian());
		}
		printf("%d\n", ans);
	}
	return 0;
}
