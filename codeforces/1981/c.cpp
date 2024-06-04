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

int l(int x) {
    for (int i = 30; i >= 0; i--) {
        if (x >> i) {
            return i + 1;
        }
    }
    assert(false);
    return 0;
}

int lcp(int x, int y) {
    int lx = l(x);
    int ly = l(y);
    int len = 0;
    while (len < lx && len < ly) {
        int val_x = (x >> (lx - len - 1) & 1);
        int val_y = (y >> (ly - len - 1) & 1);
        if (val_x == val_y) {
            len++;
        } else {
            break;
        }
    }
    return len;
}

class Solver {
    int n;
    vector<int> a;

    void fix() {
        for (int i = 1; i < n; i++) {
            if (a[i] == -1 && a[i - 1] != -1) {
                if (a[i - 1] == 1) {
                    a[i] = 2;
                } else {
                    a[i] = a[i - 1] / 2;
                }
            }
        }
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
        for (int i = -1, j = 0; j < n; j++) {
            if (a[j] != -1) {
                if (i != -1) {
                    // [i, j]
                    int li = l(a[i]);
                    int lj = l(a[j]);
                    int lc = lcp(a[i], a[j]);
                    int x = li - lc;
                    int y = lj - lc;
                    int z = j - i - x - y;
                    if (z % 2 != 0 || z < 0) {
                        cout << -1 << endl;
                        return;
                    }
                    z /= 2;
                    int k = i + 1;
                    while (z--) {
                        if (a[k - 1] == 1) {
                            a[k] = 2;
                        } else {
                            a[k] = a[k - 1] / 2;
                        }
                        a[k + 1] = a[k - 1];
                        k += 2;
                    }
                    for (; k < j; k++) {
                        if (x > 0) {
                            a[k] = a[k - 1] / 2;
                            x--;
                        } else {
                            assert(y > 0);
                            a[k] = a[j] >> (y - 1);
                            y--;
                        }
                    }
                }
                i = j;
            }
        }
        fix();
        reverse(a.begin(), a.end());
        fix();
        reverse(a.begin(), a.end());
        if (a[0] == -1) {
            a[0] = 1;
            fix();
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
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
