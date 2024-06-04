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

const int INF = 1e9;

class Solver {
  string s;

  int count_combines(int x) { return x * (x - 1) / 2; }

 public:
  void read() { cin >> s; }

  void solve() {
    int n = s.length();
    vector<int> cnt[2];
    cnt[0].resize(n + 1);
    cnt[1].resize(n + 1);
    for (int i = n - 1; i >= 0; i--) {
      cnt[s[i] - '0'][i]++;
      cnt[0][i] += cnt[0][i + 1];
      cnt[1][i] += cnt[1][i + 1];
    }

    int m = count_combines(n) - count_combines(cnt[0][0]) -
            count_combines(cnt[1][0]);

    vector<vector<int>> f[3];
    for (int i = 0; i < 3; i++) {
      f[i].resize(n);
      for (int j = 0; j < n; j++) {
        f[i][j].resize(m + 1, INF);
      }
    }

    for (int i = 0; i < n; i++) {
      f[0][i][0] = 0;
      f[2][i][0] = 0;
    }

    for (int d = 1; d < n; d++) {
      int cur = d % 3;
      int pre = (d - 1) % 3;
      int ppre = (d + 1) % 3;
      for (int i = 0; i + d < n; i++) {
        int j = i + d;
        int cnt_0 = cnt[0][i] - cnt[0][j + 1];
        int cnt_1 = cnt[1][i] - cnt[1][j + 1];
        int cur_cnt = 0;
        if (s[j] == '0') {
          cur_cnt += cnt_1;
        }
        if (s[i] == '1') {
          cur_cnt += cnt_0;
        }
        if (s[j] == '0' && s[i] == '1') {
          cur_cnt--;
        }
        for (int x = 0; x <= m; x++) {
          f[cur][i][x] = INF;
          if (s[j] == '1') {
            if (x - cnt_0 >= 0) {
              f[cur][i][x] = min(f[cur][i][x], f[pre][i][x - cnt_0]);
            }
          } else {
            f[cur][i][x] = min(f[cur][i][x], f[pre][i][x]);
          }
          if (s[i] == '0') {
            if (x - cnt_1 >= 0) {
              f[cur][i][x] = min(f[cur][i][x], f[pre][i + 1][x - cnt_1]);
            }
          } else {
            f[cur][i][x] = min(f[cur][i][x], f[pre][i + 1][x]);
          }

          if (x - cur_cnt >= 0) {
            f[cur][i][x] = min(f[cur][i][x], f[ppre][i + 1][x - cur_cnt] + 1);
          }
        }
      }
    }

    cout << f[(n - 1) % 3][0][m / 2] << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  int t = 1;
  // cin >> t;
  while (t--) {
    Solver solver;
    solver.read();
    solver.solve();
  }
  return 0;
}
