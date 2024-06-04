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
  int n, k;
  vector<int> a;

 public:
  void read() {
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
  }

  void solve() {
    vector<int> cnt(k);
    for (int val : a) {
      cnt[val % k]++;
    }

    int ans = k;
    for (int i = 0; i < k; i++) {
      int j = (k - i) % k;
      if (cnt[j] > 0) {
        ans = i;
        break;
      }
    }
    if (k == 4) {
      ans = min(ans, max(0, 2 - cnt[2]));
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
