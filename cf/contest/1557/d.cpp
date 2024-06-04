#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <cassert>
using namespace std;

template <typename T>
class SegmentTree {
    vector<T> sum, extra;
    int n;
    function<T(T, T)> op;

    void build_tree(int idx, int l, int r, const vector<T> &values) {
        assert(l <= r);

        if(l == r) {
            while(sum.size() <= idx) {
                sum.emplace_back();
            }
            sum[idx] = values[l];
        } else {
            int mid = l + (r - l) / 2;
            build_tree(idx << 1, l, mid, values);
            build_tree(idx << 1 | 1, mid + 1, r, values);
            sum[idx] = op(sum[idx << 1], sum[idx << 1 | 1]);

            while(extra.size() <= idx) {
                extra.emplace_back();
            }
        }
    }
    void update(int idx, int tree_l, int tree_r, int l, int r, const T &val) {
        assert(tree_l <= tree_r);
        assert(l <= r);

        if(r < tree_l || tree_r < l) {
            return;
        }

        sum[idx] = op(sum[idx], val);
        if(l <= tree_l && tree_r <= r) {
            if(tree_l != tree_r) {
                extra[idx] = op(extra[idx], val);
            }
        } else {
            int mid = tree_l + (tree_r - tree_l) / 2;
            update(idx << 1, tree_l, mid, l, r, val);
            update(idx << 1 | 1, mid + 1, tree_r, l, r, val);
        }
    }
    void query(int idx, int tree_l, int tree_r, int l, int r, T &val) {
        assert(tree_l <= tree_r);
        assert(l <= r);

        if(r < tree_l || tree_r < l) {
            return;
        }

        if(l <= tree_l && tree_r <= r) {
            val = op(val, sum[idx]);
        } else {
            val = op(val, extra[idx]);

            int mid = tree_l + (tree_r - tree_l) / 2;
            query(idx << 1, tree_l, mid, l, r, val);
            query(idx << 1 | 1, mid + 1, tree_r, l, r, val);
        }
    }
public:
    SegmentTree(int n, function<T(T, T)> op, const vector<T> &values) : n(n), op(op) {
        build_tree(1, 0, n - 1, values);
    }

    void update(int l, int r, T val) {
        update(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        T val{};
        query(1, 0, n - 1, l, r, val);
        return val;
    }
};

class Solver {
    int n, m;
    vector<vector<pair<int, int>>> intervals;

    tuple<map<int, int>, int> get_value_map() {
        vector<int> values;
        for(int i = 1; i <= n; i++) {
            for(const auto &pr : intervals[i]) {
                values.push_back(pr.first);
                values.push_back(pr.second);
            }
        }
        sort(values.begin(), values.end());
        auto itr = unique(values.begin(), values.end());
        values.erase(itr, values.end());

        map<int, int> value_map;
        for(int i = 0; i < values.size(); i++) {
            value_map[values[i]] = i;
        }
        return {value_map, values.size()};
    }
public:
    void read() {
        cin >> n >> m;
        intervals.assign(n + 1, {});
        for(int cnt = 0; cnt < m; cnt++) {
            int i, l, r;
            cin >> i >> l >> r;
            intervals[i].emplace_back(l, r);
        }
    }
    void solve() {
        auto [value_map, map_size] = get_value_map();
        SegmentTree<pair<int, int>> tree(
            map_size,
            [](pair<int, int> x, pair<int, int> y){return max(x, y);},
            vector<pair<int, int>>(map_size)
        );

        vector<pair<int, int>> f(n + 1);
        for(int i = 1; i <= n; i++) {
            for(const auto &pr : intervals[i]) {
                int l = value_map[pr.first];
                int r = value_map[pr.second];
                f[i] = max(f[i], tree.query(l, r));
            }
            for(const auto &pr : intervals[i]) {
                int l = value_map[pr.first];
                int r = value_map[pr.second];
                tree.update(l, r, {f[i].first + 1, i});
            }
        }

        int max_idx = 1;
        for(int i = 2; i <= n; i++) {
            if(f[i].first > f[max_idx].first) {
                max_idx = i;
            }
        }

        vector<bool> vis(n + 1);
        for(int i = max_idx; i; i = f[i].second) {
            vis[i] = true;
        }

        cout << n - 1 - f[max_idx].first << endl;
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                cout << i << ' ';
            }
        }
        cout << endl;
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
