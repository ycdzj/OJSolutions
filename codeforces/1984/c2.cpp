#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MOD = 998244353;

class Mod {
   public:
    int mod;

    explicit Mod(int mod_) : mod(mod_) {
    }

    int add(int a, int b) const {
        return (a + b) % mod;
    }
    int sub(int a, int b) const {
        return (a + mod - b) % mod;
    }
    int mul(long long a, int b) const {
        return (a * b) % mod;
    }
    int pow(long long a, int x) const {
        int ans = 1;
        while (x) {
            if (x & 1) {
                ans = (ans * a) % mod;
            }
            x >>= 1;
            a = (a * a) % mod;
        }
        return ans;
    }
    int inv(int x) const {
        return pow(x, mod - 2);
    }
};

Mod mod(MOD);

class Solver {
    int n;
    vector<int> a;

   public:
    void read() {
        cin >> n;
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        vector<long long> f_min(n + 1);
        vector<long long> f_max(n + 1);
        vector<int> g_min(n + 1);
        vector<int> g_max(n + 1);
        g_min[0] = 1;
        for (int i = 1; i <= n; i++) {
            vector<pair<long long, int>> choices;
            choices.emplace_back(f_min[i - 1] + a[i], g_min[i - 1]);
            choices.emplace_back(abs(f_min[i - 1] + a[i]), g_min[i - 1]);
            choices.emplace_back(f_max[i - 1] + a[i], g_max[i - 1]);
            choices.emplace_back(abs(f_max[i - 1] + a[i]), g_max[i - 1]);
            sort(choices.begin(), choices.end());

            f_min[i] = choices.begin()->first;
            f_max[i] = choices.rbegin()->first;
            for (auto [val, cnt] : choices) {
                if (val == choices.rbegin()->first) {
                    g_max[i] = mod.add(g_max[i], cnt);
                } else if (val == choices.begin()->first) {
                    g_min[i] = mod.add(g_min[i], cnt);
                }
            }
        }
        cout << g_max[n] << endl;
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
