#include <cstdio>
const int MAXN = 1e5 + 5;
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
    int n, m; scanf("%d%d", &n, &m);
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int k = 1; k <= n / i; k++) {
            ans += i * mob[k] * (long long)(n / (k * i)) * (m / (k * i));
        }
    }
    printf("%lld\n", 2 * ans - (long long)n * m);
    return 0;
}