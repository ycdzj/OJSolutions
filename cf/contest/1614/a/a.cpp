#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int n, l, r, k;
    vector<int> a;

public:
    void read() {
        cin >> n >> l >> r >> k;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        vector<int> b;
        for(int val : a) {
            if(l <= val && val <= r) {
                b.push_back(val);
            }
        }
        sort(b.begin(), b.end());

        int ans = 0;
        for(int val : b) {
            k -= val;
            if(k < 0) {
                break;
            }
            ans++;
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