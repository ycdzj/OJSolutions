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

const long long INF = 1e18;

class Solver {
  int n;
  vector<pair<long long, long long>> vals;

 public:
  void read() {
    cin >> n;
    vals.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> vals[i].first >> vals[i].second;
    }
  }

  void solve() {
    sort(vals.begin(), vals.end());
    multiset<long long> s;
    vector<long long> low(n, -INF), up(n, INF);
    for (int i = 0; i < n; i++) {
      bool flag = (i > 0 && vals[i].first == vals[i - 1].first);
      if (flag) {
        s.insert(vals[i].second);
      }
      auto itr = s.upper_bound(vals[i].first);
      if (itr != s.begin()) {
        --itr;
        low[i] = *itr;
      }
      itr = s.lower_bound(vals[i].first);
      if (itr != s.end()) {
        up[i] = *itr;
      }
      if (!flag) {
        s.insert(vals[i].second);
      }
    }
    long long ans = INF;
    for (long long cur = -INF, i = n - 1; i >= 0; i--) {
      low[i] = max(low[i], cur);
      up[i] = max(up[i], cur);
      cur = max(cur, vals[i].second);
      ans = min(ans, abs(low[i] - vals[i].first));
      ans = min(ans, abs(up[i] - vals[i].first));
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
