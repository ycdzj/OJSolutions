#include <cstdio>
long long gcd(long long a, long long b) {
    if(a == 0) return b;
    return gcd(b % a, a);
}
void solve() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    if(gcd(a, b) == 1) {
        printf("1\n");
        printf("%lld ", a);
        printf("%lld\n", b);
    }
    else {
        for(int i = 2; i <= 100 && a - i >= 2; i++) for(int j = 2; j <= 100 && b - j >= 2; j++) {
            if(gcd(i, j) == 1 && gcd(a - i, b - j) == 1) {
                printf("2\n");
                printf("%d %d\n", i, j);
                printf("%lld %lld\n", a - i, b - j);
                return;
            }
        }
        printf("-1\n");
    }
}
int main() {
    int T; scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}