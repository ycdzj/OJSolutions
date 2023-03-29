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
  long long n, x, p;

 public:
  void read() { cin >> n >> x >> p; }

  void solve() {
    x = (n - x) % n;

    vector<long long> s(n + 1);
    s[0] = 0;
    for (long long i = 1; i <= n; i++) {
      s[i] = (s[i - 1] + i) % n;
    }

    vector<long long> cnt(n, -1);
    long long flag = -1;
    for (long long cur = 0, i = 0; i <= p && cnt[cur] == -1;) {
      cnt[cur] = i;
      cur = (cur + s[n]) % n;
      i += n;
      if (i <= p && cur == 0) {
        flag = i;
      }
    }

    bool ans = false;
    for (long long i = 0; i < n; i++) {
      long long y = (x + n - s[i]) % n;
      if (cnt[y] != -1) {
        long long val = i + cnt[y];
        if (0 < val && val <= p) {
          ans = true;
          break;
        }
      }
    }

    if (flag != -1) {
      if (x == 0) {
        ans = true;
      }
    }

    if (ans) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
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
