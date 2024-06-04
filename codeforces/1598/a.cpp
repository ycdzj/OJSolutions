#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    string board[2];

    bool get_ans() {
        for(int i = 0; i < n; i++) {
            if(board[0][i] == '1' && board[1][i] == '1') {
                return false;
            }
        }
        return true;
    }
public:
    void read() {
        cin >> n >> board[0] >> board[1];
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