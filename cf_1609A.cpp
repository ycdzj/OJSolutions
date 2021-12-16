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
        while (x) {
            if (x & 1) {
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
    int n;
    vector<long long> a;
public:
    void read() {
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        long long sum_val = 0, max_val = 0;
        int cnt = 0;
        for(long long val : a) {
            while(val && val % 2 == 0) {
                val /= 2;
                cnt++;
            }
            sum_val += val;
            max_val = max(max_val, val);
        }
        cout << sum_val - max_val + (max_val << cnt) << endl;
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
