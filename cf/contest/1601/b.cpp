#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

struct Zkw {
    vector<pair<int, int>> a;
    int n;

public:
    Zkw(int n) : a(n * 2), n(n) {}

    pair<int, int> query(int l, int r) {
        l += n;
        r += n;
        pair<int, int> res = a[r];
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                res = max(res, a[l++]);
            }
            if(r & 1) {
                res = max(res, a[--r]);
            }
        }
        return res;
    }

    void update(int pos, pair<int, int> val) {
        pos += n;
        a[pos] = val;
        pos >>= 1;

        for(; pos > 0; pos >>= 1) {
            a[pos] = max(a[pos << 1], a[pos << 1 | 1]);
        }
    }
};

class Solver {
    int n;
    vector<int> a, b;
public:
    void read() {
        cin >> n;
        a.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        b.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> b[i];
        }
    }

    void solve() {
        Zkw zkw(n + 1);
        for(int i = 0; i <= n; i++) {
            zkw.update(i, {1, i});
        }

        vector<int> dis(n + 1, -1), pre(n + 1), jump(n + 1);
        queue<int> que;

        dis[n] = 0;
        que.push(n);

        while(!que.empty() && dis[0] == -1) {
            int u = que.front();
            que.pop();

            if(a[u] == u) {
                dis[0] = dis[u] + 1;
                pre[0] = u;
                jump[0] = 0;
                break;
            }

            int l = u - a[u];
            int r = u;

            while(zkw.query(l, r).first != 0) {
                int pos = zkw.query(l, r).second;
                zkw.update(pos, {0, 0});

                int v = pos + b[pos];
                if(dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    pre[v] = u;
                    jump[v] = pos;
                    que.push(v);
                }
            }
        }

        cout << dis[0] << endl;
        if(dis[0] != -1) {
            vector<int> path;
            path.push_back(0);
            while(path.back() != n) {
                path.push_back(pre[path.back()]);
            }

            for(int i = path.size() - 1; i > 0; i--) {
                cout << jump[path[i - 1]] << ' ';
            }
            cout << endl;
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