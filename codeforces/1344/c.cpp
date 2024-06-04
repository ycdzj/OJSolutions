#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

struct Graph {
    vector<vector<int>> adj;

    explicit Graph(int n) : adj(n) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
};

class CycleChecker {
    static bool dfs_cycle(const Graph &g, vector<int> &clr, int u) {
        clr[u] = 1;
        for(int v : g.adj[u]) {
            if(clr[v] == 1) {
                return true;
            }
            if(clr[v] == 0) {
                if(dfs_cycle(g, clr, v)) {
                    return true;
                }
            }
        }
        clr[u] = 2;
        return false;
    }
public:
    static bool check_cycle(const Graph &g) {
        vector<int> clr(g.adj.size());
        for(int i = 0; i < g.adj.size(); i++) {
            if(clr[i] == 0) {
                if(dfs_cycle(g, clr, i)) {
                    return true;
                }
            }
        }
        return false;
    }
};

class AcyclicGraph : public Graph {
    vector<int> f;
public:
    explicit AcyclicGraph(int n) : Graph(n), f(n, -1) {}
    int get_f(int u) {
        if(f[u] == -1) {
            f[u] = u;
            for(int v : adj[u]) {
                f[u] = min(f[u], get_f(v));
            }
        }
        return f[u];
    }
};

class Solver {
    int n, m;
    unique_ptr<Graph> g;

    tuple<string, int> get_ans() {
        AcyclicGraph ag(n), rev_ag(n);
        for(int u = 0; u < n; u++) {
            for(int v : g->adj[u]) {
                ag.add_edge(u, v);
                rev_ag.add_edge(v, u);
            }
        }

        string str(n, 'E');
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(ag.get_f(i) == i && rev_ag.get_f(i) == i) {
                str[i] = 'A';
                cnt++;
            }
        }

        return {str, cnt};
    }
public:
    void read() {
        cin >> n >> m;
        g = unique_ptr<Graph>(new Graph(n));

        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            g->add_edge(--u, --v);
        }
    }
    void solve() {
        if(CycleChecker::check_cycle(*g)) {
            cout << -1 << endl;
            return;
        }
        auto [str, cnt] = get_ans();
        cout << cnt << endl;
        cout << str << endl;
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