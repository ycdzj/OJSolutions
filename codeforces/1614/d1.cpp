#include <iostream>
#include <vector>
#include <numeric>
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
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        int c = accumulate(a.begin(), a.end(), 1, [](int x, int y){return max(x, y);});

        vector<int> cnt(c + 1);
        for(int val : a) {
            cnt[val]++;
        }

        vector<long long> f(c + 1);
        vector<int> cnt_sum(c + 1);
        for(int i = c; i >= 1; i--) {
            for(int j = i; j <= c; j += i) {
                cnt_sum[i] += cnt[j];
            }

            f[i] = (long long)i * cnt[i];
            for(int j = 2 * i; j <= c; j += i) {
                f[i] = max(f[i], f[j] + (long long)i * (cnt_sum[i] - cnt_sum[j]));
            }
        }

        cout << f[1] << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}