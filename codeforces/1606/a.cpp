#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solver {
    string s;

public:
    void read() {
        cin >> s;
    }

    void solve() {
        int cnt_ab = 0, cnt_ba = 0;
        for(int i = 0; i + 1 < s.length(); i++) {
            if(s[i] == 'a' && s[i + 1] == 'b') {
                cnt_ab++;
            }
            if(s[i] == 'b' && s[i + 1] == 'a') {
                cnt_ba++;
            }
        }

        if(cnt_ab != cnt_ba) {
            if(s[0] == 'a') {
                s[0] = 'b';
            } else {
                s[0] = 'a';
            }
        }

        cout << s << endl;
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
