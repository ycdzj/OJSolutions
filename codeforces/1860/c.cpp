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
  vector<int> p;

 public:
  void read() {
    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }
  }

  void solve() {
    vector<bool> f(n);
    std::set<int> s;
    int min_val = n + 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (min_val > p[i]) {
        f[i] = true;
      } else {
        auto itr = s.lower_bound(p[i]);
        f[i] = (itr != s.begin());
      }
      min_val = min(min_val, p[i]);
      if (!f[i]) {
        s.insert(p[i]);
        ans++;
      }
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
