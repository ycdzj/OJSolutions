#include <algorithm>
#include <bitset>
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

const int MAXN = 1e5 + 5;

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
    long long ans = 0;
    bitset<MAXN * 2> bs;
    bs[1] = true;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      bs >>= 1;
      sum += a[i];
      // cout << bs << endl;
      if (bs[0]) {
        ans = max(ans, sum - i);
      }
      bs |= (bs << a[i]);
    }
    for (int i = 1; i <= n; i++) {
      if (bs[i]) {
        ans = max(ans, sum - n + 1 - i);
      }
    }
    cout << ans << endl;
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
