#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

const int MAXN = 2e5 + 5;
const int MOD = 1e9 + 7;

int addmod(int a, int b) {
    return (a + b) % MOD;
}

int mulmod(long long a, int b) {
    return (a * b) % MOD;
}

struct P2 {
    int val[MAXN];
    P2() {
        val[0] = 1;
        for(int i = 1; i < MAXN; i++) {
            val[i] = mulmod(val[i - 1], 2);
        }
    }
} p2;

class Solver {
    int n, m;
    vector<int> l, r, x;

public:
    void read() {
        cin >> n >> m;
        l.resize(m);
        r.resize(m);
        x.resize(m);
        for(int i = 0; i < m; i++) {
            cin >> l[i] >> r[i] >> x[i];
        }
    }

    void solve() {
        vector<vector<int>> insert(n + 2), remove(n + 2);
        for(int i = 0; i < m; i++) {
            insert[l[i]].push_back(x[i]);
            remove[r[i] + 1].push_back(x[i]);
        }

        vector<int> cnt(30);
        int total = 0;

        vector<bool> vis(30);

        for(int i = 1; i <= n; i++) {
            for(int val : insert[i]) {
                total++;
                for(int j = 0; j < 30; j++) {
                    if(val >> j & 1) {
                        cnt[j]++;
                    }
                }
            }
            for(int val : remove[i]) {
                total--;
                for(int j = 0; j < 30; j++) {
                    if(val >> j & 1) {
                        cnt[j]--;
                    }
                }
            }
            for(int j = 0; j < 30; j++) {
                if(cnt[j] == total) {
                    vis[j] = true;
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < 30; i++) {
            if(vis[i]) {
                ans = addmod(ans, p2.val[i]);
            }
        }
        ans = mulmod(ans, p2.val[n - 1]);

        cout << ans << endl;
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
