#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 14;
typedef long long ll;
const ll INF = 1e18;

int n, m;
vector<pair<int, int>> adj[MAXN];
ll f[MAXN][1 << MAXN];
int cnt[1 << MAXN];

inline int lowbit(int x) { return x & (-x); }

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    for(int mask = 1; mask < (1 << n); mask++) {
        cnt[mask] = cnt[mask ^ lowbit(mask)] + 1;
    }
    for(int mask = 1; mask < (1 << n); mask++) if(cnt[mask] > 1) {
        for(int rt = 0; rt < n; rt++) if(mask >> rt & 1) {
            f[rt][mask] = -INF;
            for(auto pr : adj[rt]) {
                int v = pr.first, w = pr.second;
                if(mask >> v & 1) {
                    int cur = (mask ^ (1 << rt) ^ (1 << v));
                    for(int sub = cur; sub != 0; sub = ((sub - 1) & cur)) {
                        sub ^= (1 << v);
                        f[rt][mask] = max(f[rt][mask], f[v][sub] + f[rt][mask ^ sub] + (ll)w * cnt[sub] * (n - cnt[sub]));
                        sub ^= (1 << v);
                    }
                    f[rt][mask] = max(f[rt][mask], f[v][1 << v] + f[rt][mask ^ (1 << v)] + (ll)w * cnt[1 << v] * (n - cnt[1 << v]));
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++) ans = max(ans, f[i][(1 << n) - 1]);
    printf("%lld\n", ans);
    return 0;
}