#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<int> a;

    bool get_ans() {
        vector<int> prefix(n - 1);
        for(int i = 0, sum = 0; i + 1 < n; i++) {
            int diff = a[i + 1] - a[i];
            if(diff > 0) {
                sum += diff;
            }
            prefix[i] = sum;
        }

        vector<int> suffix(n - 1);
        for(int i = n - 2, sum = 0; i >= 0; i--) {
            int diff = a[i + 1] - a[i];
            if(diff < 0) {
                sum += diff;
            }
            suffix[i] = sum;
        }

        for(int i = 0; i < n; i++) {
            int sum = 0;
            if(i < n - 1) {
                sum -= suffix[i];
            }
            if(i - 1 >= 0) {
                sum += prefix[i - 1];
            }
            if(sum > a[i]) {
                return false;
            }
        }
        return true;
    }
public:
    void read() {
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
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