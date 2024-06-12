#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <class T>
T minmax(T val, T l, T r) {
    val = max(val, l);
    val = min(val, r);
    return val;
}

class Solver {
    int n, m;
    vector<string> board;

    void fix(int& i, int& j) {
        i = minmax(i, 1, n);
        j = minmax(j, 1, m);
    }

    vector<vector<int>> a;
    void update(int i1, int i2, int j1, int j2, int d) {
        fix(i1, j1);
        fix(i2, j2);
        a[i1][j1] += d;
        a[i2 + 1][j1] -= d;
        a[i1][j2 + 1] -= d;
        a[i2 + 1][j2 + 1] += d;
    }

    vector<vector<bool>> vis;
    void bfs(int i, int j, int& i1, int& i2, int& j1, int& j2, int& cnt) {
        i1 = i;
        i2 = i;

        j1 = j;
        j2 = j;

        cnt = 0;

        queue<pair<int, int>> que;
        vis[i][j] = true;
        que.emplace(i, j);
        while (!que.empty()) {
            int cur_i = que.front().first;
            int cur_j = que.front().second;
            que.pop();
            i1 = min(i1, cur_i);
            i2 = max(i2, cur_i);
            j1 = min(j1, cur_j);
            j2 = max(j2, cur_j);
            cnt++;

            const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for (int idx = 0; idx < 4; idx++) {
                int nxt_i = cur_i + dir[idx][0];
                int nxt_j = cur_j + dir[idx][1];

                if (1 <= nxt_i && nxt_i <= n) {
                    if (1 <= nxt_j && nxt_j <= m) {
                        if (!vis[nxt_i][nxt_j] && board[nxt_i][nxt_j] == '#') {
                            vis[nxt_i][nxt_j] = true;
                            que.emplace(nxt_i, nxt_j);
                        }
                    }
                }
            }
        }
    }

   public:
    void read() {
        cin >> n >> m;
        board.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> board[i];
            board[i].insert(board[i].begin(), '.');
        }
    }

    void solve() {
        a.assign(n + 2, vector<int>(m + 2));
        vis.assign(n + 1, vector<bool>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                if (vis[i][j]) {
                    continue;
                }
                int i1, i2, j1, j2, cnt;
                bfs(i, j, i1, i2, j1, j2, cnt);
                i1--;
                i2++;
                j1--;
                j2++;
                update(i1, i2, 1, m, cnt);
                update(1, n, j1, j2, cnt);
                update(i1, i2, j1, j2, -cnt);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j] += a[i - 1][j];
                a[i][j] += a[i][j - 1];
                a[i][j] -= a[i - 1][j - 1];
            }
        }

        vector<int> row(n + 1);
        vector<int> col(m + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (board[i][j] == '.') {
                    row[i]++;
                    col[j]++;
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int cur = row[i] + col[j];
                if (board[i][j] == '.') {
                    cur--;
                }
                cur += a[i][j];
                ans = max(ans, cur);
            }
        }

        cout << ans << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
