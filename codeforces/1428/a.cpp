// ----------------------Template Start----------------------
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

int MOD;
inline int addmod(int a, int b) { return (a + b) % MOD; }
inline int mulmod(long long a, int b) { return (a * b) % MOD; }
inline int powmod(long long a, int x) {
    int ans = 1;
    while(x) {
        if(x & 1) {
            ans = (ans * a) % MOD;
        }
        x >>= 1;
        a = (a * a) % MOD;
    }
    return ans;
}

void init();
void solve();

int main() {
    init();
    solve();
    return 0;
}
// ----------------------Template End----------------------

void init() {
    ios::sync_with_stdio(false);
    MOD = 1e9 + 7;
}
int abs(int x) {
    if(x < 0) {
        x = -x;
    }
    return x;
}

void solve() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int ans = abs(x1 - x2) + abs(y1 - y2) + 2;
        if(x1 == x2) {
            ans -= 2;
        } else if(y1 == y2) {
            ans -= 2;
        }
        printf("%d\n", ans);
    }
}