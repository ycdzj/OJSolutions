#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while(t-- > 0) {
        int n;
        scanf("%d", &n);
        int m = n / 2;
        int x = 0;
        for(int i = 1; i <= m; i++) {
            x += (1 << (n - i));
        }
        int sum = 0;
        for(int i = 1; i <= n; i++) {
            sum += (1 << i);
        }
        printf("%d\n", sum - 2 * x);
    }
    return 0;
}