#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n, m;
public:
    void read() {
        cin >> n >> m;
    }
    void solve() {
        int ans = 2e9;
        for(int i = 30; i >= 0; i--) {
            if(!(m >> i & 1)) {
                int k = (n ^ m);
                k ^= (1 << i);
                k |= ((1 << i) - 1);
                k ^= ((1 << i) - 1);

                ans = min(ans, k);
            }
        }
        cout << ans << endl;
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