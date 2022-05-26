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

struct G {
    vector<int> stats[9];

    G() {
        for (int i = 0; i < (1 << 8); i++) {
            stats[bitcount(i)].push_back(normalize(i));
        }
        for (int i = 0; i < 9; i++) {
            sort(stats[i].begin(), stats[i].end());
            stats[i].erase(unique(stats[i].begin(), stats[i].end()), stats[i].end());
        }
    }

    static int normalize(int x) {
        int res = x;
        for (int i = 0; i < 7; i++) {
            int low = (x & 1);
            x = (x >> 1 | (low << 7));
            res = max(res, x);
        }
        return res;
    }
    static int bitcount(int x) {
        int cnt = 0;
        while (x) {
            if (x & 1) {
                cnt++;
            }
            x >>= 1;
        }
        return cnt;
    }
} g;

class Solver {
public:
    void read() {
    }

    void solve() {
    }
};

int main() {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        cout << g.stats[i].size() << endl;
        sum += (1 << g.stats[i].size());
    }
    cout << sum << endl;
    return 0;
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
