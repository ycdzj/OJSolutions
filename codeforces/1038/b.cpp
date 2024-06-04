#include <cstdio>
long long gcd(long long a, long long b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}
int main() {
    int n; scanf("%d", &n);
    long long sum = (long long)n * (n + 1) / 2;
    for(int i = 1; i <= n; i++) {
        if(gcd(i, sum - i) > 1) {
            printf("Yes\n");
            printf("1 %d\n", i);
            printf("%d", n - 1);
            for(int j = 1; j <= n; j++) if(i != j) {
                printf(" %d", j);
            }
            printf("\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}