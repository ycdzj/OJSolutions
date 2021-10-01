#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<int> a;
public:
    void read() {
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    void solve() {
        long long ans = 0;
        for(int i = 0; i + 1 < n; i++) {
            int min_val = min(a[i], a[i + 1]);
            int max_val = max(a[i], a[i + 1]);
            ans = max(ans, (long long)max_val * min_val);
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