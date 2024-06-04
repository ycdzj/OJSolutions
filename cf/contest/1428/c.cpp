// ----------------------Template Start----------------------
#include <cstdio>
#include <cstring>
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

const int MAXN = 2e5 + 5;
char str[MAXN];

void init() {
    ios::sync_with_stdio(false);
    MOD = 1e9 + 7;
}

void solve() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        int len = strlen(str);

        int cnt_a = 0, cnt_b = 0;
        int ans = len;
        for(int i = 0; i < len; i++) {
            if(str[i] == 'A') {
                cnt_a++;
            } else {
                if(cnt_a > 0) {
                    cnt_a--;
                    ans -= 2;
                } else if(cnt_b > 0) {
                    ans -= 2;
                    cnt_b--;
                } else {
                    cnt_b = 1;
                }
            }
        }
        printf("%d\n", ans);
    }
}