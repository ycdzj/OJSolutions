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
  string s;

  bool get_ans() {
    vector<int> cnt(26);
    for (char c : s) {
      cnt[c - 'a']++;
    }

    int cnt_odd = 0;
    for (int val : cnt) {
      if (val & 1) {
        cnt_odd++;
      }
    }

    return max(0, cnt_odd - 1) <= k && k <= n;
  }

 public:
  void read() { cin >> n >> k >> s; }

  void solve() {
    if (get_ans()) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
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
