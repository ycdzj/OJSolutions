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
const long long STEP2 = 41;
const long long MOD = (long long)1e9 + 7;
const int MAXN = 2e5 + 5;

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
long long p2[MAXN];

class Solver {
    int n;
    string s;
    vector<long long> h;
    vector<long long> h2;

    void build_h() {
        h.resize(n + 1);
        h2.resize(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            h[i] = mulmod(h[i + 1], STEP);
            h[i] = addmod(h[i], s[i] - 'a');
            h2[i] = mulmod(h2[i + 1], STEP2);
            h2[i] = addmod(h2[i], s[i] - 'a');
        }
    }
    long long get_h(int l, int r) {
        // [l, r)
        return submod(h[l], mulmod(p[r - l], h[r]));
    }
    long long get_h2(int l, int r) {
        // [l, r)
        return submod(h2[l], mulmod(p2[r - l], h2[r]));
    }

   public:
    void read() {
        cin >> s;
    }

    void solve() {
        n = s.length();
        build_h();

        vector<int> nxt(n);
        for (int val = n, i = n - 1; i >= 0; i--) {
            if (s[i] != 'a') {
                val = i;
            }
            nxt[i] = val;
        }

        if (s[0] == 'a' && nxt[0] == n) {
            cout << n - 1 << endl;
            return;
        }

        int l = nxt[0];
        long long ans = 0;
        for (int r = l + 1; r <= n; r++) {
            int substr_len = r - l;
            long long substr_h = get_h(l, r);
            long long substr_h2 = get_h2(l, r);

            int idx = l;
            int min_dis = l;
            while (idx < n) {
                if (idx + substr_len > n) {
                    break;
                }
                long long cur_h = get_h(idx, idx + substr_len);
                long long cur_h2 = get_h2(idx, idx + substr_len);
                if (cur_h != substr_h || cur_h2 != substr_h2) {
                    break;
                }
                idx += substr_len;
                if (idx >= n) {
                    break;
                }
                if (nxt[idx] < n) {
                    min_dis = min(min_dis, nxt[idx] - idx);
                }
                idx = nxt[idx];
            }

            if (idx >= n) {
                // cout << r << ' ' << min_dis << endl;
                ans += min_dis + 1;
            }
        }

        cout << ans << endl;
    }
};

int main() {
    p[0] = 1;
    p2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p[i] = mulmod(p[i - 1], STEP);
        p2[i] = mulmod(p2[i - 1], STEP2);
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
