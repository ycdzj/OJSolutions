#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

int query(const vector<int> &a) {
    cout << '?';
    for(int val : a) {
        cout << ' ' << val + 1;
    }
    cout << endl;

    cout.flush();

    int ans;
    cin >> ans;
    return ans;
}

class Solver {
    int n;
    vector<int> p;

    int get_last() {
        vector<int> q(n);
        for(int d = n - 1; d >= 1; d--) {
            q[n - 1] = d;
            if(query(q) != 0) {
                return n - d;
            }
        }
        return n;
    }

public:
    void read() {
        cin >> n;
    }

    void solve() {
        p.resize(n);
        p[n - 1] = get_last();

        for(int i = 1; i < p[n - 1]; i++) {
            vector<int> q(n, p[n - 1] - i);
            q[n - 1] = 0;

            int pos = query(q);
            p[pos - 1] = i;
        }

        for(int i = p[n - 1] + 1; i <= n; i++) {
            vector<int> q(n);
            q[n - 1] = i - p[n - 1];

            int pos = query(q);
            p[pos - 1] = i;
        }

        cout << '!';
        for(int val : p) {
            cout << ' ' << val;
        }
        cout << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}