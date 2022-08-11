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
  string str;
 public:
  void read() {
    cin >> n >> m >> str;
  }

  void solve() {
    vector<int> val(m);
    vector<bool> vis(m);
    for (int i = 0, pre = -1e9, ans = 0; i < n * m; i++) {
      if (str[i] == '1') {
        pre = i;
        if (!vis[i % m]) {
          vis[i % m] = true;
          ans++;
        }
      }
      if (i - m < pre) {
        val[i % m]++;
      }
      cout << val[i % m] + ans << ' ';
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
