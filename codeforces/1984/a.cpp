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
        if (a[0] == a[n - 1]) {
            cout << "NO" << endl;
            return;
        }
        cout << "YES" << endl;
        if (a[1] < a[n - 1]) {
            cout << 'B';
            for (int i = 1; i < n; i++) {
                cout << 'R';
            }
            cout << endl;
            return;
        }
        assert(a[0] < a[1]);
        for (int i = 1; i < n; i++) {
            cout << 'R';
        }
        cout << 'B';
        cout << endl;
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
