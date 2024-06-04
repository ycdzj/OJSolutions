#include <algorithm>
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
  int n, m;
  vector<vector<int>> adj;

 public:
  void read() {
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;

      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  void solve() {
    vector<vector<bool>> f((1 << n), vector<bool>(n));
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      f[1 << i][i] = true;
      for (int mask = (1 << i); mask < (1 << n); mask += (1 << (i + 1))) {
        int cur_adj = mask;
        for (int u = 0; u < n; u++) {
          if (mask >> u & 1) {
            for (int v : adj[u]) {
              cur_adj = (cur_adj | (1 << v));
              ans[v] = u;
            }
          }
        }

        for (int v = i + 1; v < n; v++) {
          if ((mask >> v & 1) == 0) {
            continue;
          }
          for (int u : adj[v]) {
            if (f[mask ^ (1 << v)][u]) {
              f[mask][v] = true;
              break;
            }
          }

          if (cur_adj == ((1 << n) - 1) && f[mask][v]) {
            if (find(adj[v].begin(), adj[v].end(), i) != adj[v].end()) {
              ans[v] = i;
              for (int u = v, cur_mask = mask; u != i; ) {
                cur_mask ^= (1 << u);
                for (int x : adj[u]) {
                  if (f[cur_mask][x]) {
                    ans[x] = u;
                    u = x;
                    break;
                  }
                }
              }
              cout << "Yes" << endl;
              for (int val : ans) {
                cout << val + 1 << ' ';
              }
              cout << endl;
              return;
            }
          }
        }
      }
    }

    cout << "No" << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  // cin >> t;
  while (t--) {
    Solver solver;
    solver.read();
    solver.solve();
  }
  return 0;
}
