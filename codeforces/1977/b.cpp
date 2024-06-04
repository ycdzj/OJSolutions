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
    int x;

   public:
    void read() {
        cin >> x;
    }

    void solve() {
        vector<int> a(31);
        for (int i = 0; i < 30; i++) {
            a[i] = (x >> i & 1);
        }
        for (int i = 0; i < 31; i++) {
            if (a[i] == 0) {
                continue;
            }
            int j = i + 1;
            while (j < 31 && a[j] != 0) {
                j++;
            }
            if (j - i >= 2) {
                assert(j < 31);
                a[i] = -1;
                for (int k = i + 1; k < j; k++) {
                    a[k] = 0;
                }
                a[j] = 1;
            }
            i = j - 1;
        }

        cout << a.size() << endl;
        for (int val : a) {
            cout << val << ' ';
        }
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
