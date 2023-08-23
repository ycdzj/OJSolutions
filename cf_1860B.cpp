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

const long long INF = 1e18;

class Solver {
  long long m, k, a1, ak;

  long long get_ans(long long i) {
    if (0 <= i && i <= m / k) {
      return max(0ll, i - ak) + max(0ll, m - i * k - a1);
    }
    return INF;
  }

 public:
  void read() { cin >> m >> k >> a1 >> ak; }

  void solve() {
    long long ans = get_ans(0);
    ans = min(ans, get_ans(m / k));
    ans = min(ans, get_ans(ak));
    ans = min(ans, get_ans(ak - 1));
    long long x = (m - a1) / k;
    ans = min(ans, get_ans(x));
    ans = min(ans, get_ans(x + 1));
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
