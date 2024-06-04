#include <cstdio>

int main() {
    int q; scanf("%d", &q);
    while(q--) {
        long long l, r, d;
        scanf("%lld%lld%lld", &l, &r, &d);
        if(l <= d && d <= r) {
            long long k = r / d + 1;
            printf("%lld\n", k * d);
        }
        else {
            printf("%lld\n", d);
        }
    }
    return 0;
}