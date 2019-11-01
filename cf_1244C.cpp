#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    long long n, p, w, d;
    scanf("%lld%lld%lld%lld", &n, &p, &w, &d);
    for(long long i = 0; i < d && i <= n && p - i * w >= 0; i++) {
        if((p - i * w) % d == 0) {
            long long k = min((n - i) / d, (p - i * w) / (w * d));
            long long x = i + k * d;
            long long y = (p - x * w) / d;
            if(x + y <= n) {
                printf("%lld %lld %lld\n", x, y, n - x - y);
                return 0;
            }
        }
    }
    printf("-1\n");
    return 0;
}
