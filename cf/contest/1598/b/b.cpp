#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<vector<int>> a;

    bool check(int d1, int d2) {
        int cnt_1 = 0, cnt_2 = 0;
        for(int i = 0; i < n; i++) {
            if(a[i][d1] && a[i][d2]) {
                continue;
            }
            if(a[i][d1]) {
                cnt_1++;
            } else if(a[i][d2]) {
                cnt_2++;
            } else {
                return false;
            }
        }
        return cnt_1 <= n / 2 && cnt_2 <= n / 2;
    }
    bool get_ans() {
        for(int i = 0; i < 5; i++) {
            for(int j = i + 1; j < 5; j++) {
                if(check(i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
public:
    void read() {
        cin >> n;
        a.assign(n, vector<int>(5));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 5; j++) {
                cin >> a[i][j];
            }
        }
    }
    void solve() {
        if(get_ans()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
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