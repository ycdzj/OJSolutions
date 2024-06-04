#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const long long STEP = 37;
const long long MOD = (long long)1e15 + 7;
const int MAXN = 3e5 + 5;

long long addmod(long long a, long long b) {
    return (a + b) % MOD;
}

long long mulmod(long long a, long long b) {
    return (a * b) % MOD;
}

long long submod(long long a, long long b) {
    return addmod(a, MOD - b);
}

long long p[MAXN];

class Solver {
    int n, q;
    vector<int> c;
    vector<vector<int>> adj;

    vector<int> parent;
    vector<int> depth;
    vector<long long> h;
    set<long long> all_h;
    void dfs_parent(int u, int pre) {
        parent[u] = pre;
        depth[u] = depth[pre] + 1;
        h[u] = addmod(h[pre], p[u]);
        all_h.insert(h[u]);
        for (int v : adj[u]) {
            if (v == pre) {
                continue;
            }
            dfs_parent(v, u);
        }
    }

    set<pair<int, int>> black_nodes;
    long long black_h = 0;
    void add(int u) {
        black_h = addmod(black_h, p[u]);
        black_nodes.emplace(depth[u], u);
    }
    void remove(int u) {
        black_h = submod(black_h, p[u]);
        black_nodes.erase({depth[u], u});
    }

    bool check() {
        if (black_nodes.empty()) {
            return false;
        }
        int root = black_nodes.begin()->second;
        int leaf = black_nodes.rbegin()->second;
        long long cur_h = black_h;
        cur_h = submod(cur_h, h[leaf]);
        cur_h = addmod(cur_h, h[root]);
        cur_h = addmod(cur_h, h[root]);
        cur_h = submod(cur_h, p[root]);
        return all_h.find(cur_h) != all_h.end();
    }

   public:
    void read() {
        cin >> n >> q;
        c.resize(n + 1);
        adj.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    void solve() {
        parent.resize(n + 1);
        depth.resize(n + 1);
        h.resize(n + 1);
        dfs_parent(1, 1);

        for (int i = 1; i <= n; i++) {
            if (c[i] == 1) {
                add(i);
            }
        }

        while (q--) {
            int u;
            cin >> u;
            if (c[u] == 1) {
                remove(u);
            }
            c[u] ^= 1;
            if (c[u] == 1) {
                add(u);
            }
            if (check()) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
};

int main() {
    p[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p[i] = mulmod(p[i - 1], STEP);
    }

    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
