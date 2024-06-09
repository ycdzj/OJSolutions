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
    int x, y;

   public:
    void read() {
        cin >> x >> y;
    }

    void solve() {
        int z = x ^ y;
        int ans = z;
        for (int i = 30; i >= 0; i--) {
            int d = (1 << i);
            if (ans > d) {
                ans -= d;
            } else if (ans == d) {
                break;
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
