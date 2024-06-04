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

    bool get_ans() {
        int cnt = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (a[i] > a[i + 1]) {
                cnt++;
            }
        }
        if (cnt > 1) {
            return false;
        }
        if (cnt == 0) {
            return true;
        }
        return a[n - 1] <= a[0];
    }

   public:
    void read() {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        if (get_ans()) {
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
