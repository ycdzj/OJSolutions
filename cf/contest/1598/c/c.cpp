#include <iostream>
#include <numeric>
#include <functional>
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
        map<int, int> cnt;
        for(int val : a) {
            cnt[val]++;
        }
        long long s = accumulate(a.begin(), a.end(), 0ll);
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            long long naj = 2 * s - (long long)n * a[i];
            if(naj % n != 0) {
                continue;
            }
            int aj = naj / n;
            if(a[i] == aj) {
                ans += (long long)cnt[a[i]] * (cnt[a[i]] - 1) / 2;
            } else {
                ans += (long long)cnt[a[i]] * cnt[aj];
            }
            cnt[a[i]] = 0;
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