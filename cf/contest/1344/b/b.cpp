#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n, m;
    vector<string> board;

    bool check_single_interval() {
        for(int i = 0; i < n; i++) {
            int cnt = 0;
            for(int j = 0; j < m; j++) {
                char pre = '.';
                if(j - 1 >= 0) {
                    pre = board[i][j - 1];
                }
                if(pre == '.' && board[i][j] == '#') {
                    cnt++;
                }
            }
            if(cnt > 1) {
                return false;
            }
        }

        for(int j = 0; j < m; j++) {
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                char pre = '.';
                if(i - 1 >= 0) {
                    pre = board[i - 1][j];
                }
                if(pre == '.' && board[i][j] == '#') {
                    cnt++;
                }
            }
            if(cnt > 1) {
                return false;
            }
        }

        return true;
    }

    bool check_black(int i, int j) {
        return 0 <= i && i < n && 0 <= j && j < m && board[i][j] == '#';
    }

    bool check_row_col() {
        vector<bool> vis_row(n), vis_col(m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(check_black(i, j)) {
                    vis_row[i] = true;
                    vis_col[j] = true;
                }
            }
        }

        int cnt_row = 0;
        for(int i = 0; i < n; i++) {
            if(!vis_row[i]) {
                cnt_row++;
            }
        }

        int cnt_col = 0;
        for(int j = 0; j < m; j++) {
            if(!vis_col[j]) {
                cnt_col++;
            }
        }

        if(cnt_row == 0 && cnt_col == 0) {
            return true;
        }
        if(cnt_row > 0 && cnt_col > 0) {
            return true;
        }
        return false;
    }

    void bfs(vector<vector<bool>> &vis, int si, int sj) {
        queue<pair<int, int>> que;

        vis[si][sj] = true;
        que.emplace(si, sj);

        while(!que.empty()) {
            auto [ui, uj] = que.front();
            que.pop();

            pair<int, int> next_pos[] = {
                {ui + 1, uj},
                {ui - 1, uj},
                {ui, uj + 1},
                {ui, uj - 1},
            };

            for(auto [vi, vj] : next_pos) {
                if(!check_black(vi, vj)) {
                    continue;
                }
                if(!vis[vi][vj]) {
                    vis[vi][vj] = true;
                    que.emplace(vi, vj);
                }
            }
        }
    }

    int count_components() {
        vector<vector<bool>> vis(n, vector<bool>(m));
        int cnt = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(check_black(i, j) && !vis[i][j])  {
                    bfs(vis, i, j);
                    cnt++;
                }
            }
        }

        return cnt;
    }

public:
    void read() {
        cin >> n >> m;
        board.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> board[i];
        }
    }
    void solve() {
        if(!check_single_interval()) {
            cout << -1 << endl;
            return;
        }
        if(!check_row_col()) {
            cout << -1 << endl;
            return;
        }
        cout << count_components() << endl;
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