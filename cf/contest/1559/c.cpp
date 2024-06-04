#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n;
    vector<int> a;

    vector<int> get_ans() {
        if(a[n] == 0) {
            vector<int> ans;
            for(int i = 1; i <= n + 1; i++) {
                ans.push_back(i);
            }
            return ans;
        }

        if(a[1] == 1) {
            vector<int> ans;
            ans.push_back(n + 1);
            for(int i = 1; i <= n; i++) {
                ans.push_back(i);
            }
            return ans;
        }

        int s = -1;
        for(int i = 1; i + 1 <= n; i++) {
            if(a[i] == 0 && a[i + 1] == 1) {
                s = i;
                break;
            }
        }

        if(s != -1) {
            vector<int> ans;
            for(int i = 1; i <= n; i++) {
                ans.push_back(i);
                if(i == s) {
                    ans.push_back(n + 1);
                }
            }
            return ans;
        }

        return {};
    }
public:
    void read() {
        cin >> n;
        a.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
    }
    void solve() {
        vector<int> ans = get_ans();
        if(ans.empty()) {
            cout << -1 << endl;
        } else {
            for(int i = 0; i < ans.size(); i++) {
                cout << ans[i] << ' ';
            }
            cout << endl;
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