#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
using namespace std;

class Solver {
    int n, k;
    vector<int> a;
public:
    void read() {
        cin >> n >> k;
        a.resize(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
    }
    void solve() {
        vector<int> indices(n);
        for(int i = 0; i < n; i++) {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int x, int y){return a[x] < a[y];});
        int cnt = 1;
        for(int i = 1; i < n; i++) {
            if(indices[i - 1] + 1 != indices[i]) {
                cnt++;
            }
        }
        if(cnt <= k) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
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