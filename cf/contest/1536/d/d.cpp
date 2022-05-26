#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

const int INF = 1e9 + 5;

class Solver {
    int n;
    vector<int> b;

    bool get_ans() {
        set<int> s;
        s.insert(INF);
        s.insert(-INF);
        s.insert(b[0]);

        for(int i = 1; i < n; i++) {
            if(b[i] > b[i - 1]) {
                auto itr = s.upper_bound(b[i - 1]);
                if(b[i] > *itr) {
                    return false;
                }
            } else if(b[i] < b[i - 1]) {
                auto itr = --s.lower_bound(b[i - 1]);
                if(b[i] < *itr) {
                    return false;
                }
            }
            s.insert(b[i]);
        }

        return true;
    }

public:
    void read() {
        cin >> n;
        b.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> b[i];
        }
    }

    void solve() {
        if(get_ans()) {
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
    while(t--) {
        Solver solver;
        solver.read();
        solver.solve();
    }
    return 0;
}