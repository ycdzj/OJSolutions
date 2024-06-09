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

const int STEP = 2;
const int MOD = 1e9 + 7;

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
    int n, k;
    string s;

    int alpha;
    int factors[2];
    void build_alpha() {
        for (int i = 0; i < 2; i++) {
            factors[i] = 0;
        }
        alpha = mod.pow(2, k);
        int b = n / k;
        for (int i = 0, cur = 1; i < b; i++) {
            factors[i % 2] = mod.add(factors[i % 2], cur);
            cur = mod.mul(cur, alpha);
        }
    }
    int calc(int x) {
        int y = mod.sub(mod.sub(alpha, x), 1);

        int res_x = mod.mul(x, factors[0]);
        int res_y = mod.mul(y, factors[1]);
        return mod.add(res_x, res_y);
    }

    vector<int> prefix_hash;
    vector<int> suffix_hash;
    void build_hash() {
        prefix_hash.resize(n);
        suffix_hash.resize(n + 1);
        for (int i = 0, pre = 0; i < n; i++) {
            int cur = mod.mul(pre, STEP);
            cur = mod.add(cur, s[i] - '0');
            prefix_hash[i] = cur;
            pre = cur;
        }
        for (int i = n - 1, pre = 0; i >= 0; i--) {
            int cur = mod.mul(pre, STEP);
            cur = mod.add(cur, s[i] - '0');
            suffix_hash[i] = cur;
            pre = cur;
        }
    }
    int get_k_hash(int i) {
        int h = suffix_hash[i];
        if (i + k == n) {
            return h;
        }
        if (i + k < n) {
            h = mod.sub(h, mod.mul(alpha, suffix_hash[i + k]));
            return h;
        }

        int pre_h = prefix_hash[i - 1];
        if (n - k - 1 >= 0) {
            pre_h = mod.sub(pre_h, mod.mul(prefix_hash[n - k - 1],
                                           mod.pow(STEP, i - n + k)));
        }
        return mod.add(h, mod.mul(mod.pow(STEP, n - i), pre_h));
    }

   public:
    void read() {
        cin >> n >> k >> s;
    }

    void solve() {
        build_alpha();
        build_hash();
        for (int i = 1; i <= n; i++) {
            int new_hash = suffix_hash[i];
            new_hash = mod.add(
                new_hash, mod.mul(prefix_hash[i - 1], mod.pow(STEP, n - i)));
            int k_hash = get_k_hash(i);
            if (!(k_hash == 0 || k_hash == mod.sub(alpha, 1))) {
                continue;
            }
            if (calc(k_hash) != new_hash) {
                continue;
            }
            cout << i << endl;
            return;
        }
        cout << -1 << endl;
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
