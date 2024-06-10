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

    bool get_ans() {
        int pre = s[0] - '0';
        for (int i = 1; i < s.length(); i++) {
            pre *= 10;
            pre += s[i] - '0';
            if (pre < 10) {
                return false;
            }
            if (pre > 19) {
                return false;
            }

            if (pre == 10) {
                pre = 0;
                continue;
            }
            if (pre == 19) {
                pre = 1;
                continue;
            }
            
            if (i + 1 < s.length()) {
                pre = 1;
            } else {
                pre = 0;
            }
        }
        return pre == 0;
    }

   public:
    void read() {
        cin >> s;
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
