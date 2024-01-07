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
  vector<int> a;

 public:
  void read() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
  }

  void solve() {
    std::set<int> vis;
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
      pos[i] = pos[i - 1];
      if (vis.count(a[i]) > 0) {
        continue;
      }
      pos[i]++;
      vis.insert(a[i]);
    }
    vis.clear();
    long long ans = 0;
    for (int i = n; i >= 1; i--) {
      if (vis.count(a[i]) > 0) {
        continue;
      }
      ans += pos[i];
      vis.insert(a[i]);
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
