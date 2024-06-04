#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<vector<int>> rows;
    vector<int> cnt_by_col;
public:
    void read() {
        cin >> n;
        rows.assign(n + 1, {});
        cnt_by_col.assign(n + 1, {});
        for(int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            rows[a].push_back(b);
            cnt_by_col[b]++;
        }
    }
    void solve() {
        long long ans = 0;
        for(int i = 1; i <= n; i++) {
            long long sum = 0, cnt = 0;
            for(int val : rows[i]) {
                ans += cnt * (cnt_by_col[val] - 1);
                ans += sum;

                cnt++;
                sum += cnt_by_col[val] - 1;
            }
        }
        ans = (long long)n * (n - 1) * (n - 2) / 6 - ans;
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