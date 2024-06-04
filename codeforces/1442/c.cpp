#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Mod {
    int m;
public:
    explicit Mod(int m) : m(m) {}
    int add(int a, int b) {
        return (a + b) % m;
    }
    int mul(int a, int b) {
        return static_cast<int>((static_cast<long long>(a) * b) % m);
    }
    int sub(int a, int b) {
        return add(a, m - b);
    }
    int pow(int a, int x) {
        long long cur = a, res = 1;
        while(x) {
            if(x & 1) {
                res = (res * cur) % m;
            }
            x >>= 1;
            cur = (cur * cur) % m;
        }
        return static_cast<int>(res);
    }
    int inv(int a) {
        return pow(a, m - 2);
    }
    int div(int a, int b) {
        return mul(a, inv(b));
    }
} mod(998244353);

template <typename T>
pair<T, T> operator + (const pair<T, T> &a, const pair<T, T> &b) {
    return {a.first + b.first, a.second + b.second};
}

template <typename WEIGHT_TYPE>
class Graph {
    vector<vector<pair<int, WEIGHT_TYPE>>> adj;

public:
    explicit Graph(int n) : adj(n) {}

    void add_edge(int u, int v, WEIGHT_TYPE w) {
        adj[u].emplace_back(v, w);
    }

    void dijkstra(int s, vector<WEIGHT_TYPE> &dis) {
        priority_queue<pair<WEIGHT_TYPE, int>, vector<pair<WEIGHT_TYPE, int>>, greater<>> que;
        vector<bool> vis(adj.size());

        que.push({dis[s], s});

        while(!que.empty()) {
            auto [dis_u, u] = que.top();
            que.pop();
            if(!vis[u]) {
                vis[u] = true;
                dis[u] = dis_u;

                for(auto [v, w] : adj[u]) {
                    if(!vis[v]) {
                        que.push({dis[u] + w, v});
                    }
                }
            }
        }
    }
};

class Solver {
    int n, m, k;
    vector<vector<int>> adj;

    void init_k() {
        k = 1;
        while((1 << k) <= n) {
            k++;
        }
    }

    tuple<int, bool> get_first_ans() {
        Graph<int> g(n * (k + 1));

        for(int u = 0; u < n; u++) {
            for(int v : adj[u]) {
                for(int i = 0; i <= k; i++) {
                    int gu = i * n + u, gv = i * n + v;
                    if(i & 1) {
                        swap(gu, gv);
                    }
                    g.add_edge(gu, gv, 1);
                }
            }
        }

        for(int i = 0; i < k; i++) {
            for(int u = 0; u < n; u++) {
                g.add_edge(i * n + u, (i + 1) * n + u, 1 << i);
            }
        }

        vector<int> dis(n * (k + 1), 1e9);
        dis[0] = 0;
        g.dijkstra(0, dis);

        int ans = 1e9;
        for(int i = 0; i <= k; i++) {
            ans = min(ans, dis[i * n + n - 1]);
        }

        if(ans == 1e9) {
            return {0, false};
        }
        return {ans, true};
    }

    int get_second_ans() {
        Graph<pair<int, int>> g(n * 2);
        for(int u = 0; u < n; u++) {
            for(int v : adj[u]) {
                g.add_edge(u, v, {0, 1});
                g.add_edge(n + v, n + u, {0, 1});
            }
            g.add_edge(u, n + u, {1, 0});
            g.add_edge(n + u, u, {1, 0});
        }

        vector<pair<int, int>> dis(n * 2);
        g.dijkstra(0, dis);

        pair<int, int> min_dis = min(dis[n - 1], dis[n + n - 1]);
        return mod.add(mod.sub(mod.pow(2, min_dis.first), 1), min_dis.second);
    }

    int get_ans() {
        if(auto [ans, ok] = get_first_ans(); ok) {
            return ans;
        }
        return get_second_ans();
    }
public:
    explicit Solver() {
        cin >> n >> m;
        adj.resize(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[--u].push_back(--v);
        }
        init_k();
    }
    void solve() {
        cout << get_ans() << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while(t--) {
        Solver solver;
        solver.solve();
    }
    return 0;
}