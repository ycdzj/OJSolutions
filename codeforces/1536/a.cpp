#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

class Solver {
    int n;
    vector<int> a;

    bool check() {
        unordered_map<int, bool> vis;
        for(int i = 0; i < n; i++) {
            vis[a[i]] = true;
        }

        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < i; j++) {
                int c = abs(a[i] - a[j]);
                if(!vis[c]) {
                    vis[c] = true;
                    a.push_back(c);
                    if(a.size() > 300) {
                        return false;
                    }
                }
            }
        }

        return true;
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
        if(check()) {
            cout << "YES" << endl;
            cout << a.size() << endl;
            for(int i = 0; i < a.size(); i++) {
                cout << a[i] << ' ';
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
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