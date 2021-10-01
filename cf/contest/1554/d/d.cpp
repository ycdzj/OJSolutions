#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
public:
    void read() {
        cin >> n;
    }
    void solve() {
        if(n == 1) {
            cout << 'a' << endl;
        } else if(n & 1) {
            cout << string(n / 2, 'a') << "bc" << string(n / 2 - 1, 'a') << endl;
        } else {
            cout << string(n / 2, 'a') << "b" << string(n / 2 - 1, 'a') << endl;
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