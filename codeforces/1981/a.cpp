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
    int l, r;

   public:
    void read() {
        cin >> l >> r;
    }

    void solve() {
        for (int i = 30; i >= 0; i--) {
            int x = 1 << i;
            if (l <= x && x <= r) {
                cout << i << endl;
                return;
            }
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
