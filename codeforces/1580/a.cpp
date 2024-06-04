#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n, m;
    vector<vector<int>> board;
public:
    void read() {
        cin >> n >> m;
        board.assign(n + 1, vector<int>(m + 1));
        for(int i = 1; i <= n; i++) {
            string str;
            cin >> str;
            for(int j = 1; j <= m; j++) {
                board[i][j] = str[j - 1] - '0';
            }
        }
    }
    void solve() {
        int ans = 1e9;
        for(int i1 = 1; i1 + 2 <= n; i1++) {
            vector<int> a(m + 1), b(m + 1), s(m + 1), c(m + 1);
            for(int j = 1; j <= m; j++) {
                a[j] = 1 - board[i1][j];
                a[j] += 1 - board[i1 + 1][j];
            }
            for(int i2 = i1 + 2; i2 <= n; i2++) {
                for(int j = 1; j <= m; j++) {
                    if(board[i2 - 1][j]) {
                        a[j]++;
                    } else {
                        a[j]--;
                        b[j]++;
                    }
                    a[j] += 1 - board[i2][j];
                    s[j] = s[j - 1] + a[j];
                    c[j] = b[j] + s[j - 1];
                }
                if(i2 - i1 + 1 < 5) {
                    continue;
                }
                for(int j = m - 1; j >= 1; j--) {
                    c[j] = min(c[j], c[j + 1]);
                }
                for(int j = 1; j + 3 <= m; j++) {
                    ans = min(ans, b[j] - s[j] + c[j + 3]);
                }
            }
        }
        cout << ans << endl;
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