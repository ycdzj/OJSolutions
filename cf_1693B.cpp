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
  vector<vector<int>> children;
  vector<pair<long long, long long>> val;
 public:
  void read() {
    cin >> n;
    children.resize(n + 1);
    val.resize(n + 1);
    for (int i = 2; i <= n; i++) {
      int par;
      cin >> par;
      children[par].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
      cin >> val[i].first >> val[i].second;
    }
  }

  pair<int, long long> get_ans(int root) {
    int cnt_op = 0;
    long long sum_val = 0;
    for (int child : children[root]) {
      pair<int, long long> ans = get_ans(child);
      cnt_op += ans.first;
      sum_val += ans.second;
    }

    if (sum_val < val[root].first) {
      return {cnt_op + 1, val[root].second};
    }
    return {cnt_op, min(val[root].second, sum_val)};
  }

  void solve() {
    cout << get_ans(1).first << endl;
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
