#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int MAXN = 3e5 + 5;

inline int mulmod(long long x, int y) { return (x * y) % MOD; }
inline int addmod(int x, int y) { return (x + y) % MOD; }
int powmod(int a, int x) {
    int ans = 1;
    while (x) {
        if (x & 1) {
            ans = mulmod(ans, a);
        }
        a = mulmod(a, a);
        x >>= 1;
    }
    return ans;
}

int fac[MAXN], inv_fac[MAXN];
inline int combine(int n, int m) { return mulmod(fac[n], mulmod(inv_fac[m], inv_fac[n - m])); }

int n, k;
vector<pair<int, int>> lamp;

int main() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }
    inv_fac[MAXN - 1] = powmod(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_fac[i] = mulmod(inv_fac[i + 1], i + 1);
    }

    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        lamp.emplace_back(l, r);
    }
    sort(lamp.begin(), lamp.end());

    multiset<int> cur;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (!cur.empty() && *cur.begin() < lamp[i].first) {
            cur.erase(cur.begin());
        }
        if (cur.size() >= k - 1) {
            ans = addmod(ans, combine(cur.size(), k - 1));
        }
        cur.insert(lamp[i].second);
    }
    printf("%d\n", ans);

    return 0;
}
