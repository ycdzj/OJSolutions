#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Solver {
    int n, m;
    vector<string> board;
    vector<vector<int>> ans;

    void flip(vector<pair<int, int>> positions) {
        vector<int> cur_ans;
        for(auto position : positions) {
            int i = position.first;
            int j = position.second;

            if(board[i][j] == '0') {
                board[i][j] = '1';
            } else {
                board[i][j] = '0';
            }

            cur_ans.push_back(i + 1);
            cur_ans.push_back(j + 1);
        }
        ans.push_back(cur_ans);
    }

    int count(int i, int j) {
        int cnt = 0;
        for(int di = 0; di < 2; di++) {
            for(int dj = 0; dj < 2; dj++) {
                if(board[i + di][j + dj] == '1') {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    void process_triple(int i, int j) {
        vector<pair<int, int>> positions;
        for(int di = 0; di < 2; di++) {
            for(int dj = 0; dj < 2; dj++) {
                if(board[i + di][j + dj] == '1') {
                    positions.emplace_back(i + di, j + dj);
                }
            }
        }
        flip(positions);
    }

    void process_double(int i, int j) {
        if(board[i][j] == '1' && board[i + 1][j + 1] == '1') {
            flip({{i, j}, {i + 1, j}, {i, j + 1}});
            process_triple(i, j);
            return;
        }
        if(board[i][j + 1] == '1' && board[i + 1][j] == '1') {
            flip({{i, j + 1}, {i, j}, {i + 1, j + 1}});
            process_triple(i, j);
            return;
        }
        if(board[i][j] == '1' && board[i][j + 1] == '1') {
            flip({{i, j}, {i + 1, j}, {i + 1, j + 1}});
            flip({{i, j + 1}, {i + 1, j}, {i + 1, j + 1}});
            return;
        }
        if(board[i + 1][j] == '1' && board[i + 1][j + 1] == '1') {
            flip({{i + 1, j}, {i, j}, {i, j + 1}});
            flip({{i + 1, j + 1}, {i, j}, {i, j + 1}});
            return;
        }
        if(board[i][j] == '1' && board[i + 1][j] == '1') {
            flip({{i, j}, {i, j + 1}, {i + 1, j + 1}});
            flip({{i + 1, j}, {i, j + 1}, {i + 1, j + 1}});
            return;
        }
        flip({{i, j + 1}, {i, j}, {i + 1, j}});
        flip({{i + 1, j + 1}, {i, j}, {i + 1, j}});
    }

    void process_single(int i, int j) {
        for(int di = 0; di < 2; di++) {
            for(int dj = 0; dj < 2; dj++) {
                if(board[i + di][j + dj] == '1') {
                    vector<pair<int, int>> positions;
                    positions.emplace_back(i + di, j + dj);
                    positions.emplace_back(i + di, j + 1 - dj);
                    positions.emplace_back(i + 1 - di, j + dj);
                    flip(positions);
                    process_double(i, j);
                    return;
                }
            }
        }
    }
    
    void process_quad(int i, int j) {
        flip({{i, j}, {i + 1, j}, {i, j + 1}});
        process_single(i, j);
    }

    void solve() {
        cin >> n >> m;

        board.assign(n, string());
        for(int i = 0; i < n; i++) {
            cin >> board[i];
        }

        if(n & 1) {
            for(int j = 0; j < m; j++) {
                if(board[0][j] == '1') {
                    vector<pair<int, int>> positions;
                    positions.emplace_back(0, j);
                    positions.emplace_back(1, j);
                    if(j + 1 < m) {
                        positions.emplace_back(1, j + 1);
                    } else {
                        positions.emplace_back(1, j - 1);
                    }

                    flip(positions);
                }
            }
        }

        if(m & 1) {
            for(int i = 0; i < n; i++) {
                if(board[i][0] == '1') {
                    vector<pair<int, int>> positions;
                    positions.emplace_back(i, 0);
                    positions.emplace_back(i, 1);
                    if(i + 1 < n) {
                        positions.emplace_back(i + 1, 1);
                    } else {
                        positions.emplace_back(i - 1, 1);
                    }
                    flip(positions);
                }
            }
        }

        for(int i = (n & 1); i + 1 < n; i += 2) {
            for(int j = (m & 1); j + 1 < m; j += 2) {
                int cnt = count(i, j);
                if(cnt == 1) {
                    process_single(i, j);
                } else if(cnt == 2) {
                    process_double(i, j);
                } else if(cnt == 3) {
                    process_triple(i, j);
                } else if(cnt == 4) {
                    process_quad(i, j);
                }
            }
        }

        cout << ans.size() << endl;

        for(auto &indices : ans) {
            for(auto &index : indices) {
                cout << index << ' ';
            }
            cout << endl;
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        Solver solver;
        solver.solve();
    }
    return 0;
}
