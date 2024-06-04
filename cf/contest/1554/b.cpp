#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    static int greatest_bit(int x) {
        for(int i = 30; i >= 0; i--) {
            if(x >> i & 1) {
                return (1 << i);
            }
        }
        return 0;
    }

    int n, k;
    vector<int> a;

    long long eval(int i, int j) {
        return (long long)(i + 1) * (j + 1) - (long long)k * (a[i] | a[j]);
    }
public:
    void read() {
        cin >> n >> k;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    void solve() {
        int g = greatest_bit(n);
        if(!g) {
            exit(-1);
        }
        g = (g | (g - 1));
        
        long long ans = -1e18;
        for(int j = 1; j < n; j++) {
            int l_idx = static_cast<int>(max(0ll, j - 1 - (long long)(k * g) / j));
            for(int i = l_idx; i < j; i++) {
                ans = max(ans, eval(i, j));
            }
        }

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