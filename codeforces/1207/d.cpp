#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
inline int addmod(int a, int b) {
    return (a + b) % MOD;
}
inline int mulmod(long long a, int b) {
    return (a * b) % MOD;
}

const int MAXN = 3e5 + 5;
const int INF = 1e9;

struct Item {
    int a, b;
} item[MAXN];

bool cmp_a(const Item &item1, const Item &item2) {
    return item1.a < item2.a;
}
bool cmp_b(const Item &item1, const Item &item2) {
    return item1.b < item2.b;
}

int n;
int fac[MAXN];
int main() {
    fac[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        fac[i] = mulmod(fac[i - 1], i);
    }

    ios::sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> item[i].a >> item[i].b;
    }
    sort(item, item + n, cmp_a);

    int ans = fac[n];
    bool flag = true;
    int cnt_a = 1;
    for(int i = 0, pre = 0, max_b = 0; i < n; i++) {
        if(i == n - 1 || item[i].a != item[i + 1].a) {
            cnt_a = mulmod(cnt_a, fac[i - pre + 1]);

            sort(item + pre, item + i + 1, cmp_b);
            if(max_b > item[pre].b) {
                flag = false;
            }

            max_b = item[i].b;
            pre = i + 1;
        }
    }
    ans = addmod(ans, MOD - cnt_a);
    if(flag) {
        int cnt_ab = 1;
        for(int i = 0, pre = 0; i < n; i++) {
            if(i == n - 1 || item[i].a != item[i + 1].a) {
                for(int j = pre, jpre = pre; j <= i; j++) {
                    if(j == i || item[j].b != item[j + 1].b) {
                        cnt_ab = mulmod(cnt_ab, fac[j - jpre + 1]);
                        jpre = j + 1;
                    }
                }
                pre = i + 1;
            }
        }
        ans = addmod(ans, cnt_ab);
    }

    sort(item, item + n, cmp_b);
    int cnt_b = 1;
    for(int i = 0, pre = 0; i < n; i++) {
        if(i == n - 1 || item[i].b != item[i + 1].b) {
            cnt_b = mulmod(cnt_b, fac[i - pre + 1]);
            pre = i + 1;
        }
    }
    ans = addmod(ans, MOD - cnt_b);
    cout << ans << endl;
    return 0;
}
