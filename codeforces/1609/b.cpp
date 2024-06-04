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
    int n, q;
    string str;

    int cnt;

    void replace(int p, char c) {
        for(int i = p - 2; i <= p && i + 2 < n; i++) {
            if(str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'c') {
                cnt--;
            }
        }
        str[p] = c;
        for(int i = p - 2; i <= p && i + 2 < n; i++) {
            if(str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'c') {
                cnt++;
            }
        }
    }
public:
    void read() {
        cin >> n >> q >> str;

        cnt = 0;
        for(int i = 0; i + 2 < n; i++) {
            if(str[i] == 'a' && str[i + 1] == 'b' && str[i + 2] == 'c') {
                cnt++;
            }
        }
    }

    void solve() {
        while(q--) {
            int p;
            string c;
            cin >> p >> c;
            replace(p - 1, c[0]);
            cout << cnt << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}
