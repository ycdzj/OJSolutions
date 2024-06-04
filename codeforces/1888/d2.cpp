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
  int n, m;
  vector<int> a, b;

 public:
  void read() {
    cin >> n >> m;
    a.resize(n - 1);
    for (int i = 0; i < n - 1; i++) {
      cin >> a[i];
    }
    b.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> b[i];
    }
  }

  void solve() {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> f(n - 1);
    for (int i = 0, j = 0; i < n - 1; i++) {
      while (j < n && b[j] <= a[i]) {
        j++;
      }
      f[i] = j;
    }

    vector<int> g(n + 1);
    for (int k = n, max_val = 0; k >= 1 && max_val <= k; k--) {
      g[k] = 1e9;
      if (k > 1) {
        max_val = max(max_val, f[n - k] - (n - k));
      }
    }

    vector<int> max_pos(n + 1, -1);
    int max_h = 0;
    for (int k = n - 1; k >= 0; k--) {
      if (max_h <= k) {
        g[k] = max(g[k], b[n - 1] - 1);
      } else if (max_h == k + 1) {
        g[k] = max(g[k], b[f[max_pos[k + 1]] - 1] - 1);
      }
      int j = n - 1 - k;
      max_h = max(max_h, f[j] - j);
      if (0 <= f[j] - j && f[j] - j <= n) {
        if (max_pos[f[j] - j] == -1) {
          max_pos[f[j] - j] = j;
        }
      }
    }

    long long ans = 0;
    g[0] = min(g[0], m);
    for (int i = 1; i <= n; i++) {
      g[i] = min(g[i], m);
      ans += (long long)i * (g[i] - g[i - 1]);
    }

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
