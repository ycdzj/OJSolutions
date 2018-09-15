#include <cstdio>
const int MAXN = 5e5 + 5;
int n, a[MAXN];
int main() {
    scanf("%d", &n);
    bool neg = false, pos = false;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(a[i] < 0) neg = true;
        else if(a[i] > 0) pos = true;
        else neg = pos = true;
    }
    long long ans = 0;
    if(n == 1) ans = a[0];
    else {
        if(neg && pos) {
            for(int i = 0; i < n; i++) {
                if(a[i] > 0) ans += a[i];
                else ans -= a[i];
            }
        }
        else if(neg) {
            int max_ = -1e9;
            for(int i = 0; i < n; i++) {
                if(a[i] > max_) max_ = a[i];
                ans -= a[i];
            }
            ans += max_;
            ans += max_;
        }
        else {
            int min_ = 1e9;
            for(int i = 0; i < n; i++) {
                if(a[i] < min_) min_ = a[i];
                ans += a[i];
            }
            ans -= min_;
            ans -= min_;
        }
    }
    printf("%lld\n", ans);
    return 0;
}