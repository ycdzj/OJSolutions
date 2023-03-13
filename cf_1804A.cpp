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
  int a, b;
 public:
  void read() {
    cin >> a >> b;
  }

  void solve() {
    a = abs(a);
    b = abs(b);
    int ans = a + b + abs(a - b);
    if (abs(a - b) > 0) {
      ans--;
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
