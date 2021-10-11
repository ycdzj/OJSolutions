#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Mod {
    int m;
public:
    explicit Mod(int m) : m(m) {}
    int add(int a, int b) {
        return (a + b) % m;
    }
    int mul(int a, int b) {
        return static_cast<int>((static_cast<long long>(a) * b) % m);
    }
    int sub(int a, int b) {
        return add(a, m - b);
    }
    int pow(int a, int x) {
        long long cur = a, res = 1;
        while(x) {
            if(x & 1) {
                res = (res * cur) % m;
            }
            x >>= 1;
            cur = (cur * cur) % m;
        }
        return static_cast<int>(res);
    }
    int inv(int a) {
        return pow(a, m - 2);
    }
    int div(int a, int b) {
        return mul(a, inv(b));
    }
};

class Combine {
    Mod mod;
    vector<int> fac, inv_fac;
public:
    explicit Combine(int n, Mod m) : mod(m), fac(n), inv_fac(n) {
        fac[0] = 1;
        for(int i = 1; i < n; i++) {
            fac[i] = mod.mul(fac[i - 1], i);
        }
        inv_fac[n - 1] = mod.inv(fac[n - 1]);
        for(int i = n - 2; i >= 0; i--) {
            inv_fac[i] = mod.mul(inv_fac[i + 1], i + 1);
        }
    }
    int arrange(int n, int m) {
        return mod.mul(fac[n], inv_fac[n - m]);
    }
    int combine(int n, int m) {
        return mod.mul(arrange(n, m), inv_fac[m]);
    }
};

class Pow2 {
    vector<int> p2;
    Mod mod;
public:
    explicit Pow2(Mod m) : mod(m) {
        p2.resize(1);
        p2[0] = 1;
    }
    int get(int x) {
        while(p2.size() <= x) {
            p2.push_back(mod.mul(p2.back(), 2));
        }
        return p2[x];
    }
};

class Solver {
    static Mod mod;
    static Combine com;
    static Pow2 p2;

    int n, k;
public:
    void read() {
        cin >> n >> k;
    }
    void solve() {
        int f_11 = 0, f_10 = 0;
        if(n & 1) {
            f_11 = 1;
        } else {
            f_10 = 1;
        }

        int f_01 = 0, f_00 = 0;
        for(int i = 0; i < n; i++) {
            int f = com.combine(n, i);
            if(i & 1) {
                f_01 = mod.add(f_01, f);
            } else {
                f_00 = mod.add(f_00, f);
            }
        }

        int ans = 0, pre = 1;
        for(int i = 0; i < k; i++) {
            int cur = mod.mul(pre, mod.mul(f_10, mod.pow(p2.get(k - i - 1), n)));
            ans = mod.add(ans, cur);

            pre = mod.mul(pre, mod.add(f_11, f_00));
        }
        ans = mod.add(ans, pre);

        cout << ans << endl;
    }
};

Mod Solver::mod(1e9 + 7);
Combine Solver::com(2e5 + 5, Solver::mod);
Pow2 Solver::p2(Solver::mod);

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