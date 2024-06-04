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
  int n, k, d, w;
  vector<int> t;

 public:
  void read() {
    cin >> n >> k >> d >> w;
    t.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> t[i];
    }
  }

  void solve() {
    int ans = 0;
    int idx = 0;
    while (idx < n) {
      int open_ts = t[idx] + w;
      int remain = k;
      ans++;
      while (remain > 0 && idx < n && t[idx] <= open_ts + d) {
        idx++;
        remain--;
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
