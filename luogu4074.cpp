#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAXN = 1e5 + 5;
struct Query {
	int time, x, y, idx;
} query[MAXN];
struct Modi {
	int time, x, y, pre;
} modi[MAXN];
int cnt_q, cnt_m;
vector<int> adj[MAXN];
int w[MAXN], v[MAXN], c[MAXN];
int n, m, q;
int cnt[MAXN], cur_u, cur_v, cur_t;
bool vis[MAXN];
long long cur_ans;
void ins(int val) {
	cur_ans += (long long)v[val] * w[++cnt[val]];
}
void del(int val) {
	cur_ans -= (long long)v[val] * w[cnt[val]--];
}
void sync_t(int t) {
	while(cur_t < cnt_m && modi[cur_t].time < t) {
		int x = modi[cur_t].x;
		if(vis[x]) del(c[x]);
		modi[cur_t].pre = c[x];
		c[x] = modi[cur_t].y;
		if(vis[x]) ins(c[x]);
		cur_t++;
	}
	while(cur_t > 0 && modi[cur_t - 1].time >= t) {
		cur_t--;
		int x = modi[cur_t].x;
		if(vis[x]) del(c[x]);
		c[x] = modi[cur_t].pre;
		if(vis[x]) ins(c[x]);
	}
}
int fa[MAXN][20], dep[MAXN];
int sq, bno[MAXN], cnt_bno;
stack<int> stk;
void dfs(int u, int pre) {
	fa[u][0] = pre;
	dep[u] = dep[pre] + 1;
	int cur = stk.size();
	for(auto v : adj[u]) if(v != pre) {
			dfs(v, u);
			if(stk.size() - cur >= sq) {
				while(stk.size() > cur) {
					bno[stk.top()] = cnt_bno;
					stk.pop();
				}
				cnt_bno++;
			}
		}
	stk.push(u);
}
int lca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	int d = dep[v] - dep[u];
	for(int i = 0; i < 20; i++) if(d >> i & 1) v = fa[v][i];
	if(u == v) return u;
	for(int i = 19; i >= 0; i--) if(fa[u][i] != fa[v][i]) {
			u = fa[u][i]; v = fa[v][i];
		}
	return fa[u][0];
}
void sync_u(int &cur, int u) {
	int lc = lca(cur, u);
	for(int i = cur; i != lc; i = fa[i][0]) {
		if(vis[i]) del(c[i]), vis[i] = false;
		else ins(c[i]), vis[i] = true;
	}
	for(int i = u; i != lc; i = fa[i][0]) {
		if(vis[i]) del(c[i]), vis[i] = false;
		else ins(c[i]), vis[i] = true;
	}
	cur = u;
}
bool cmp(const Query &x, const Query &y) {
	if(bno[x.x] != bno[y.x]) return bno[x.x] < bno[y.x];
	if(bno[x.y] != bno[y.y]) return bno[x.y] < bno[y.y];
	return x.time < y.time;
}
long long ans[MAXN];
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= m; i++) scanf("%d", &v[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for(int i = 1; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 0; i < q; i++) {
		int t, x, y; scanf("%d%d%d", &t, &x, &y);
		if(t == 0) modi[cnt_m++] = {i, x, y};
		else {
			query[cnt_q] = {i, x, y, cnt_q};
			cnt_q++;
		}
	}
	sq = pow(n, 2.0 / 3);
	dfs(1, 1);
	while(!stk.empty()) {
		bno[stk.top()] = cnt_bno;
		stk.pop();
	}
	for(int i = 1; i < 20; i++) {
		for(int u = 1; u <= n; u++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	cur_u = 1; cur_v = 1;
	sort(query, query + cnt_q, cmp);
	for(int i = 0; i < cnt_q; i++) {
		sync_t(query[i].time);
		sync_u(cur_u, query[i].x);
		sync_u(cur_v, query[i].y);
		int p = lca(cur_u, cur_v);
		ins(c[p]);
		ans[query[i].idx] = cur_ans;
		del(c[p]);
	}
	for(int i = 0; i < cnt_q; i++) printf("%lld\n", ans[i]);
	return 0;
}