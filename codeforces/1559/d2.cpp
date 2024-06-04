#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class DisjointSet {
    vector<int> f;
public:
    explicit DisjointSet(int n) {
        f.resize(n);
        for(int i = 0; i < n; i++) {
            f[i] = i;
        }
    }

    int find(int x) {
        if(f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        f[x] = y;
    }
};

class Matrix {
    static int merge(vector<map<int, int>> &rows, vector<map<int, int>> &cols, int i1, int i2) {
        if(i1 == i2) {
            return i2;
        }
        if(rows[i1].size() > rows[i2].size()) {
            swap(i1, i2);
        }
        for(auto pr : rows[i1]) {
            rows[i2][pr.first] = pr.second;
            cols[pr.first].erase(cols[pr.first].find(i1));
            cols[pr.first][i2] = pr.second;
        }
        rows[i1].clear();
        return i2;
    }

    vector<map<int, int>> rows, cols;
public:
    explicit Matrix(int n) : rows(n), cols(n) {}

    void set(int i, int j, int val) {
        rows[i][j] = val;
        cols[j][i] = val;
    }

    int get(int i, int j) {
        auto itr = rows[i].find(j);
        if(itr != rows[i].end()) {
            return itr->second;
        }
        return 0;
    }

    int merge_row(int i1, int i2) {
        return merge(rows, cols, i1, i2);
    }

    int merge_col(int j1, int j2) {
        return merge(cols, rows, j1, j2);
    }

    bool get_merge_idx(int i1, int i2, int &j1, int &j2) {
        for(auto itr_i1 = rows[i1].begin(), itr_i2 = rows[i2].begin(); itr_i1 != rows[i1].end() && itr_i2 != rows[i2].end(); ++itr_i1) {
            if(itr_i1->first != itr_i2->first) {
                j1 = itr_i1->first;
                j2 = itr_i2->first;
                return true;
            }
        }
        for(auto itr_i1 = rows[i1].begin(), itr_i2 = rows[i2].begin(); itr_i1 != rows[i1].end() && itr_i2 != rows[i2].end(); ++itr_i2) {
            if(itr_i1->first != itr_i2->first) {
                j1 = itr_i1->first;
                j2 = itr_i2->first;
                return true;
            }
        }
        return false;
    }

    bool is_row_empty(int i) {
        return rows[i].empty();
    }
};

class Solver {
    int n, m[2];
    vector<pair<int, int>> edges[2];

    vector<pair<int, int>> get_ans() {
        DisjointSet dsu[2] = {DisjointSet(n + 1), DisjointSet(n + 1)};
        for(int i = 0; i < 2; i++) {
            for(const auto &edge : edges[i]) {
                dsu[i].merge(edge.first, edge.second);
            }
        }

        Matrix mat(n + 1);
        for(int i = 1; i <= n; i++) {
            mat.set(dsu[0].find(i), dsu[1].find(i), i);
        }

        vector<pair<int, int>> ans;
        queue<int> que;
        for(int i = 1; i <= n; i++) {
            if(mat.is_row_empty(i)) {
                continue;
            }

            int cur_i = i;
            while(!que.empty()) {
                int pre_i = que.front();
                int cur_j, pre_j;
                if(!mat.get_merge_idx(cur_i, pre_i, cur_j, pre_j)) {
                    break;
                }
                que.pop();

                ans.emplace_back(mat.get(cur_i, cur_j), mat.get(pre_i, pre_j));
                cur_i = mat.merge_row(cur_i, pre_i);
                mat.merge_col(cur_j, pre_j);
            }
            que.push(cur_i);
        }

        return ans;
    }
public:
    void read() {
        cin >> n >> m[0] >> m[1];
        for(int i = 0; i < 2; i++) {
            edges[i].resize(m[i]);
            for(int j = 0; j < m[i]; j++) {
                cin >> edges[i][j].first >> edges[i][j].second;
            }
        }
    }
    void solve() {
        vector<pair<int, int>> ans = get_ans();
        cout << ans.size() << endl;
        for(const auto &pr : ans) {
            cout << pr.first << ' ' << pr.second << endl;
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