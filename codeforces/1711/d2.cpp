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
  int n, m;
  vector<pair<int, int>> rains;

 public:
  void read() {
    cin >> n >> m;
    rains.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> rains[i].first >> rains[i].second;
    }
  }

  void solve() {
    vector<pair<int, int>> pos;
    for (auto [x, p] : rains) {
      pos.emplace_back(x - p, 0);
      pos.emplace_back(x, 1);
      pos.emplace_back(x + p, 2);
    }
    sort(pos.begin(), pos.end());

    long long cur_rain = 0;
    long long cur_pos = 0;
    long long cur_delta = 0;
    long long min_pos = 1e18, max_pos = -1e18;
    for (auto [p, t] : pos) {
      cur_rain += cur_delta * (p - cur_pos);
      cur_pos = p;

      if (t == 0) {
        cur_delta++;
      } else if (t == 1) {
        cur_delta -= 2;
      } else {
        cur_delta++;
      }

      if (cur_rain > m) {
        long long d = cur_rain - m;
        min_pos = min(min_pos, cur_pos - d);
        max_pos = max(max_pos, cur_pos + d);
      }
    }

    for (auto [x, p] : rains) {
      if (x - p <= min_pos && max_pos <= x + p) {
        cout << '1';
      } else {
        cout << '0';
      }
    }
    cout << endl;
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
