#include <cstdio>
typedef long long ll;
int main() {
    ll n; scanf("%lld", &n);
    if(n % 2 == 0) printf("%lld\n", n / 2);
    else {
        for(ll i = 2; i * i <= n; i++) if(n % i == 0) {
            n -= i;
            printf("%lld\n", 1 + n / 2);
            return 0;
        }
        printf("1\n");
    }
    return 0;
}