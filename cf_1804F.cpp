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
  int n, m, q;
  vector<vector<pair<int, int>>> adj;

  int get_x(int cnt) {
    vector<int> d(n + 1, -1);
    queue<int> que;
    d[1] = 0;
    que.push(1);
    int res = 0;
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      res = d[u];

      for (auto [v, idx] : adj[u]) {
        if (idx >= cnt) {
          break;
        }
        if (d[v] == -1) {
          d[v] = d[u] + 1;
          que.push(v);
        }
      }
    }

    return res;
  }

 public:
  void read() {
    cin >> n >> m >> q;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back({v, -1});
      adj[v].push_back({u, -1});
    }
    for (int i = 0; i < q; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back({v, i});
      adj[v].push_back({u, i});
    }
  }

  void solve() {
    for (int i = 0; i <= q;) {
      int x_i = get_x(i);
      int l = i + 1, r = q + 1;
      while (l < r) {
        int mid = (l + r) / 2;
        if (2 * get_x(mid) >= x_i) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      while (i < l) {
        cout << x_i << ' ';
        i++;
      }
    }
    cout << endl;
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
