#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    long long k, x;

    long long f(long long i) {
        if(i <= k) {
            return i * (i + 1) / 2;
        }
        return k * (k + 1) / 2 + (3 * k - i - 1) * (i - k) / 2;
    }
public:
    void read() {
        cin >> k >> x;
    }

    void solve() {
        long long l = 1, r = 2 * k - 1;
        while(l < r) {
            long long mid = l + (r - l) / 2;
            if(f(mid) >= x) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << l << endl;
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
