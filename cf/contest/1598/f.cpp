#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

class Solver {
    struct RowExtraData {
        vector<int> f;
        int delta, min_delta;
        unordered_map<int, int> cnt_map, first_idx_map;

        RowExtraData() {}
        explicit RowExtraData(const string &str) : f(str.size() + 1), delta(0), min_delta(0) {
            stack<int> stk;
            vector<int> next(str.size(), -1);
            for(int i = 0; i < str.size(); i++) {
                if(str[i] == '(') {
                    delta++;
                    stk.push(i);
                } else {
                    delta--;
                    if(!stk.empty()) {
                        next[i] = stk.top();
                        next[stk.top()] = i;
                        stk.pop();
                    }
                }
                if(auto itr = first_idx_map.find(delta); itr == first_idx_map.end()) {
                    first_idx_map[delta] = i;
                }
                cnt_map[delta]++;
                min_delta = min(min_delta, delta);
            }
            for(int i = (int)str.size() - 1; i >= 0; i--) {
                if(str[i] == '(' && next[i] != -1) {
                    f[i] = 1 + f[next[i] + 1];
                }
            }
        }
    };

    int n;
    vector<string> rows;
    vector<RowExtraData> extra_datas;

    int get_delta(int mask) {
        int delta = 0;
        for(int i = 0; i < n; i++) {
            if(mask >> i & 1) {
                delta += extra_datas[i].delta;
            }
        }
        return delta;
    }

    vector<int> get_g() {
        int m = 1 << n;
        vector<int> g(m, -1e9);
        g[0] = 0;
        for(int mask = 1; mask < m; mask++) {
            int delta = get_delta(mask);
            for(int i = 0; i < n; i++) {
                if(mask >> i & 1) {
                    int cur_delta = delta - extra_datas[i].delta;
                    if(cur_delta + extra_datas[i].min_delta >= 0) {
                        int cur_g = g[mask ^ (1 << i)] + extra_datas[i].cnt_map[-cur_delta];
                        g[mask] = max(g[mask], cur_g);
                    }
                }
            }
        }
        return g;
    }

    int get_f(int i, int delta) {
        int first_idx;
        if(auto itr = extra_datas[i].first_idx_map.find(-delta); itr != extra_datas[i].first_idx_map.end()) {
            first_idx = itr->second;
        } else {
            return 0;
        }

        if(auto itr = extra_datas[i].first_idx_map.find(-delta - 1); itr != extra_datas[i].first_idx_map.end()) {
            if(itr->second < first_idx) {
                return 0;
            }
        }
        return 1 + extra_datas[i].f[first_idx + 1];
    }

public:
    void read() {
        cin >> n;
        rows.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> rows[i];
        }
    }

    void solve() {
        extra_datas.resize(n);
        for(int i = 0; i < n; i++) {
            extra_datas[i] = RowExtraData(rows[i]);
        }

        vector<int> g = get_g();

        int ans = 0;
        for(int mask = 0; mask < (1 << n); mask++) {
            int delta = get_delta(mask);
            for(int i = 0; i < n; i++) {
                if(!(mask >> i & 1)) {
                    int cur_ans = g[mask] + get_f(i, delta);
                    ans = max(ans, cur_ans);
                }
            }
        }

        cout << ans << endl;
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
