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

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

class Solver {
    int n;
    vector<int> k;

   public:
    void read() {
        cin >> n;
        k.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> k[i];
        }
    }

    void solve() {
        int l = 1;
        for (int val : k) {
            l = lcm(l, val);
        }

        long long sum = 0;
        for (int val : k) {
            sum += l / val;
        }

        if (sum >= l) {
            cout << -1 << endl;
            return;
        }

        for (int val : k) {
            cout << l / val << ' ';
        }
        cout << endl;
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
