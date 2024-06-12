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
  int n;
  vector<int> g[3];

  vector<int> val;
  vector<vector<tuple<int, int, int>>> adj;

  bool dfs(int u, int val_u) {
    val[u] = val_u;
    for (auto [v, a, b] : adj[u]) {
      if (val[u] != a) {
        continue;
      }
      if (val[v] != 0 && val[v] != b) {
        return false;
      }
      if (val[v] == 0) {
        if (!dfs(v, b)) {
          return false;
        }
      }
    }
    return true;
  }

  bool get_ans() {
    val.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      if (val[i] != 0) {
        continue;
      }
      auto val_bak = val;
      if (dfs(i, -1)) {
        continue;
      }
      val = std::move(val_bak);
      if (!dfs(i, 1)) {
        return false;
      }
    }
    return true;
  }

 public:
  void read() {
    cin >> n;
    for (int i = 0; i < 3; i++) {
      g[i].resize(n);
      for (int j = 0; j < n; j++) {
        cin >> g[i][j];
      }
    }
  }

  void solve() {
    adj.resize(n + 1);
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        if (x == y) {
          continue;
        }
        for (int i = 0; i < n; i++) {
          int a = -1;
          if (g[x][i] < 0) {
            a = -a;
          }
          int b = 1;
          if (g[y][i] < 0) {
            b = -b;
          }
          adj[abs(g[x][i])].emplace_back(abs(g[y][i]), a, b);
        }
      }
    }

    if (get_ans()) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
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
