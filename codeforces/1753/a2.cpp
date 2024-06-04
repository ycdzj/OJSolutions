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
  int n;
  vector<int> a;
 public:
  void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
  }

  void solve() {
    int sum = accumulate(a.begin(), a.end(), 0);
    vector<bool> b(n);
    for (int i = 1, pre = 0; i < n; i++) {
      if (sum * a[i] > 0 && !b[i - 1]) {
        b[i] = true;
        sum -= 2 * a[i];
      }
    }
    if (sum) {
      cout << -1 << endl;
    } else {
      int cnt = count(b.begin(), b.end(), false);
      cout << cnt << endl;
      for (int i = 1, pre = 0; i <= n; i++) {
        if (i == n || !b[i]) {
          cout << pre + 1 << ' ' << i << endl;
          pre = i;
        }
      }
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
