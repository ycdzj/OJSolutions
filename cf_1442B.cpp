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

class Solver {
    static Mod mod;

    int n, k;
    vector<int> a, b;

    int get_ans() {
        vector<int> ra(n + 1);
        for(int i = 1; i <= n; i++) {
            ra[a[i]] = i;
        }

        vector<int> c(n + 1);
        for(int i = 1; i <= k; i++) {
            c[ra[b[i]]] = i;
        }

        int ans = 1;
        for(int i = 1; i <= n; i++) {
            if(!c[i]) {
                continue;
            }

            int cnt = 0;
            if(i - 1 >= 1 && c[i - 1] < c[i]) {
                cnt++;
            }
            if(i + 1 <= n && c[i + 1] < c[i]) {
                cnt++;
            }
            ans = mod.mul(ans, cnt);
        }

        return ans;
    }
public:
    void read() {
        cin >> n >> k;
        a.resize(n + 1);
        b.resize(k + 1);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for(int i = 1; i <= k; i++) {
            cin >> b[i];
        }
    }
    void solve() {
        cout << get_ans() << endl;
    }
};

Mod Solver::mod(998244353);

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