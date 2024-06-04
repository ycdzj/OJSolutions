#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        int ans = 0;
        for(int i = 0; i <= 100; i++) {
            for(int j = 0; j <= 100; j++) {
                if(i <= a && 2 * i + j <= b && 2 * j <= c) {
                    if(ans < i + j) {
                        ans = i + j;
                    }
                }
            }
        }
        printf("%d\n", ans * 3);
    }
    return 0;
}
