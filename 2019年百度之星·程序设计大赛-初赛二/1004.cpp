#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
inline int powmod(int a, int x) {
    long long cur = a, res = 1;
    while(x) {
        if(x & 1) {
            res = (res * cur) % MOD;
        }
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return res;
}

const int MAXN = 2e5 + 5;

int fac[MAXN], inv_fac[MAXN];
inline int com(int n, int m) {
    return mulmod(fac[n], mulmod(inv_fac[m], inv_fac[n - m]));
}

int main() {
    ios::sync_with_stdio(false);
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for(int i = MAXN - 2; i >= 0; i--) {
        inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);
    }
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> v;
        int preval, precnt = 1;
        cin >> preval;
        for(int i = 1; i < 2 * n; i++) {
            int a;
            cin >> a;
            if(a == preval) {
                precnt++;
            }
            else {
                v.push_back(precnt);
                preval = a;
                precnt = 1;
            }
        }
        v.push_back(precnt);
        int ans[2][3], cur = 0, pre = 1;
        ans[cur][0] = 0;
        ans[cur][1] = 1;
        ans[cur][2] = 0;
        for(int i = 0; i < v.size(); i++) {
            cur ^= 1;
            pre ^= 1;
            ans[cur][0] = 0; ans[cur][1] = 0; ans[cur][2] = 0;
            if(v[i] & 1) {
                ans[cur][1] = addmod(ans[cur][1], mulmod(ans[pre][0], com(v[i], v[i] / 2)));
                ans[cur][1] = addmod(ans[cur][1], mulmod(ans[pre][2], com(v[i], v[i] / 2)));
                ans[cur][0] = addmod(ans[cur][0], mulmod(ans[pre][1], com(v[i], v[i] / 2)));
                ans[cur][2] = addmod(ans[cur][2], mulmod(ans[pre][1], com(v[i], v[i] / 2)));
            }
            else {
                for(int j = 0; j < 3; j++) {
                    ans[cur][j] = addmod(ans[cur][j], mulmod(ans[pre][j], com(v[i], v[i] / 2)));
                }
                ans[cur][0] = addmod(ans[cur][0], mulmod(ans[pre][2], com(v[i], v[i] / 2 - 1)));
                ans[cur][2] = addmod(ans[cur][2], mulmod(ans[pre][0], com(v[i], v[i] / 2 - 1)));
            }
        }
        cout << ans[cur][1] << endl;
    }
    return 0;
}
