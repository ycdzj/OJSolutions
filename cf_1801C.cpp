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
  vector<vector<int>> a;

 public:
  void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      int k;
      cin >> k;
      a[i].resize(k);
      for (int j = 0; j < k; j++) {
        cin >> a[i][j];
      }
    }
  }

  void solve() {
    vector<pair<int, int>> prs;
    for (int i = 0; i < n; i++) {
      int max_val = 0;
      for (int val : a[i]) {
        max_val = max(max_val, val);
      }
      prs.push_back({max_val, i});
    }
    sort(prs.begin(), prs.end());

    std::map<int, int> max_vals;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int cur = 0;
      int cnt = 0;
      for (int val : a[prs[i].second]) {
        if (cur < val) {
          cur = val;
          cnt++;

          auto itr = max_vals.lower_bound(val);
          if (itr != max_vals.begin()) {
            --itr;
            cnt = max(cnt, itr->second + 1);
          }
        }
      }
      max_vals[cur] = max(max_vals[cur], cnt);
      ans = max(ans, cnt);
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
