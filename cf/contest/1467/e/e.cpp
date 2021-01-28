#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<vector<int>> adj;
    vector<int> a;

    vector<int> b;
    map<int, int> total;
    int edge_count;
    void dfs(int u, int par, map<int, int> &count) {
        int origin_count = count[a[u]]++;

        int before = count[a[u]];
        for(int v : adj[u]) {
            if(v == par) {
                continue;
            }
            dfs(v, u, count);
            if(count[a[u]] > before) {
                edge_count++;
                b[v]++;
                before = count[a[u]];
            }
        }
        if((before - origin_count) != total[a[u]]) {
            edge_count++;
            b[0]++;
            b[u]--;
        }
    }

    void dfs2(int u, int par, int cur_val, int &ans) {
        cur_val += b[u];
        if(cur_val == edge_count) {
            ans++;
        }
        for(int v : adj[u]) {
            if(v == par) {
                continue;
            }
            dfs2(v, u, cur_val, ans);
        }
    }

public:
    void read() {
        scanf("%d", &n);
        adj.resize(n);
        a.resize(n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--;
            v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    void solve() {
        b.resize(n);
        total.clear();
        edge_count = 0;

        for(int i = 0; i < n; i++) {
            total[a[i]]++;
        }

        map<int, int> count;
        dfs(0, 0, count);
        int ans = 0;
        dfs2(0, 0, 0, ans);
        printf("%d\n", ans);
    }
};

int main() {
    Solver solver;
    solver.read();
    solver.solve();
    return 0;
}
