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

class Solver {
    int n, a, b;
    vector<vector<int>> adj;

    vector<int> dfs_path;
    void dfs_mid(int u, int pre, int& mid, int& dis) {
        dfs_path.push_back(u);
        if (u == b) {
            dis = dfs_path.size() / 2;
            mid = dfs_path[(dfs_path.size() - 1) / 2];
        } else {
            for (int v : adj[u]) {
                if (v == pre) {
                    continue;
                }
                dfs_mid(v, u, mid, dis);
            }
        }
        dfs_path.pop_back();
    }

    int dfs_longest(int u, int pre) {
        int dis = 0;
        for (int v : adj[u]) {
            if (v == pre) {
                continue;
            }
            dis = max(dis, 1 + dfs_longest(v, u));
        }
        return dis;
    }

   public:
    void read() {
        cin >> n >> a >> b;
        adj.resize(n + 1);
        for (int i = 1; i < n; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }

    void solve() {
        int mid, dis_mid;
        dfs_mid(a, a, mid, dis_mid);
        int dis_long = dfs_longest(mid, mid);
        int ans = 2 * (n - 1) + dis_mid - dis_long;
        cout << ans << endl;
    }
};

int main() {
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
