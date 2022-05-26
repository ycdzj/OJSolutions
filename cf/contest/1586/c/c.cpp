#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int n, m, q;
    vector<string> board;

public:
    void read() {
        cin >> n >> m;
        board.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> board[i];
        }
        cin >> q;
    }

    void solve() {
        vector<int> a(m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(board[i][j] == 'X') {
                    int i2 = i + 1;
                    int j2 = j - 1;
                    if(i2 < n && j2 >= 0) {
                        if(board[i2][j2] == 'X') {
                            a[j] = 1;
                        }
                    }
                }
            }
        }
        for(int j = 1; j < m; j++) {
            a[j] += a[j - 1];
        }
        while(q--) {
            int l, r;
            cin >> l >> r;
            --l;
            --r;

            // a(l, r] == 0 ?
            int s = a[r] - a[l];
            if(s == 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}