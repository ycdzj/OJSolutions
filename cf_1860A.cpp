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

class Solver {
  string s;

 public:
  void read() { cin >> s; }

  void solve() {
    if (s.length() == 1 || s == "()") {
      cout << "NO" << endl;
      return;
    }

    int flag = 1;
    for (char c : s) {
      if (c == '(') {
        if (flag == 2) {
          flag = 3;
          break;
        }
      } else {
        if (flag == 1) {
          flag = 2;
        }
      }
    }

    cout << "YES" << endl;
    if (flag == 1 || flag == 2) {
      for (int i = 0; i < s.length(); i++) {
        cout << "()";
      }
      cout << endl;
    } else {
      for (int i = 0; i < s.length(); i++) {
        cout << "(";
      }
      for (int i = 0; i < s.length(); i++) {
        cout << ")";
      }
      cout << endl;
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
