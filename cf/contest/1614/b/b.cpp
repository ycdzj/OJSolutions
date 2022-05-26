#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>

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
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            b[i] = i;
        }
        sort(b.begin(), b.end(), [&](int x, int y) { return a[x] > a[y]; });

        vector<int> idx(n);
        long long ans = 0;
        for(int i = 0; i < n; i += 2) {
            idx[b[i]] = i / 2 + 1;
            ans += (long long)(i / 2 + 1) * a[b[i]];
            if(i + 1 < n) {
                idx[b[i + 1]] = -(i / 2 + 1);
                ans += (long long)(i / 2 + 1) * a[b[i + 1]];
            }
        }

        cout << ans * 2 << endl;
        cout << 0;
        for(int val : idx) {
            cout << ' ' << val;
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