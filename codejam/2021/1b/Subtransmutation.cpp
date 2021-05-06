#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool check(int n, int a, int b, const vector<int> &u, int idx) {
    vector<int> cnt(idx + 1);
    cnt[idx] = 1;
    for(int i = idx; i >= 1; i--) {
        if(i <= n) {
            if(u[i] > cnt[i]) {
                return false;
            }
            cnt[i] -= u[i];
        }
        if(i - a >= 1) {
            cnt[i - a] += cnt[i];
        }
        if(i - b >= 1) {
            cnt[i - b] += cnt[i];
        }
    }
    return true;
}

int solve() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> u(n + 1);
    int st = 1;
    for(int i = 1; i <= n; i++) {
        cin >> u[i];
        if(u[i] > 0) {
            st = i;
        }
    }
    for(int i = st; i <= 1000; i++) {
        if(check(n, a, b, u, i)) {
            return i;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        int ans = solve();
        if(ans == -1) {
            cout << "Case #" << i << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << i << ": " << ans << endl;
        }
    }
    return 0;
}