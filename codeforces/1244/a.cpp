#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int a, b, c, d, k;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        int x = (a - 1) / c + 1;
        int y = (b - 1) / d + 1;
        if(x + y > k) {
            printf("-1\n");
        }
        else {
            printf("%d %d\n", x, y);
        }
    }
    return 0;
}
