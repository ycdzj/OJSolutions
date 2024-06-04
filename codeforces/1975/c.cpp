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
    int n;
    vector<int> a;

   public:
    void read() {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        int ans = 0;
        for (int i = 0; i + 1 < n; i++) {
            ans = max(ans, min(a[i], a[i + 1]));
        }
        for (int i = 0; i + 2 < n; i++) {
            int b[3] = {a[i], a[i + 1], a[i + 2]};
            sort(b, b + 3);
            ans = max(ans, b[1]);
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
