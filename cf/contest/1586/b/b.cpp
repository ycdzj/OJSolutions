#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int n, m;
    vector<vector<int>> r;

public:
    void read() {
        cin >> n >> m;
        r.resize(m);
        for(int i = 0; i < m; i++) {
            r[i].resize(3);
            for(int j = 0; j < 3; j++) {
                cin >> r[i][j];
            }
        }
    }

    void solve() {
        vector<bool> vis(n + 1);
        for(int i = 0; i < m; i++) {
            vis[r[i][1]] = true;
        }
        for(int u = 1; u <= n; u++) {
            if(!vis[u]) {
                for(int i = 1; i <= n; i++) {
                    if(i != u) {
                        cout << i << ' ' << u << endl;
                    }
                }
                return;
            }
        }
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