#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

constexpr long long INF = 2e18;

class Solver {
    int n;
    vector<long long> a;
    long long sum_of_a;

    int m;
    vector<pair<long long, long long>> b;

    long long get_ans(long long x, long long y, int p) {
        long long ans = 0;

        if(a[p] < x) {
            ans += x - a[p];
        }

        long long cur_sum = sum_of_a - a[p];
        if(cur_sum < y) {
            ans += y - cur_sum;
        }

        return ans;
    }

public:
    void read() {
        cin >> n;
        a.resize(n);
        sum_of_a = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            sum_of_a += a[i];
        }

        cin >> m;
        b.resize(m);
        for(int i = 0; i < m; i++) {
            cin >> b[i].first >> b[i].second;
        }
    }

    void solve() {
        sort(a.begin(), a.end());

        for(int i = 0; i < m; i++) {
            long long ans = INF;

            int p = upper_bound(a.begin(), a.end(), b[i].first) - a.begin();
            if(p < n) {
                ans = min(ans, get_ans(b[i].first, b[i].second, p));
            }
            if(p - 1 >= 0) {
                ans = min(ans, get_ans(b[i].first, b[i].second, p - 1));
            }

            cout << ans << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    Solver solver;
    solver.read();
    solver.solve();
    return 0;
}