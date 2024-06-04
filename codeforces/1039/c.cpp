#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;
typedef long long ll;
inline int add(int a, int b) { return (a + b) % MOD; }
inline int mul(ll a, int b) { return (a * b) % MOD; }
int f[MAXN], sz[MAXN], time[MAXN], clk;
void update(int p) {
	if(time[p] != clk) {
		f[p] = p;
		sz[p] = 1;
		time[p] = clk;
	}
}
int find(int x) {
	update(x);
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
void merge(int x, int y) {
	x = find(x); y = find(y);
	if(x != y) {
		sz[y] += sz[x];
		f[x] = y;
	}
}
int n, m, k;
ll c[MAXN];
int pow2[MAXN];
map<ll, vector<pair<int, int>>> mp;
int main() {
	pow2[0] = 1;
	for(int i = 1; i < MAXN; i++) pow2[i] = mul(pow2[i - 1], 2);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++) scanf("%lld", &c[i]);
	for(int i = 0; i < m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		mp[c[u] ^ c[v]].emplace_back(u, v);
	}
	int ans = 0;
	for(auto pr : mp) {
		clk++;
		for(auto e : pr.second) merge(e.first, e.second);
		int blk = 0, szz = 0;
		for(auto e : pr.second) {
			if(sz[find(e.first)] != 0) {
				blk++;
				szz += sz[find(e.first)];
				sz[find(e.first)] = 0;
			}
		}
		ans = add(ans, mul(pow2[n - szz], add(pow2[szz], MOD - pow2[blk])));
	}
	int nk = mul(pow2[n], pow2[k]);
	ans = add(nk, MOD - ans);
	printf("%d\n", ans);
	return 0;
}