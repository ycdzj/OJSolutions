#include <cstdio>
#include <algorithm>
const int MAXN = 5e4 + 5;

int mob[MAXN];
bool pri[MAXN];

int main() {
    for(int i = 1; i < MAXN; i++) mob[i] = 1;
    for(int i = 2; i < MAXN; i++) if(!pri[i]) {
        mob[i] = -1;
        for(int j = 2 * i; j < MAXN; j += i) {
            pri[j] = true;
            mob[j] = -mob[j];
            if((j / i) % i == 0) mob[j] = 0;
        }
    }
    for(int i = 1; i < MAXN; i++) mob[i] += mob[i - 1];

    int n; scanf("%d", &n);
    while(n--) {
        int a, b, d; scanf("%d%d%d", &a, &b, &d);
        long long ans = 0;
        for(int i = 1; i <= a / d && i <= b / d; ) {
            int x = a / (d * i);
            int y = b / (d * i);
            int j = std::min(a / (x * d), b / (y * d));
            ans += (long long)x * y * (mob[j] - mob[i - 1]);
            i = j + 1;
        }
        printf("%lld\n", ans);
    }

    return 0;
}