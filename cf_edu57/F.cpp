#include <iostream>
using namespace std;

const int MOD = 998244353;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
inline int powmod(int a, int x) {
    long long res = 1, cur = a;
    while(x) {
        if(x & 1) res = (res * cur) % MOD;
        cur = (cur * cur) % MOD;
        x >>= 1;
    }
    return res;
}
inline int divmod(int a, int b) { return mulmod(a, powmod(b, MOD - 2)); }

const int MAXN = 2e5 + 5;
struct ZKW {
    int tree[MAXN * 2];
    int n;
    void update(int p, int val) {
        tree[p += n] += val;
        for(p >>= 1; p > 0; p >>= 1) tree[p] = tree[p << 1] + tree[p << 1 | 1];
    }
    int query(int l, int r) {//[l, r]
        if(l > r) return 0;
        l += n; r += n;
        int res = tree[r];
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = res + tree[l++];
            if(r & 1) res = res + tree[--r];
        }
        return res;
    }
} zkw;
int n, a[MAXN], pos[MAXN];

int main() {
    ios::sync_with_stdio(false);

    cin >> n;
    zkw.n = n + 1;
    int m = 0;

    for(int i = 1; i <= n; i++) pos[i] = -1;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] == -1) m++;
        else pos[a[i]] = i;
    }

    int ans = divmod(mulmod(m, m - 1), 4);
    for(int i = 1; i <= n; i++) {
        if(a[i] == -1) continue;
        ans = addmod(ans, zkw.query(a[i] + 1, n));
        zkw.update(a[i], 1);
    }
    
    for(int i = 0; i < zkw.n * 2; i++) zkw.tree[i] = 0;
    for(int i = 1; i <= n; i++) if(pos[i] == -1) {
        zkw.update(i, 1);
    }
    int sum = 0;
    for(int i = 1, cnt = 0; i <= n; i++) {
        if(a[i] != -1) {
            int num = zkw.query(a[i] + 1, n);
            sum = addmod(sum, mulmod(num, cnt));
        }
        else {
            cnt++;
        }
    }
    for(int i = n, cnt = 0; i >= 1; i--) {
        if(a[i] != -1) {
            int num = zkw.query(1, a[i] - 1);
            sum = addmod(sum, mulmod(num, cnt));
        }
        else {
            cnt++;
        }
    }
    ans = addmod(ans, divmod(sum, m));
    cout << ans << endl;
    return 0;
}
