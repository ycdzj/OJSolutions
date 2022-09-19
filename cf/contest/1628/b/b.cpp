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
#include <cstdlib>

using namespace std;

class Solver {
  int n;
  vector<string> a;

  bool check(const string& str) {
    for (int i = 0; i < str.length() / 2; i++) {
      if (str[i] != str[str.length() - 1 - i]) {
        return false;
      }
    }
    return true;
  }

  bool get_ans() {
    set<string> s_full, s_prefix;
    for (int i = n - 1; i >= 0; i--) {
      if (check(a[i])) {
        return true;
      }
      if (s_full.count(a[i])) {
        return true;
      }
      if (a[i].length() == 3 && s_full.count(a[i].substr(0, 2))) {
        return true;
      }
      if (a[i].length() == 2 && s_prefix.count(a[i])) {
        return true;
      }
      reverse(a[i].begin(), a[i].end());
      s_full.insert(a[i]);
      if (a[i].length() == 3) {
        s_prefix.insert(a[i].substr(0, 2));;
      }
    }
    return false;
  }

 public:
  void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
  }

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
