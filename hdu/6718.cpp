#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int MAXN = 1e5 + 5;
int inv_2;

inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}
inline int powmod(int a, int x) {
    long long cur = a, res = 1;
    while(x) {
        if(x & 1) {
            res = (res * cur) % MOD;
        }
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return res;
}

int n;
int b[MAXN];
long long c[MAXN];

vector<int> adj[MAXN];
vector<vector<int>> scc;
bool scc_vis[MAXN];
int dfn[MAXN], low[MAXN];
int scc_clock;
stack<int> stk;

void scc_dfs(int u) {
    dfn[u] = low[u] = ++scc_clock;
    stk.push(u);

    for(int v : adj[u]) {
        if(dfn[v] == 0) {
            scc_dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!scc_vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        scc.emplace_back();
        while(stk.top() != u) {
            scc.back().push_back(stk.top());
            scc_vis[stk.top()] = true;
            stk.pop();
        }
        scc.back().push_back(stk.top());
        scc_vis[stk.top()] = true;
        stk.pop();
    }
}

int solve(vector<int> &v) {
    int n = v.size();
    vector<long long> lim(n);
    for(int i = 0; i < v.size(); i++) {
        lim[i] = c[v[i]] + 1;
    }
    int ans = 0;
    for(int j = 0, po = 1, inv_po = 1; j <= 60; j++) {
        long long mask = ((long long)1 << j) - 1;
        long long xorsum = 0;
        int f0 = 1, f1 = 0;
        int sum = 1, cnt = 0;
        for(int i = 0; i < n; i++) {
            int nxt_f0, nxt_f1;
            int val = (lim[i] & mask) % MOD;
            xorsum ^= (lim[i] >> (j + 1));
            sum = mulmod(sum, val);
            if(lim[i] >> j & 1) {
                cnt++;
                nxt_f0 = addmod(mulmod(val, f0), mulmod(po, f1));
                nxt_f1 = addmod(mulmod(val, f1), mulmod(po, f0));
            }
            else {
                nxt_f0 = mulmod(f0, val);
                nxt_f1 = mulmod(f1, val);
            }
            f0 = nxt_f0;
            f1 = nxt_f1;
        }
        f0 = addmod(f0, MOD - sum);

        if(xorsum == 0) {
            if(cnt & 1) {
                ans = addmod(ans, mulmod(f1, inv_po));
            }
            else {
                ans = addmod(ans, mulmod(f0, inv_po));
            }
        }
        po = mulmod(po, 2);
        inv_po = mulmod(inv_po, inv_2);
    }
    return ans;
}

int main() {
    inv_2 = powmod(2, MOD - 2);
    int p60 = 1;
    for(int i = 0; i < 60; i++) {
        p60 = mulmod(p60, 2);
    }
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        adj[i].push_back(b[i]);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
    }
    for(int i = 1; i <= n; i++) {
        if(dfn[i] == 0) {
            scc_dfs(i);
        }
    }
    int ans = 1;
    for(auto v : scc) {
        if(v.size() == 1) {
            ans = mulmod(ans, c[v[0]] % MOD + 1);
        }
        else {
            ans = mulmod(ans, mulmod(solve(v), p60));
        }
    }
    printf("%d\n", ans);
    return 0;
}
