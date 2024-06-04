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

const long long STEP = 1e12;

class Solver {
  string s;

 public:
  void read() { cin >> s; }

  void solve() {
    s = "0" + s;
    int total_0 = count(s.begin(), s.end(), '0');

    long long ans = 1e18;
    int cur_0 = 0, cur_1 = 0;
    for (int i = 0, pre = -1; i < s.length(); i++) {
      if (s[i] == '0') {
        cur_0++;
        long long cur_ans = (total_0 - cur_0 + cur_1) * (STEP + 1) - (i - pre - 1);
        ans = min(ans, cur_ans);
        pre = i;
      } else {
        cur_1++;
      }
    }

    cout << ans << endl;
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
