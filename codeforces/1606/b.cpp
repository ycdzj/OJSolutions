#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solver {
    long long n, k;

public:
    void read() {
        cin >> n >> k;
    }

    void solve() {
        long long cur_cnt = 1;
        long long cur_hour = 0;

        while(cur_cnt < n) {
            if(cur_cnt < k) {
                cur_cnt += cur_cnt;
                cur_hour++;
                continue;
            }

            long long hour_remain = (n - cur_cnt + k - 1) / k;
            cur_hour += hour_remain;
            break;
        }

        cout << cur_hour << endl;
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
