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
    vector<int> cnt(n);
    for (int val : a) {
      if (val < n) {
        cnt[val]++;
      }
    }

    int min_val = n;
    for (int i = 0; i < n; i++) {
      if (cnt[i] == 0) {
        min_val = i;
        break;
      }
    }

    vector<int> mark(n + 1);
    int cur_mark = 0;
    vector<int> ans;
    for (int i = 0; i < n; ) {
      cur_mark++;
      int cnt_diff = 0;
      int j = i;
      int nxt_min_val = min_val;
      while (j == i || cnt_diff < min_val) {
        if (a[j] < min_val) {
          if (--cnt[a[j]] == 0) {
            nxt_min_val = min(nxt_min_val, a[j]);
          }
          if (mark[a[j]] != cur_mark) {
            mark[a[j]] = cur_mark;
            cnt_diff++;
          }
        }
        j++;
      }
      ans.push_back(min_val);
      min_val = nxt_min_val;
      i = j;
    }
    cout << ans.size();
    for (int val : ans) {
      cout << ' ' << val;
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
