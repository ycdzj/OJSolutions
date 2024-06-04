#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

class Solver {
    int n;
    vector<int> a;

    bool check_entire() {
        int max_a = *max_element(a.begin(), a.end());
        int cur = 1;
        for (int val : a) {
            int g = gcd(cur, val);
            if ((long long)cur / g * val > max_a) {
                return true;
            }
            cur = cur / g * val;
        }
        return false;
    }

    int check_factor(int f) {
        int cur_lcm = 1;
        int cnt = 0;
        for (int val : a) {
            if (val == f) {
                return 0;
            }
            if (f % val == 0) {
                cnt++;
                cur_lcm = cur_lcm / gcd(cur_lcm, val) * val;
            }
        }
        if (cur_lcm == f) {
            return cnt;
        }
        return 0;
    }

   public:
    void read() {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        int ans;
        if (check_entire()) {
            ans = n;
        } else {
            ans = 0;
            int max_a = *max_element(a.begin(), a.end());
            for (int i = 1; i <= max_a / i; i++) {
                if (max_a % i == 0) {
                    ans = max(ans, check_factor(i));
                    ans = max(ans, check_factor(max_a / i));
                }
            }
        }

        cout << ans << endl;
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
