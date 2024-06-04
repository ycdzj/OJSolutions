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

struct Prime {
    vector<int> pri;
    void build(int n) {
        vector<bool> vis(n);
        for (int i = 2; i < n; i++) {
            if (vis[i]) {
                continue;
            }
            pri.push_back(i);
            for (int j = 2 * i; j < n; j += i) {
                vis[j] = true;
            }
        }
    }
};

Prime pri;

class Solver {
    int n;

    int m;
    vector<vector<int>> nxt;
    vector<vector<int>> adj;

    void dfs(int pre, int u, int s) {
        nxt[pre][u] = s;
        while (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            if (nxt[u][v] != -2) {
                continue;
            }
            nxt[u][v] = -1;
            nxt[v][u] = -1;
            nxt[pre][u] = v;
            dfs(u, v, s);
            s = v;
        }
    }

   public:
    void read() {
        cin >> n;
    }

    void solve() {
        int m = -1;
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) {
                if (i * i / 2 + 1 >= n - 1) {
                    m = i;
                    break;
                }
            } else {
                if (i * (i + 1) / 2 >= n - 1) {
                    m = i;
                    break;
                }
            }
        }

        nxt.assign(m, vector<int>(m, -2));
        adj.resize(m);
        for (int i = 0; i < m; i++) {
            int x = i ^ 1;
            for (int j = 0; j < m; j++) {
                if (j == i) {
                    continue;
                }
                if (j > 1 && i > 1 && m % 2 == 0 && j == x) {
                    continue;
                }
                adj[i].push_back(j);
            }
        }

        dfs(0, 0, -1);

        vector<bool> vis(m);
        int pre = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            cout << pri.pri[cur] << ' ';
            if (!vis[cur] && i + 1 < n) {
                vis[cur] = true;
                cout << pri.pri[cur] << ' ';
                i++;
            }
            int next = nxt[pre][cur];
            pre = cur;
            cur = next;
        }
        cout << endl;
    }
};

int main() {
    pri.build(100000);
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
