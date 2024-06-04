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

  bool get_ans() {
    int offset;
    if (auto itr = find(a.begin(), a.end(), 1); itr == a.end()) {
      return false;
    } else {
      offset = itr - a.begin();
    }

    for (int i = 1; i < n; i++) {
      int idx = (offset + i) % n;
      int pre_idx = (offset + i - 1) % n;
      if (a[idx] == 1 || a[idx] > a[pre_idx] + 1) {
        return false;
      }
    }

    return true;
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