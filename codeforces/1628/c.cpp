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

  int get_ans() {
    vector<vector<int>> b(n, vector<int>(n));
    int ans = 0;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (b[i - 1][j] == 0) {
          ans ^= a[i][j];
          if (i + 1 < n) {
            b[i + 1][j] ^= 1;
          }
          if (j + 1 < n) {
            b[i][j + 1] ^= 1;
          }
          if (j - 1 >= 0) {
            b[i][j - 1] ^= 1;
          }
        }
      }
    }
    return ans;
  }

 public:
  void read() {
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
      a[i].resize(n);
      for (int j = 0; j < n; j++) {
        cin >> a[i][j];
      }
    }
  }

  void solve() {
    cout << get_ans() << endl;
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
