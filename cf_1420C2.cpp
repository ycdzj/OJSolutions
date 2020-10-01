#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

void make_change(vector<int> &a, int idx, int val, long long &ans) {
    int n = a.size() - 2;
    for (int i = idx - 1; i <= idx + 1; i++) {
        if (1 <= i && i <= n) {
            if (a[i - 1] <= a[i] && a[i] >= a[i + 1]) {
                ans -= a[i];
            } else if (a[i - 1] >= a[i] && a[i] <= a[i + 1]) {
                ans += a[i];
            }
        }
    }
    a[idx] = val;
    for (int i = idx - 1; i <= idx + 1; i++) {
        if (1 <= i && i <= n) {
            if (a[i - 1] <= a[i] && a[i] >= a[i + 1]) {
                ans += a[i];
            } else if (a[i - 1] >= a[i] && a[i] <= a[i + 1]) {
                ans -= a[i];
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, q;
        scanf("%d%d", &n, &q);
        vector<int> a(n + 2);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i - 1] <= a[i] && a[i] >= a[i + 1]) {
                ans += a[i];
            } else if (a[i - 1] >= a[i] && a[i] <= a[i + 1]) {
                ans -= a[i];
            }
        }
        printf("%lld\n", ans);
        while (q--) {
            int l, r;
            scanf("%d%d", &l, &r);
            int l_val = a[l], r_val = a[r];
            make_change(a, l, r_val, ans);
            make_change(a, r, l_val, ans);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
