#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solver {
    int n;
    string a;
public:
    void read() {
        cin >> n >> a;
    }

    void solve() {
        int ans = 0;
        for(int i = 0, pre = -1; i < n; i++) {
            if (a[i] == '0') {
                if (pre != -1) {
                    int cur = 2 - (i - pre - 1);
                    ans += max(0, cur);
                }
                pre = i;
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