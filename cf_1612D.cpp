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

bool f(long long a, long long b, long long x) {
    if (a > b) {
        return f(b, a, x);
    }
    if (b - a < a) {
        return f(b - a, b, x);
    }
    if (x > b) {
        return false;
    }
    if (a == 0) {
        return x == a || x == b;
    }
    if (a <= x && x % a == b % a) {
        return true;
    }
    return f(b % a, a, x);
}

class Solver {
    long long a, b, x;
public:
    void read() {
        cin >> a >> b >> x;
    }

    void solve() {
        if (f(a, b, x)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
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
