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
    int e, w;
    vector<vector<int>> a;

public:
    void read() {
        cin >> e >> w;
        a.assign(e, vector<int>(w));
        for (int i = 0; i < e; i++) {
            for (int j = 0; j < w; j++) {
                cin >> a[i][j];
            }
        }
    }

    void solve() {
        vector<vector<int>> g(e, vector<int>(e));
        for (int l = 0; l < e; l++) {
            vector<int> cur_min(w, 1e9);
            for (int r = l; r < e; r++) {
                for (int i = 0; i < w; i++) {
                    cur_min[i] = min(cur_min[i], a[r][i]);
                }
                g[l][r] = accumulate(cur_min.begin(), cur_min.end(), 0);
            }
        }

        vector<vector<int>> f(e, vector<int>(e));
        for (int d = 1; d < e; d++) {
            for (int l = 0, r = d; r < e; l++, r++) {
                f[l][r] = 1e9;
                for (int m = l; m < r; m++) {
                    f[l][r] = min(f[l][r], f[l][m] + f[m + 1][r] + (g[l][m] + g[m + 1][r] - 2 * g[l][r]) * 2);
                }
            }
        }

        cout << f[0][e - 1] + g[0][e - 1] * 2 << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        Solver solver;
        solver.read();
        cout << "Case #" << i << ": ";
        solver.solve();
    }
    return 0;
}
