#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

int gcd(int a, int b) {
    if(a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

class Solver {
    int n;
    vector<int> a;

    int count(int idx) {
        int cnt = 0;
        for(int val : a) {
            if(val >> idx & 1) {
                cnt++;
            }
        }
        return cnt;
    }

public:
    void read() {
        cin >> n;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }

    void solve() {
        int g = 0;
        for(int i = 0; i < 30; i++) {
            int cnt = count(i);
            g = gcd(g, cnt);
        }

        for(int i = 1; i <= n; i++) {
            if(g % i == 0) {
                cout << i << ' ';
            }
        }
        cout << endl;
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