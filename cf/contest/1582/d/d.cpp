#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

int my_abs(int x) {
    if(x < 0) {
        return -x;
    }
    return x;
}

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
        int s = 0;
        for(int i = 0; i < n - 1; i++) {
            if((s + a[i] != 0 && my_abs(s + a[i]) < my_abs(s - a[i])) || s - a[i] == 0) {
                s += a[i];
                cout << a[n - 1] << ' ';
            } else {
                s -= a[i];
                cout << -a[n - 1] << ' ';
            }
        }
        cout << -s << endl;
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
