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

 public:
  void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
  }

  void solve() {
    set<int> cur;
    for (int i = 0; i < n; i++) {
      cur.insert(a[i]);
    }
    for (int i = n; i > 1; i--) {
      set<int> nxt;
      if (cur.size() == 1) {
        nxt.insert(0);
      } else {
        int pre_val = *cur.begin();
        for (auto itr = ++cur.begin(); itr != cur.end(); ++itr) {
          nxt.insert(*itr - pre_val);
          pre_val = *itr;
        }
        if (cur.size() < i) {
          nxt.insert(0);
        }
      }
      swap(cur, nxt);
    }
    cout << *cur.begin() << endl;
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
