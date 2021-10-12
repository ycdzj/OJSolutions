#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n, m, q;
    vector<vector<bool>> board;
    vector<vector<array<long long, 2>>> f;
    long long sum = 0;

    long long get(int i, int j) {
        if(f[i][j][0] > 0) {
            return f[i][j][0] + f[i][j][1] - 1;
        }
        return 0;
    }

    void calc(int i, int j) {
        sum -= get(i, j);

        if(board[i][j]) {
            f[i][j][0] = 0;
            f[i][j][1] = 0;
        } else {
            f[i][j][0] = 1;
            if(i + 1 <= n && !board[i + 1][j]) {
                f[i][j][0] += f[i + 1][j][1];
            }

            f[i][j][1] = 1;
            if(j + 1 <= m && !board[i][j + 1]) {
                f[i][j][1] += f[i][j + 1][0];
            }
        }

        sum += get(i, j);
    }

    bool check(int i, int j) {
        return 1 <= i && i <= n && 1 <= j && j <= m;
    }

    void init() {
        for(int i = n; i >= 1; i--) {
            for(int j = m; j >= 1; j--) {
                calc(i, j);
            }
        }
    }

    void update(int r, int c, bool val) {
        board[r][c] = val;
        calc(r, c);
        for(int d = 1; ; d++) {
            int i = r - d;
            int j = c - d;

            bool flag = false;
            if(check(i + 1, j)) {
                calc(i + 1, j);
                flag = true;
            }
            if(check(i, j + 1)) {
                calc(i, j + 1);
                flag = true;
            }
            if(check(i, j)) {
                calc(i, j);
                flag = true;
            }
            if(!flag) {
                break;
            }
        }
    }
public:
    void read() {
        cin >> n >> m >> q;
        board.assign(n + 1, vector<bool>(m + 1));
        f.assign(n + 1, vector<array<long long, 2>>(m + 1));
    }
    void solve() {
        init();
        while(q--) {
            int r, c;
            cin >> r >> c;
            update(r, c, !board[r][c]);
            cout << sum << endl;
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