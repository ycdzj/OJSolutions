// ----------------------Template Start----------------------
#include <atomic>
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

const int MAXN = 1e5 + 5;
int n, k;
int a[MAXN];

struct Item {
    int val;
    int cnt;
    long long get_score() const {
        long long cur_ans = get_ans();
        Item tmp;
        tmp.val = val;
        tmp.cnt = cnt + 1;
        return cur_ans - tmp.get_ans();
    }
    long long get_ans() const {
        long long x = val / cnt;
        long long ans = (cnt - (val % cnt)) * x * x;
        ans += (val % cnt) * (x + 1) * (x + 1);
        return ans;
    }
    bool operator < (const Item &item) const {
        return get_score() < item.get_score();
    }
};

void init() {
    ios::sync_with_stdio(false);
    MOD = 1e9 + 7;
}

void solve() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    priority_queue<Item> que;
    for(int i = 0; i < n; i++) {
        Item item;
        item.val = a[i];
        item.cnt = 1;
        que.push(item);
    }
    for(int i = 0; i < k - n; i++) {
        Item item = que.top();
        que.pop();
        item.cnt++;
        que.push(item);
    }
    long long ans = 0;
    while(!que.empty()) {
        Item item = que.top();
        que.pop();
        ans += item.get_ans();
    }
    printf("%lld\n", ans);
}