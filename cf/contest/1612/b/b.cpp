#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int n, a, b;
public:
    void read() {
        cin >> n >> a >> b;
    }

    void solve() {
        if(a > b + 1) {
            cout << -1 << endl;
            return;
        }
        int cnt_l = a - 1;
        int cnt_r = n - b;
        if(a < b) {
            cnt_l++;
            cnt_r++;
        }
        if(cnt_l > n / 2 || cnt_r > n / 2) {
            cout << -1 << endl;
            return;
        }
        for(int i = b + 1; i <= n; i++) {
            cout << i << ' ';
        }
        for(int i = a; i <= b; i++) {
            cout << i << ' ';
        }
        for(int i = 1; i <= a - 1; i++) {
            cout << i << ' ';
        }
        cout << endl;
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