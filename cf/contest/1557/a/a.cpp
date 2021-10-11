#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
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
        sort(a.begin(), a.end());
        long long sum = accumulate(a.begin(), a.end() - 1, 0ll);
        cout << setprecision(10) << (double)sum / (n - 1) + a[n - 1] << endl;
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