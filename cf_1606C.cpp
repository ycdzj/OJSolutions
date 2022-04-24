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
#include <array>

using namespace std;

class Pow10 {
    array<int, 10> p;
public:
    Pow10() : p() {
        p[0] = 1;
        for (int i = 1; i < 10; i++) {
            p[i] = p[i - 1] * 10;
        }
    }

    int get(int i) {
        return p[i];
    }
};

Pow10 p10;

class Solver {
    int n, k;
    array<bool, 10> vis;

public:
    void read() {
        cin >> n >> k;

        fill(vis.begin(), vis.end(), false);
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            vis[val] = true;
        }
    }

    void solve() {
        array<int, 10> pre = {};
        pre[9] = -1;
        for (int i = 8; i >= 0; i--) {
            if (vis[i + 1]) {
                pre[i] = i + 1;
            } else {
                pre[i] = pre[i + 1];
            }
        }

        int last_idx = -1, last_take = -1;
        for (int rem_k = k + 1, i = 0; i < 10; i++) {
            if (vis[i]) {
                int take = rem_k;
                if (pre[i] != -1) {
                    int cnt_digit = pre[i] - i;
                    take = min(take, p10.get(cnt_digit) - 1);
                }

                rem_k -= take;

                if (rem_k == 0) {
                    last_idx = i;
                    last_take = take;
                    break;
                }
            }
        }

        assert(last_idx != -1);
        assert(last_take != -1);

        cout << last_take;
        for (int i = last_idx - 1; i >= 0; i--) {
            if (vis[i]) {
                int cnt_digit = pre[i] - i;
                cout << p10.get(cnt_digit) - 1;
            }
        }
        for(int i = 0; i < 10; i++) {
            if(vis[i]) {
                break;
            }
            cout << '0';
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
