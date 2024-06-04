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
    int n, m;

   public:
    void read() {
        cin >> n >> m;
    }

    void solve() {
        int l = n - m;
        int r = n + m;
        int ans = 0;
        for (int i = 0; i <= 30; i++) {
            // [n - m, n + m]
            int len = 1 << i;
            int ll = l / len;
            int rr = r / len;
            if (ll == rr && ll % 2 == 0) {
                continue;
            }
            ans |= len;
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
