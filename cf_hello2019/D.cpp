#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;
const int MAXN = 5e7;
bool pri[MAXN];
void prime(bool a[], int n) {
    for(int i = 2; i * i <= n; i++) if(!a[i]) {
            for(int j = i * i; j <= n; j += i) a[j] = true;
        }
}

const int MOD = 1e9 + 7;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(ll a, int b) { return (a * b) % MOD; }
inline int powmod(int a, int x) {
    ll cur = a, res = 1;
    while(x) {
        if(x & 1) res = (res * cur) % MOD;
        x >>= 1;
        cur = (cur * cur) % MOD;
    }
    return res;
}

vector<pair<ll, int>> v;
ll n, k;
int f[65][65][2];
int inv[65];
int main() {
    cin >> n >> k;
    int m = sqrt(n) + 10;
    prime(pri, m);
    int max_cnt = 0;
    for(int i = 2; i <= m; i++) if(!pri[i] && n % i == 0) {
            int cnt = 0;
            while(n % i == 0) {
                n /= i;
                cnt++;
            }
            v.emplace_back((ll)i, cnt);
            max_cnt = max(max_cnt, cnt);
        }
    if(n > 1) {
        v.emplace_back(n, 1);
        max_cnt = max(max_cnt, 1);
    }
    for(int i = 0; i <= max_cnt + 1; i++) inv[i] = powmod(i, MOD - 2);

    int cur = 0, pre = 1;
    for(int i = 0; i <= max_cnt; i++) f[i][i][cur] = 1;
    for(int kk = 1; kk <= k; kk++) {
        cur ^= 1; pre ^= 1;
        for(int i = 0; i <= max_cnt; i++) for(int j = 0; j <= max_cnt; j++) {
            if(i == 0) f[i][j][cur] = f[i][j][pre];
            else {
                f[i][j][cur] = addmod(f[i - 1][j][cur], f[i][j][pre]);
            }
        }
        for(int i = 1; i <= max_cnt; i++) for(int j = 0; j <= max_cnt; j++) {
            f[i][j][cur] = mulmod(f[i][j][cur], inv[i + 1]);
        }
    }
    int ans = 1;
    for(int i = 0; i < v.size(); i++) {
        int pp = 1;
        int cursum = 0;
        for(int j = 0; j <= v[i].second; j++) {
            cursum = addmod(cursum, mulmod(f[v[i].second][j][cur], pp));
            pp = mulmod(pp, v[i].first % MOD);
        }
        ans = mulmod(ans, cursum);
    }

    cout << ans << endl;
    return 0;
}
