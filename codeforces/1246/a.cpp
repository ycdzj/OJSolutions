#include <cstdio>

int f(long long x) {
    int res = 0;
    while(x) {
        if(x & 1) {
            res++;
        }
        x >>= 1;
    }
    return res;
}

int main() {
    long long n, p;
    scanf("%lld%lld", &n, &p);
    int ans = -1;
    for(int k = 0; k <= 100; k++) {
        if(n - k * p >= k && f(n - k * p) <= k) {
            ans = k;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
