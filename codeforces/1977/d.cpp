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

const long long STEP = 37;
const long long MOD = (long long)1e15 + 7;
const int MAXN = 3e5 + 5;

long long addmod(long long a, long long b) {
    return (a + b) % MOD;
}

long long mulmod(long long a, long long b) {
    return (a * b) % MOD;
}

long long submod(long long a, long long b) {
    return addmod(a, MOD - b);
}

long long p[MAXN];

class Solver {
    int n, m;
    vector<string> board;

   public:
    void read() {
        cin >> n >> m;
        board.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }
    }

    void solve() {
        int ans_val = 0;
        int ans_i = 0;
        int ans_j = 0;
        map<long long, int> cnt;
        for (int j = 0; j < m; j++) {
            long long h = 0;
            for (int i = 0; i < n; i++) {
                h = addmod(h, mulmod(p[i], board[i][j] - '0'));
            }
            for (int i = 0; i < n; i++) {
                int b = board[i][j] - '0';
                long long cur_h = submod(h, mulmod(p[i], b));
                cur_h = addmod(cur_h, mulmod(p[i], b ^ 1));
                int cur_cnt = ++cnt[cur_h];
                if (cur_cnt > ans_val) {
                    ans_val = cur_cnt;
                    ans_i = i;
                    ans_j = j;
                }
            }
        }
        cout << ans_val << endl;
        for (int i = 0; i < n; i++) {
            int b = board[i][ans_j] - '0';
            if (i == ans_i) {
                b ^= 1;
            }
            cout << b;
        }
        cout << endl;
    }
};

int main() {
    p[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p[i] = mulmod(p[i - 1], STEP);
    }

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
