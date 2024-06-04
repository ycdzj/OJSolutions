#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    static char get_inv(char c) {
        if(c == 'B') {
            return 'R';
        }
        if(c == 'R') {
            return 'B';
        }
        return '?';
    }

    int n;
    string a;

    void fill() {
        for(int i = 1; i < n; i++) {
            if(a[i] == '?') {
                a[i] = get_inv(a[i - 1]);
            }
        }
        for(int i = n - 2; i >= 0; i--) {
            if(a[i] == '?') {
                a[i] = get_inv(a[i + 1]);
            }
        }
    }
public:
    void read() {
        cin >> n >> a;
    }
    void solve() {
        fill();
        if(a[0] == '?') {
            a[0] = 'R';
        }
        fill();
        cout << a << endl;
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