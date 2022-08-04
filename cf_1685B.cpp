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
  int cnt_a, cnt_b, cnt_ab, cnt_ba;
  std::string str;

  bool get_ans() {
    int n = str.length();
    int num_a = 0, num_b = 0;
    for (int i = 0; i < n; i++) {
      if (str[i] == 'A') {
        num_a++;
      } else {
        num_b++;
      }
    }
    if (num_a != cnt_a + cnt_ab + cnt_ba) {
      return false;
    }
    if (num_b != cnt_b + cnt_ab + cnt_ba) {
      return false;
    }

    int sum = 0;
    multiset<int> len_ab, len_ba;
    for (int i = 0; i < n; ) {
      int j = i + 1;
      while(j < n && str[j - 1] != str[j]) {
        j++;
      }

      int len = j - i;
      if (len % 2 == 0) {
        if (str[i] == 'A') {
          len_ab.insert(len);
        } else {
          len_ba.insert(len);
        }
      } else {
        sum += len / 2;
      }

      i = j;
    }

    for (int len : len_ab) {
      if (cnt_ab >= len / 2) {
        cnt_ab -= len / 2;
      } else {
        len -= cnt_ab * 2;
        cnt_ab = 0;
        cnt_ba -= min(len / 2 - 1, cnt_ba);
      }
    }

    for (int len : len_ba) {
      if (cnt_ba >= len / 2) {
        cnt_ba -= len / 2;
      } else {
        len -= cnt_ba * 2;
        cnt_ba = 0;
        cnt_ab -= min(len / 2 - 1, cnt_ab);
      }
    }

    return sum >= cnt_ab + cnt_ba;
  }

 public:
  void read() {
    cin >> cnt_a >> cnt_b >> cnt_ab >> cnt_ba >> str;
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
