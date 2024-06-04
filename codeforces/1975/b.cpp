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
        int j = 1;
        while (j < n && a[j] % a[0] == 0) {
            j++;
        }
        for (int k = j + 1; k < n; k++) {
            if (a[k] % a[0] != 0 && a[k] % a[j] != 0) {
                return false;
            }
        }
        return true;
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
        sort(a.begin(), a.end());
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
