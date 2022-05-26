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
    vector<int> a, b;

    bool get_ans() {
        map<int, int> sa, sb;
        for(int val : a) {
            sa[val]++;
        }
        for(int val : b) {
            sb[val]++;
        }

        auto itr_sa = sa.begin();
        auto itr_sb = sb.begin();
        while(itr_sa != sa.end() && itr_sb != sb.end()) {
            if(itr_sa->first == itr_sb->first) {
                int d = min(itr_sa->second, itr_sb->second);
                itr_sa->second -= d;
                itr_sb->second -= d;
            } else if(itr_sa->first == itr_sb->first - 1) {
                int d = min(itr_sa->second, itr_sb->second);
                itr_sa->second -= d;
                itr_sb->second -= d;
                if(itr_sa->second != 0) {
                    return false;
                }
            } else {
                return false;
            }
            if(itr_sa->second == 0) {
                ++itr_sa;
            }
            if(itr_sb->second == 0) {
                ++itr_sb;
            }
        }

        return itr_sa == sa.end() && itr_sb == sb.end();
    }

public:
    void read() {
        cin >> n;
        a.resize(n);
        b.resize(n);

        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
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