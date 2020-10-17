// ----------------------Template Start----------------------
#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
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

const int MAXN = 3e5 + 5;
int n;
char str[MAXN];

void init() {
    ios::sync_with_stdio(false);
    MOD = 1e9 + 7;
}

void solve() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%s", &n, str);

        map<char, bool> vis;
        for(int i = 0; i < n; i++) {
            vis[str[i]] = true;
        }

        vector<int> ans(n);
        if(vis['<'] && vis['>']) {
            for(int i = 0; i < n; i++) {
                if(str[i] == '-') {
                    ans[i] = 1;
                    ans[(i + 1) % n] = 1;
                }
            }
        } else {
            fill(ans.begin(), ans.end(), 1);
        }
        int sum = accumulate(ans.begin(), ans.end(), 0);
        printf("%d\n", sum);
    }
}