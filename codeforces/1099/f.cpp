#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 5;
const int MAXM = 1e5 + 5;
const ll INF = 1e18;
struct Bit {
    ll tree[MAXN];
    int n;
    int lowbit(int x) { return x & (-x); }
    void modify(int p, ll val) {
        while(p <= n) {
            tree[p] += val;
            p += lowbit(p);
        }
    }
    ll query(int p) {
        ll res = 0;
        while(p >= 1) {
            res += tree[p];
            p -= lowbit(p);
        }
        return res;
    }
} bit, bit2;
int n;
ll T;
vector<int> adj[MAXM];
ll x[MAXM], t[MAXM], l[MAXM];
ll val[MAXM];
int p[MAXM];
void dfs(int u, ll sum_l) {
    ll rem = T - 2 * sum_l;
    if(rem < 0) val[u] = -INF;
    else {
        int ll = 1, rr = bit.n;
        while(ll < rr) {
            int mid = (ll + rr) / 2;
            if(bit.query(mid) >= rem) rr = mid;
            else ll = mid + 1;
        }
        if(bit.query(ll) < rem) val[u] = bit2.query(ll);
        else val[u] = bit2.query(ll - 1) + (rem - bit.query(ll - 1)) / ll;
    }
    for(auto v : adj[u]) {
        bit.modify(t[v], t[v] * x[v]);
        bit2.modify(t[v], x[v]);
        dfs(v, sum_l + l[v]);
        bit.modify(t[v], -t[v] * x[v]);
        bit2.modify(t[v], -x[v]);
    }
}
ll f[MAXM];
void calc_f(int u) {
    ll arr[3] = {-INF, -INF, -INF};
    for(auto v : adj[u]) {
        calc_f(v);
        arr[0] = f[v];
        if(arr[0] > arr[1]) swap(arr[0], arr[1]);
        if(arr[1] > arr[2]) swap(arr[1], arr[2]);
    }
    f[u] = max(val[u], arr[1]);
}

int main() {
    cin >> n >> T;
    for(int i = 1; i <= n; i++) cin >> x[i];
    for(int i = 1; i <= n; i++) cin >> t[i];
    for(int i = 2; i <= n; i++) {
        cin >> p[i] >> l[i];
        adj[p[i]].push_back(i);
    }
    bit.n = MAXN - 1;
    bit2.n = MAXN - 1;
    bit.modify(t[1], t[1] * x[1]);
    bit2.modify(t[1], x[1]);
    dfs(1, 0);
    calc_f(1);
    ll ans = f[1];
    for(auto v : adj[1]) ans = max(ans, f[v]);
    cout << ans << endl;
    return 0;
}