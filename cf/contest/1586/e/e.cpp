#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Dsu {
    vector<int> f;
public:
    Dsu(int n) : f(n) {
        for(int i = 0; i < n; i++) {
            f[i] = i;
        }
    }

    int find(int x) {
        if(f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        f[u] = v;
    }
};

class Solver {
    int n, m, q;
    vector<pair<int, int>> edges, queries;

    vector<vector<int>> adj;

    void build_adj() {
        Dsu dsu(n + 1);
        
        for(auto [u, v] : edges) {
            int d_u = dsu.find(u);
            int d_v = dsu.find(v);
            if(d_u != d_v) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                dsu.merge(u, v);
            }
        }
    }

    vector<array<int, 20>> par;
    vector<int> dep;
    void build_par(int u, int p) {
        par[u][0] = p;
        for(int i = 1; i < 20; i++) {
            par[u][i] = par[par[u][i - 1]][i - 1];
        }

        dep[u] = dep[p] + 1;

        for(int v : adj[u]) {
            if(v == p) {
                continue;
            }
            build_par(v, u);
        }
    }

    int get_lca(int u, int v) {
        if(dep[u] > dep[v]) {
            swap(u, v);
        }
        
        int diff = dep[v] - dep[u];
        for(int i = 0; i < 20; i++) {
            if(diff >> i & 1) {
                v = par[v][i];
            }
        }

        if(u == v) {
            return u;
        }

        for(int i = 19; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }

        return par[u][0];
    }

    vector<int> get_simple_path(int u, int v) {
        vector<int> path;
        while(u != v) {
            path.push_back(u);
            u = par[u][0];
        }
        return path;
    }

    vector<int> get_path(int u, int v) {
        int l = get_lca(u, v);

        vector<int> path_u = get_simple_path(u, l);
        vector<int> path_v = get_simple_path(v, l);

        path_u.push_back(l);
        path_u.insert(path_u.end(), path_v.rbegin(), path_v.rend());
        return path_u;
    }

public:
    void read() {
        cin >> n >> m;
        edges.resize(m);
        for(int i = 0; i < m; i++) {
            cin >> edges[i].first >> edges[i].second;
        }

        cin >> q;
        queries.resize(q);
        for(int i = 0; i < q; i++) {
            cin >> queries[i].first >> queries[i].second;
        }
    }

    void solve() {
        vector<int> sum(n + 1);
        for(auto[u, v] : queries) {
            sum[u] ^= 1;
            sum[v] ^= 1;
        }
        int cnt_odd = 0;
        for(int i = 1; i <= n; i++) {
            if(sum[i]) {
                cnt_odd++;
            }
        }
        if(cnt_odd > 0) {
            cout << "NO" << endl;
            cout << cnt_odd / 2 << endl;
            return;
        }

        adj.resize(n + 1);
        par.resize(n + 1);
        dep.resize(n + 1);
        build_adj();
        build_par(1, 1);

        cout << "YES" << endl;
        for(auto[u, v] : queries) {
            vector<int> path = get_path(u, v);
            cout << path.size() << endl;
            for(int val : path) {
                cout << val << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}