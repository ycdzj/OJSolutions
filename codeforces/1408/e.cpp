#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> f;

public:
    explicit DisjointSet(int n) {
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i] = i;
        }
    }

    int find(int x) {
        if (f[x] != x) {
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

class Solver {
private:
    int m, n;
    vector<int> a, b;
    vector<pair<int, int>> edge_list;

public:
    void read() {
        scanf("%d%d", &m, &n);

        a.resize(m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &a[i]);
        }

        b.resize(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }

        for (int i = 0; i < m; i++) {
            int s;
            scanf("%d", &s);
            for (int j = 0; j < s; j++) {
                int v;
                scanf("%d", &v);
                edge_list.emplace_back(i, v - 1);
            }
        }
    }
    void solve() {
        sort(edge_list.begin(), edge_list.end(), [this](const pair<int, int> &x, const pair<int, int> &y) {
            return this->a[x.first] + this->b[x.second] > this->a[y.first] + this->b[y.second];
        });

        long long ans = 0;
        DisjointSet dsu(m + n);
        for (auto edge : edge_list) {
            int x = dsu.find(edge.first);
            int y = dsu.find(m + edge.second);
            if (x == y) {
                ans += a[edge.first] + b[edge.second];
            } else {
                dsu.merge(x, y);
            }
        }

        printf("%lld\n", ans);
    }
};

int main() {
    Solver solver;
    solver.read();
    solver.solve();
    return 0;
}