// ----------------------Template Start----------------------
#include <climits>
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

int n;
vector<int> a;
vector<int> pre;
vector<pair<int, int>> ans;
vector<bool> vis;

void solve() {
    scanf("%d", &n);

    a.resize(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    pre.assign(n, -1);
    vector<int> pos_list[4];
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] == 2) {
            if(pos_list[1].empty()) {
                printf("-1\n");
                return;
            } else {
                pre[pos_list[1].back()] = i;
                pos_list[1].pop_back();
            }
        } else if(a[i] == 3) {
            if(!pos_list[3].empty()) {
                pre[pos_list[3].back()] = i;
                pos_list[3].pop_back();
            } else if(!pos_list[2].empty()) {
                pre[pos_list[2].back()] = i;
                pos_list[2].pop_back();
            } else if(!pos_list[1].empty()) {
                pre[pos_list[1].back()] = i;
                pos_list[1].pop_back();
            }  else {
                printf("-1\n");
                return;
            }
        }
        pos_list[a[i]].push_back(i);
    }

    for(int i = 0; i < n; i++) {
        if(a[i] == 0) {
            continue;
        }
        if(pre[i] == -1) {
            ans.emplace_back(i, i);
        } else if(a[pre[i]] == 2) {
            ans.emplace_back(i, pre[i]);
        } else {
            ans.emplace_back(i, i);
            ans.emplace_back(i, pre[i]);
        }
    }

    printf("%d\n", (int)ans.size());
    for(int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].second + 1, ans[i].first + 1);
    }
}