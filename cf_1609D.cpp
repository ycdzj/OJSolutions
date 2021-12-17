#include <iostream>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;

class Dsu {
    int n;
    vector<int> f;
    vector<int> sz; // siza!

public:
    explicit Dsu(int n_) : n(n_), f(n_), sz(n_) {
        for (int i = 0; i < f.size(); i++) {
            f[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        if (f[x] != x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }

    int get_size(int x) {
        return sz[find(x)];
    }

    void merge(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            f[x] = y;
            sz[y] += sz[x];
        }
    }
};

class Solver {
    int n, d;

public:
    void read() {
        cin >> n >> d;
    }

    void solve() {
        multiset<int> sz_set;
        for (int i = 1; i <= n; i++) {
            sz_set.insert(1);
        }

        Dsu dsu(n + 1);
        int cnt_redundant = 0;

        for (int i = 0; i < d; i++) {
            int u, v;
            cin >> u >> v;

            if (dsu.find(u) == dsu.find(v)) {
                cnt_redundant++;
            } else {
                sz_set.erase(sz_set.find(dsu.get_size(u)));
                sz_set.erase(sz_set.find(dsu.get_size(v)));
                dsu.merge(u, v);
                sz_set.insert(dsu.get_size(u));
            }

            int ans = 0;
            auto itr = sz_set.rbegin();
            for (int j = 0; itr != sz_set.rend() && j <= cnt_redundant; j++) {
                ans += *itr;
                ++itr;
            }

            cout << ans - 1 << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
