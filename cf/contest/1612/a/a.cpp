#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int x, y;

    pair<int, int> get_ans() {
        if((x + y) % 2 == 1) {
            return {-1, -1};
        }
        return {x / 2, (y + 1) / 2};
    }
public:
    void read() {
        cin >> x >> y;
    }

    void solve() {
        auto ans = get_ans();
        cout << ans.first << ' ' << ans.second << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}