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

class Sieve {
    vector<bool> vis;
public:
    explicit Sieve(int n) : vis(n) {
        for(int i = 2; i < n; i++) {
            if(!vis[i]) {
                for(int j = 2 * i; j < n; j += i) {
                    vis[j] = true;
                }
            }
        }
    }

    bool is_prime(int x) {
        return x >= 2 && !vis[x];
    }
};

Sieve sieve(1e6 + 5);

class Solver {
    int n, e;
    vector<int> a;

public:
    void read() {
        cin >> n >> e;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        long long ans = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(sieve.is_prime(a[i])) {
                int l = i - e;
                while(l >= 0 && a[l] == 1) {
                    l -= e;
                }

                int r = i + e;
                while(r < n && a[r] == 1) {
                    r += e;
                }

                long long lcnt = (i - l) / e - 1;
                long long rcnt = (r - i) / e - 1;
                ans += (lcnt + 1) * (rcnt + 1) - 1;
            }
        }
        cout << ans << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
