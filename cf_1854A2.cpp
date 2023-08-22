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

vector<pair<int, int>> solve(vector<int> a) {
  int n = a.size();
  int cnt_negative = 0;
  int cnt_positive = 0;
  int max_val = -100;
  int min_val = 100;
  for (int val : a) {
    if (val < 0) {
      cnt_negative++;
    } else if (val > 0) {
      cnt_positive++;
    }
    max_val = max(max_val, val);
    min_val = min(min_val, val);
  }

  if (cnt_negative == 0 && cnt_positive == 0) {
    return {};
  }

  bool flag;
  if (max(cnt_positive, cnt_negative) <= 12) {
    flag = (min_val + max_val < 0);
  } else {
    flag = (cnt_negative > 12);
  }

  if (flag) {
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      b[i] = -a[n - 1 - i];
    }
    auto ans = solve(b);
    for (auto& pr : ans) {
      pr.first = n - 1 - pr.first;
      pr.second = n - 1 - pr.second;
    }
    return ans;
  }

  vector<pair<int, int>> ans;
  int idx = 0;
  for (int i = 1; i < n; i++) {
    if (a[idx] < a[i]) {
      idx = i;
    }
  }
  assert(a[idx] > 0);

  for (int i = 0; i < n; i++) {
    if (a[i] < 0) {
      while (a[idx] + a[i] < 0) {
        a[idx] += a[idx];
        ans.push_back({idx, idx});
      }
      ans.push_back({i, idx});
    }
  }

  for (int i = 1; i < n; i++) {
    ans.push_back({i, i - 1});
  }
  return ans;
}

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
    auto ans = ::solve(a);
    cout << ans.size() << endl;
    for (auto pr : ans) {
      cout << pr.first + 1 << ' ' << pr.second + 1 << endl;
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
